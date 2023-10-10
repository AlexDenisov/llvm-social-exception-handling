#include <stdint.h>

// ruby -e 'puts "0x" + "LLVMSOCL".chars.map { |x| x.ord.to_s(16) }.join.upcase'
static const uint64_t LLVMSocialExceptionClass = 0x4C4C564D534F434C; // "LLVMSOCL"
