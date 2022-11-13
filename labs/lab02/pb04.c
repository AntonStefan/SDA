#include <stdio.h>
#include <stdlib.h>

float squareRoot(int x){
    int st = 0, dr = x, mij;
    float add, rez;
    int i;
    
    // Cautare BSearch
    while(st < dr){
        mij = (st + dr) / 2;

        if(mij * mij == x){
            rez = mij;
            break;
        }
        if(mij * mij < x){
            st =  mij + 1;
            rez = mij;
        }
        else{
            dr = mij - 1;
        }
    }
    // Aproximare precizie
    add = 0.1;
    for(i = 0; i < 3; i++){
        while(rez * rez <= x){
            rez += add;
        }
        rez -= add;
        add = add * 0.1;
    }
    return rez;
}

int main(){

    float x;
    scanf("%f", &x);
    printf("%f", squareRoot(x));

    return 0;
}