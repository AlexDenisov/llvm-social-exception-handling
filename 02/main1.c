// works once a while, but modifies x
int eventually_works(int *x);

typedef struct {
  int rax;
  int rbx;
  // ...
  int pc; // program counter
} Regs;

void save_registers(Regs *regs) {
  // mov regs->rax, $rax
  // mov regs->rbx, $rbx
  // ...
  // mov regs->pc, $pc /// <<<<<<<< $pc points here
  // ret
}

void restore_registers(Regs *regs) {
  // mov $rax, regs->rax
  // mov $rbx, regs->rbx
  // ...
  // jmp regs->pc + 1
}

static Regs cpu_state;

void some_stuff(int *x) {
  if (!eventually_works(&x))
    restore_registers(&cpu_state);
}

int main() {
  int x;

  save_registers(&cpu_state);
  x = 42;
  some_stuff(&x);

  return 0;
}

