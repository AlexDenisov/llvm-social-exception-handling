#include <setjmp.h>

// works once a while, but modifies x
int eventually_works(int *x);

jmp_buf cpu_state;

void some_stuff(int *x) {
  if (!eventually_works(&x))
    longjmp(&cpu_state, 1);
}

int main() {
  int x;

  int retval = setjmp(&cpu_state);
  if (retval == 1) {
    // log failed attempt
  }
  x = 42;
  some_stuff(&x);
  
  return 0;
}

