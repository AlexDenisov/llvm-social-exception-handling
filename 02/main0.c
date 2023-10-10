// works once a while, but modifies x
int eventually_works(int *x);

void some_stuff(int *x) {
  if (!eventually_works(&x))
    goto start_over; // ???
}

int main() {
  int x;

start_over:
  x = 42;
  some_stuff(&x);

  return 0;
}
