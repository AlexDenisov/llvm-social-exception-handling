void foo();
void bar();
void baz(int x);

int main() {
  try {
    foo();
  } catch(int x) {
    baz(x);
  } catch(...) {
    bar();
  }

  return 0;
}
