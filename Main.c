/* 
Cesar Augusto de Araujo Filho RGA:202021901009
Leandro Steffens de Oliveira RGA:202021901032
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dir.h"
#include "End.h"

void copyStr(char dest[], char orig[],int ini, int fim){
    int i=0;
    while(i<fim && orig[i+ini] !='\0'&& orig[i+ini] != '\n'){
        dest[i] = orig[i+ini];
        i++;
    }
    dest[i] = '\0';
}

int main() {
    char cmdStr[55], Op[5];

    char Nome[50], NomeAnt[50], Aux[20];
    int i,j = 0;

    end *End = (end *) malloc(sizeof (end));
    InicializaEnd(End);

    Dir* Root = Inicializar();
    Dir* Atual = Root;
    InsereElementoEnd(End, Atual->Nome);
    do {
        MostraEnd(End);

        fflush(stdin);
        fgets(cmdStr,55,stdin);

        if(strncmp(cmdStr, "cd ..", 5) == 0){
          strcpy(Op, cmdStr);
        }
        else{
        copyStr(Nome,cmdStr,3,55);
        copyStr(Op,cmdStr,0,2);
        }

        if (strncmp(Op, "ls", 2) == 0) {

            MostrarDiretorios(Atual);

        } else if (strncmp(Op, "ma", 2) == 0) {

            Atual = InserirFile(Atual, Nome);

        } else if (strncmp(Op, "mp", 2) == 0) {

            Atual = InserirDir(Atual, Nome);

        } else if (strncmp(Op, "cd ..", 5) == 0) {
            strcpy(NomeAnt, Atual->Nome);

            Atual = VoltarDiretorio(Atual);

            if (strcmp(Atual->Nome, NomeAnt) != 0)
                DesempilhaElementoEnd(End);

        } else if (strncmp(Op, "cd", 2) == 0) {

            strcpy(NomeAnt, Atual->Nome);

            if(Atual->Filho == NULL)
              printf("comando invalido \n");
            else
            Atual = EntraDiretorio(Atual, Nome);

            if (strcmp(Atual->Nome, NomeAnt) != 0)
                InsereElementoEnd(End, Atual->Nome);

        } else if (strncmp(Op, "rm", 2) == 0) {


            Atual = DeletaElemento(Atual, Nome);

        } else if (strncmp(Op, "ex", 2) == 0) {
            printf("sistema encerrado");
            break;

        } else {
            printf("comando invalido \n");
        }


    } while (1);
    FinalizaPilha(End);
    return 0;
}
