#include <stdio.h>

long long int putere(long long int x, int p);

int main()
{
    long long int x;
    int p;
    scanf("%lld%d", &x, &p);
    printf("%lld", putere(x, p));

    return 0;
}

long long int putere(long long int x, int p){
    if(p == 0)
        return 1;
    if(p % 2 == 0)
        return putere(x, p/2) * putere(x, p/2);
    else
        return putere(x, p/2) * putere(x, p/2) * x;
}