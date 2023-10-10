#include <unwind.h>
#include "exception_class.h"
#include <stdlib.h>

// Coming from LLVM's compiler-rt
// Pointer encodings documented at:
//   http://refspecs.freestandards.org/LSB_1.3.0/gLSB/gLSB/ehframehdr.html

#define DW_EH_PE_omit 0xff // no data follows

#define DW_EH_PE_absptr 0x00
#define DW_EH_PE_uleb128 0x01
#define DW_EH_PE_udata2 0x02
#define DW_EH_PE_udata4 0x03
#define DW_EH_PE_udata8 0x04
#define DW_EH_PE_sleb128 0x09
#define DW_EH_PE_sdata2 0x0A
#define DW_EH_PE_sdata4 0x0B
#define DW_EH_PE_sdata8 0x0C

#define DW_EH_PE_pcrel 0x10
#define DW_EH_PE_textrel 0x20
#define DW_EH_PE_datarel 0x30
#define DW_EH_PE_funcrel 0x40
#define DW_EH_PE_aligned 0x50

// read a uleb128 encoded value and advance pointer
static size_t readULEB128(const uint8_t **data) {
  size_t result = 0;
  size_t shift = 0;
  unsigned char byte;
  const uint8_t *p = *data;
  do {
    byte = *p++;
    result |= (byte & 0x7f) << shift;
    shift += 7;
  } while (byte & 0x80);
  *data = p;
  return result;
}

// read a pointer encoded value and advance pointer
static uintptr_t readEncodedPointer(const uint8_t **data, uint8_t encoding) {
  const uint8_t *p = *data;
  uintptr_t result = 0;

  if (encoding == DW_EH_PE_omit)
    return 0;

  // first get value
  switch (encoding & 0x0F) {
  case DW_EH_PE_absptr:
    result = *((const uintptr_t *)p);
    p += sizeof(uintptr_t);
    break;
  case DW_EH_PE_uleb128:
    result = readULEB128(&p);
    break;
  case DW_EH_PE_udata2:
    result = *((const uint16_t *)p);
    p += sizeof(uint16_t);
    break;
  case DW_EH_PE_udata4:
    result = *((const uint32_t *)p);
    p += sizeof(uint32_t);
    break;
  case DW_EH_PE_udata8:
    result = *((const uint64_t *)p);
    p += sizeof(uint64_t);
    break;
  case DW_EH_PE_sdata2:
    result = *((const int16_t *)p);
    p += sizeof(int16_t);
    break;
  case DW_EH_PE_sdata4:
    result = *((const int32_t *)p);
    p += sizeof(int32_t);
    break;
  case DW_EH_PE_sdata8:
    result = *((const int64_t *)p);
    p += sizeof(int64_t);
    break;
  case DW_EH_PE_sleb128:
  default:
    // not supported
    abort();
    break;
  }

  // then add relative offset
  switch (encoding & 0x70) {
  case DW_EH_PE_absptr:
    // do nothing
    break;
  case DW_EH_PE_pcrel:
    result += (uintptr_t)(*data);
    break;
  case DW_EH_PE_textrel:
  case DW_EH_PE_datarel:
  case DW_EH_PE_funcrel:
  case DW_EH_PE_aligned:
  default:
    // not supported
    abort();
    break;
  }

  *data = p;
  return result;
}

// End of compiler-rt code

_Unwind_Reason_Code
llvm_social_personality(int version,
                        _Unwind_Action actions,
                        uint64_t exceptionClass,
                        _Unwind_Exception *unwind_exception,
                        _Unwind_Context *context) {
  // Do not handle "foreign" exceptions
  if (exceptionClass != LLVMSocialExceptionClass) {
    return _URC_CONTINUE_UNWIND;
  }
  // Language Specific Data
  const uint8_t *lsda = (const uint8_t *)_Unwind_GetLanguageSpecificData(context);
  if (!lsda) {
    return _URC_CONTINUE_UNWIND;
  }

  uintptr_t pc = (uintptr_t)_Unwind_GetIP(context) - 1;
  uintptr_t funcStart = (uintptr_t)_Unwind_GetRegionStart(context);
  uintptr_t pcOffset = pc - funcStart;

  // Parse LSDA header.
  uint8_t lpStartEncoding = *lsda++;
  const uint8_t *lpStart = 0;
  if (lpStartEncoding != DW_EH_PE_omit) {
    readEncodedPointer(&lsda, lpStartEncoding);
    lpStart = (const uint8_t *)readEncodedPointer(&lsda, lpStartEncoding);
  }
  if (lpStart == 0) {
    lpStart = (const uint8_t *)funcStart;
  }

  uint8_t ttypeEncoding = *lsda++;
  if (ttypeEncoding != DW_EH_PE_omit) {
    readULEB128(&lsda);
  }

  // Walk call-site table looking for range that includes current PC.
  uint8_t callSiteEncoding = *lsda++;
  uint32_t callSiteTableLength = readULEB128(&lsda);
  const uint8_t *callSiteTableStart = lsda;
  const uint8_t *callSiteTableEnd = callSiteTableStart + callSiteTableLength;
  const uint8_t *p = callSiteTableStart;
  while (p < callSiteTableEnd) {
    uintptr_t start = readEncodedPointer(&p, callSiteEncoding);
    size_t length = readEncodedPointer(&p, callSiteEncoding);
    size_t landingPad = readEncodedPointer(&p, callSiteEncoding);
    readULEB128(&p);
    if (landingPad == 0) {
      continue; // no landing pad for this entry
    }

    if ((start <= pcOffset) && (pcOffset < (start + length))) {
      if (actions & _UA_SEARCH_PHASE) {
        return _URC_HANDLER_FOUND;
      }

      // LLVM expects two values to be passed to the landing pad
      _Unwind_SetGR(context, __builtin_eh_return_data_regno(0), (uintptr_t)unwind_exception);
      _Unwind_SetGR(context, __builtin_eh_return_data_regno(1), (uintptr_t)0);
      landingPad = (uintptr_t)lpStart + landingPad;
      _Unwind_SetIP(context, landingPad);
      return _URC_INSTALL_CONTEXT;
    }
  }
  return _URC_CONTINUE_UNWIND;
}