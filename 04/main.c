#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>

extern jmp_buf cpu_state;
void throw();

int eventually_works() {
  if (arc4random_uniform(100) < 90) {
    printf("eventually_works: failed\n");
    return 0;
  }
  printf("eventually_works: success\n");
  return 1;
}

void some_stuff() {
  if (!eventually_works())
    throw();
}

void some_stuff_locked();

int main() {
  setjmp(cpu_state);
  some_stuff_locked();
  return 0;
}
