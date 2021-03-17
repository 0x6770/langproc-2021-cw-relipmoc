int f(int *p)
{
    p = p -1;
    p = (p--)+2;
    return *p;
}