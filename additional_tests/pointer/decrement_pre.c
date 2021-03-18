int f(int *p)
{   
    --p;
    p = p+2;
    return *p;
}