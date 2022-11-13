#include <stdio.h>
#include <stdlib.h>

int *alocare(int size);
void citire(int *v, int n);
void afisare(int *v, int n);
int numarare(int *v, int x, int pos);

int main()
{
    int *v;
    int n;
    int x, gasite = 0;
    //Rezolvare
    scanf("%d", &n);
    v = alocare(n);
    citire(v, n);
    scanf("%d", &x);
    gasite = numarare(v, x, n - 1);
    printf("%d", gasite);
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
int numarare(int *v, int x, int pos){
    if(pos == 0)
        if(v[pos] == x)
            return 1;
        else
            return 0;
    if(v[pos] == x)
            return 1 + numarare(v, x, pos - 1);
        else
            return numarare(v, x, pos - 1);
}