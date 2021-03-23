int f() {
  int a = 1;
  switch (a) {
    case 1: {
      a += 1;
    }
    case 2: {
      a += 2;
    }
    case 3: {
      a += 3;
    }
  }
  return a;
}
