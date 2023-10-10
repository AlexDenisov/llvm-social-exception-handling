// works once a while, but modifies x
int eventually_works(int *x);

int main() {
  int x;
  x = 42;
  eventually_works(&x); // may fail ???
  return 0;
}
