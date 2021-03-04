int f(){
    int a;
    a = 127;
    int b = 3;
    a &= b*2+b;
    return a;
}