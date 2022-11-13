#include "stack.h"
#include <string.h>


int expression_evaluation(char *exp, char *end);

int main(){

    char exp[1000], token[2] = " ";
    fgets(exp, 1000, stdin);
    exp[strlen(exp) - 1] = '\0';
    printf("%d\n", expression_evaluation(exp, NULL));

    return 0;
}

int expression_evaluation(char *exp, char* end){
    Stack *vStack, *oStack;
    char token[2] = " ";
    char *aux, *cpy = (char*)malloc(1000 * sizeof(char));
    int vTop;
    int rezAux;
    init_stack(&vStack);
    init_stack(&oStack);
    add_stack(oStack, (int)'+');
    aux = strtok(exp, token);
    while(aux != end){
        if(aux[0] == ')')
            break;
        if(48 <= aux[0] && aux[0] <= 57){
            add_stack(vStack, atoi(aux));
        }
        else{
            switch ((int)aux[0])
            {
            case (int)'*':
                vTop = pop_stack(vStack);
                aux = strtok(NULL, token);
                if((int)aux[0] == '('){
                    strcpy(cpy, aux + strlen(aux) + 1);
                    rezAux = expression_evaluation(cpy, ")");
                    add_stack(vStack, vTop * rezAux);
                }
                else
                    add_stack(vStack, vTop * atoi(aux));
                break;
            case (int)'/':
                vTop = pop_stack(vStack);
                aux = strtok(NULL, token);
                if((int)aux[0] == '('){
                    strcpy(cpy, aux + strlen(aux) + 1);
                    rezAux = expression_evaluation(cpy, ")");
                    add_stack(vStack, vTop / rezAux);
                }
                else
                    add_stack(vStack, vTop / atoi(aux));
                break;
            case (int)'(':
                strcpy(cpy, aux + strlen(aux) + 1);
                rezAux = expression_evaluation(cpy, ")");
                add_stack(vStack, rezAux);
                break;
            default:
                break;
            }
            if((int)aux[0] == '+' || (int)aux[0] == '-'){
                add_stack(oStack, (int)aux[0]);
            }
        }
        aux = strtok(NULL, token);
    }
    
    int rez = 0;
    int op;
    while(vStack->len != 0){
        op = pop_stack(oStack);
        if(op == (int)'+')
            rez = rez + pop_stack(vStack);
        else
            rez = rez - pop_stack(vStack);
    }
    free(cpy);
    free_stack(&vStack);
    free_stack(&oStack);

    return rez;
}
