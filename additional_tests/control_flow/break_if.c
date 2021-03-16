int f() {
  int a;
  a = 0;
  while (1) {
    a++;
    if (a == 3) break;
    if (a < 5) continue;
    return 123;
  }
  return a;
}
