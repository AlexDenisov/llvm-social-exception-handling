#include <setjmp.h>
#include <unwind.h>
#include "exception_class.h"
#include <stdio.h>
#include <stdlib.h>

static struct _Unwind_Exception global_exception;

void throw() {
  global_exception.exception_class = LLVMSocialExceptionClass;
  _Unwind_Reason_Code rc = _Unwind_RaiseException(&global_exception);
  if (rc == _URC_END_OF_STACK) {
    printf("unhandled exception\n");
    abort();
  }
}

/// ....

jmp_buf cpu_state;
void rethrow() {
  longjmp(cpu_state, 1);
}
