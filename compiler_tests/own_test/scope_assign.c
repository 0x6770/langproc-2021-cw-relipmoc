int f() {
  int a;
  a = 0;
  {
    a = 2;
    { a = 1; }
  }
  return a;
}
