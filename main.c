#include <stdio.h>
#include <stdlib.h>

//https://www.learn-c.org/en/Linked_lists

typedef struct node{
    int value;
    struct node *left;
    struct node *right;
    struct node *dad;
} Node;

typedef struct list
{
    Node *no;
    struct list *next;
}

void showActual(Node *actual){
    if(actual == NULL);
        printf("\n %s", dir//diretorio);
}

int main(){

    int option;

    printf("\t\tGerenciador de arquivos\n\n");
    printf("\n/>");
    scanf("%d", &option);

    switch{

        case ma:
            printf("\n");
        //funcao que cria um arquivo
        break;

        case mp:
            printf("\n");
        //funcao que cria uma pasta;
        break;

        case rm:
            printf("\n");
        //funcao que delete arquivo ou pasta
        break;

        case ex:
            printf("\nSistema encerrado");
            system(pause);
        break;

        default:
            printf("\ncomando invalido");
            return main;
        break;
    }


    return 0;
}
