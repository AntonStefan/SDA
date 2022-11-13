#include <stdio.h>

unsigned long long fibb(int k){
    if(k <= 1)
        return k;
    return fibb(k - 2) + fibb(k - 1);
}

int main()
{
    int k;
    scanf("%d", &k);
    printf("%llu", fibb(k));

    return 0;
}