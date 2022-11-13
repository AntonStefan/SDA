#include "queue.h"

int digits_count(int val);
int max_digits_count(int *v, int n);
void sort_by_digit(Queue **vq, int *v, int n, int p);
void radix_sort(int *v, int n);


int main(){

    int x, n, *v;
    scanf("%d", &n);
    v = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i ++){
        scanf("%d", &v[i]);
    }
    radix_sort(v, n);
    for(int i = 0; i < n; i ++){
        printf("%d ", v[i]);
    }
    printf("\n");

    free(v);
    return 0;
}

int digits_count(int val){
    int count = 1;
    val = val / 10;
    while(val != 0){
        count++;
        val = val / 10;
    }
    return count;
}

int max_digits_count(int *v, int n){
    int max_digits = 0, dcTemp;
    int i;
    for(i = 0; i < n; i++){
        dcTemp = digits_count(v[i]);
        if(dcTemp > max_digits)
            max_digits = dcTemp;
    }
    return max_digits;
}

void sort_by_digit(Queue** vq, int *v, int n, int p){
    int i, k, d;
    for(i = 0; i < n; i++){
        d = (v[i] / p) % 10;
        add_queue(vq[d], v[i]);
    }
    k = 0;
    for(i = 0; i < 10; i++){
        while(vq[i]->len != 0){
            v[k++] = vq[i]->head->data;
            pop_queue(vq[i]);
        }
    }
}

void radix_sort(int *v, int n){
    int max_digits = max_digits_count(v, n);
    int p = 1;
    int i;
    Queue **vq =(Queue**)malloc(10 * sizeof(Queue*));
    for(i = 0; i < 10; i++)
        init_queue(&(vq[i]));
    
    for(i = 1; i <= max_digits; i++){
        sort_by_digit(vq, v, n, p);
        p *= 10;
    }

    for(i = 0; i < 10; i++)
        free_queue(&(vq[i]));
    free(vq);
}