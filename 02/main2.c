// works once a while, but modifies x
int eventually_works(int *x);

typedef struct {
  int rax;
  int rbx;
  // ...
  int pc; // program counter
} Regs;

int save_registers(Regs *regs) {
  // mov regs->rax, $rax
  // mov regs->rbx, $rbx
  // ...
  // mov $retval, 0
  // mov regs->pc, $pc /// <<<<<<<< $pc points here
  // ret $retval
}

void restore_registers(Regs *regs, int retval) {
  // mov $rax, regs->rax
  // mov $rbx, regs->rbx
  // ...
  // mov $retval, retval
  // jmp regs->pc + 1
}

static Regs cpu_state;

void some_stuff(int *x) {
  if (!eventually_works(&x))
    restore_registers(&cpu_state, 1);
}

int main() {
  int x;

  int retval = save_registers(&cpu_state);
  if (retval == 1) {
    // log failed attempt
  }
  x = 42;
  some_stuff(&x);
  
  
  return 0;
}

