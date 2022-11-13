#include <stdio.h>
#include <stdlib.h>

int temp[1000];

void mergeSort(int *v, int st, int dr){
    if(st >= dr)
        return;
    mergeSort(v, st, (st+dr)/2);
    mergeSort(v, (st+dr)/2+1, dr);
    //Declarare variabile
    int i, j, k, m;
    m = (st + dr) / 2;
    k = st;
    i = st;
    j = m + 1;
    //Interclasare parti vector
    while(i <= m && j <= dr){
        if(v[i] < v[j])
            temp[k++] = v[i++];
        else
            temp[k++] = v[j++];
    }
    while(i <= m)
        temp[k++] = v[i++];
    while(j <= dr)
        temp[k++] = v[j++];
    //Copiere din vectorul temporar in cel de sortat
    for(i = st; i <= dr; i++)
        v[i] = temp[i];

}

int main()
{
    int v[100];
    int i, n;

    scanf("%d", &n);
    for(i = 0; i < n; i++)
        scanf("%d", &v[i]);

    mergeSort(v, 0, n - 1);

    for(i = 0; i < n; i++)
        printf("%d ", v[i]);

    return 0;
}