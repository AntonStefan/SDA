#include <stdio.h>

unsigned long long f[500];

unsigned long long fibb(int k){
    if(k <= 1)
        return f[k];
    return fibb(k - 2) + fibb(k - 1);
    if(f[k] == 0)
        f[k] = f[k - 2] + f[k - 1];
}

int main()
{   
    int k;
    f[0] = 0;
    f[1] = 1;
    scanf("%d", &k);
    printf("%llu", fibb(k));

    return 0;
}