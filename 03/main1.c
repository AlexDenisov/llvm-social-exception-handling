#include <setjmp.h>

// works once a while, but modifies x
int eventually_works(int *x);

jmp_buf cpu_state;

void some_stuff(int *x) {
  if (!eventually_works(&x))
    longjmp(&cpu_state, 1);
}

void some_stuff_locked(int *x) {
  if (exists("/tmp/file.lock"))
    return;
  create_lock("/tmp/file.lock");
  some_stuff(x);
  ensure { // "finally", "defer"
    remove_lock("/tmp/file.lock");
  }
}

int main() {
  int x;

  int retval = setjmp(&cpu_state);
  if (retval == 1) {
    // log failed attempt
  }
  x = 42;
  some_stuff_locked(&x);
  
  return 0;
}

