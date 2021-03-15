int f() {
  int a = 1;
  {
    int a = 5;
    { a = 0; }
    a = 2;
  }
  return a;
}
