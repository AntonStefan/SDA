#include <stdio.h>
#include <stdlib.h>

int *alocare(int size);
void citire(int *v, int n);
void afisare(int *v, int n);
int suma(int *v, int x, int pos);

int main()
{
    int *v;
    int n;
    int x, sum;
    //Rezolvare    
    scanf("%d", &n);
    v = alocare(n);
    citire(v, n);
    sum = suma(v, x, n - 1);
    printf("%d", sum);
    //Eliberare memorie
    free(v);
    return 0;
}

int *alocare(int size){
    int *v = (int*)malloc(size * sizeof(int));
    return v;
}
void citire(int *v, int n){
    int i;
    for(i = 0; i < n ;i++)
        scanf("%d", &(v[i]));
}
void afisare(int *v, int n){
    int i;
    for(i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}
int suma(int *v, int x, int pos){
    if(pos == 0)
        return v[pos];
    return v[pos] + suma(v, x, pos - 1);
}  