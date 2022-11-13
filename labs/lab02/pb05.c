#include <stdio.h>

int binSearch(int x, int *v, int st, int dr){
    int mij = (st + dr) / 2;
    if(st > dr)
        return -1;
    if(v[mij] == x)
        return mij;
    if(x > v[mij])
        binSearch(x, v, mij+1, dr);
    else
        binSearch(x, v, st, mij-1);    
}

int cautarePiv(int *v, int n){
    int i;
    for(i = 1; i < n; i++){
        if(v[i-1] > v[i])
            return i - 1;
    }
    return -1;
}

int main(){

    int v[100];
    int i, n, x;
    int piv , rez1, rez2;
    //Citire date
    scanf("%d", &n);
    for(i = 0; i < n; i++)
        scanf("%d", &v[i]);
    scanf("%d", &x);
    //Gasire pivot
    piv = cautarePiv(v, n);
    if(piv == -1){
        printf("%d", binSearch(x, v, 0, n-1));
    }
    else{
        rez1 = binSearch(x, v, 0, piv);
        rez2 = binSearch(x, v, piv+1, n-1);
        if(rez1 != -1)
            printf("%d", rez1);
        else
            printf("%d", rez2);
    }
    printf("\n");
    
    return 0;
}