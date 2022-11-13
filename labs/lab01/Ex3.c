#include <stdio.h>
#include <stdlib.h>

long long int fibb(int pos);

int main()
{
    int pos;
   
    scanf("%d", &pos);
    printf("%lld", fibb(pos));

    return 0;
}

long long int fibb(int pos){
    if(pos == 0) 
        return 0;
    if(pos == 1)
        return 1;
    return fibb(pos - 1) + fibb(pos -2);      
}