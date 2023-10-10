// works once a while, but modifies x
int eventually_works(int *x);

int main() {
  int x;
  x = 42;
  while (!eventually_works(&x)) {}
  return 0;
}
