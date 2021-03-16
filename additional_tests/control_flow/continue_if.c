int f() {
  int a;
  a = 0;
  while (1) {
    a++;
    if (a < 5) continue;
    return a;
  }
}
