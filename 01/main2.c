// works once a while, but modifies x
int eventually_works(int *x);

int main() {
  int x;

start_over:
  x = 42;
  if (!eventually_works(&x))
    goto start_over;

  return 0;
}
