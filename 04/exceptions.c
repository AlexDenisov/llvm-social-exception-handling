#include <setjmp.h>

jmp_buf cpu_state;

void throw() {
  longjmp(cpu_state, 1);
}
