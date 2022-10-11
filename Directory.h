#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct directory {
    char Nome[50];
    struct directory *Pai;
    struct directory *Filho;
    struct directory *Irmao;
    int Tipo;
} Directory;

Directory* Inicializar();
Directory* InserirDirectory(Directory* Atual, char Nome[]);
Directory* InserirFile(Directory* Atual, char Nome[]);
void MostrarDiretorios(Directory* Atual);
Directory* EntraDiretorio(Directory* Atual, char Nome[]);
Directory* VoltarDiretorio(Directory* Atual);
Directory* DeletaElemento(Directory* Atual, char Nome[]);
void DeletaElementoAux(Directory *Atual);

//Função responsavel por inicializa a raiz do sistema de arquivos

Directory* Inicializar() {
    Directory* Root = (Directory*) malloc(sizeof (Directory));
    if (Root != NULL) {
        Root->Pai = NULL;
        strcpy(Root->Nome, "");
        Root->Irmao = NULL;
        Root->Filho = NULL;
        Root->Tipo = 0;
    }
    return Root;
}

//Função responsavel por entrar em um diretorio determinado pelo usuario

Directory* EntraDiretorio(Directory* Atual, char Nome[]) {
    Directory* tmp = (Directory*) malloc(sizeof (Directory));
    Directory* Current = (Directory*) malloc(sizeof (Directory));
    Current = Atual;
    tmp = Atual;

    Atual = Atual->Filho;
    if ((strcmp(Atual->Nome, Nome) == 0)&&(Atual->Tipo == 0))
        tmp = Atual;
    else {

        while (Atual->Irmao != NULL) {
            Atual = Atual->Irmao;
            if (strcmp(Atual->Nome, Nome) == 0 && Atual->Tipo == 0) {
                tmp = Atual;
                return tmp;
            }
        }
        printf("o sistema nao pode encontrar o caminho especificado.\n\n");
        tmp = Current;
    }
    return tmp;
}

//Função responsavel por retornar a pasta pai

Directory* VoltarDiretorio(Directory* Atual) {
    if (Atual->Pai != NULL) {
        Atual = Atual->Pai;
    }
    return Atual;
}

//Função responsavel pela inserção de uma pasta

Directory* InserirDirectory(Directory* Atual, char Nome[]) {
    Directory* Pai = (Directory*) malloc(sizeof (Directory));
    Directory* Aux = Atual;
    Directory *novoDirectory = (Directory*) malloc(sizeof (Directory));
    Pai = Atual;
    if (Atual->Filho != NULL) {
        Atual = Atual->Filho;
        if (strcmp(Nome, Atual->Nome) < 0) {
            Aux = Atual;

            Pai->Filho = novoDirectory;
            novoDirectory->Pai = Pai;
            novoDirectory->Irmao = Atual;
            strcpy(novoDirectory->Nome, Nome);
            novoDirectory->Filho = NULL;
            novoDirectory->Tipo = 0;
        } else {

            while (Atual->Irmao != NULL)
            {
                Aux = Atual;
                Atual = Atual->Irmao;

                if (strcmp(Nome, Atual->Nome) < 0) {
                    Aux->Irmao = novoDirectory;
                    novoDirectory->Pai = Pai;
                    novoDirectory->Irmao = Atual;
                    strcpy(novoDirectory->Nome, Nome);
                    novoDirectory->Filho = NULL;
                    novoDirectory->Tipo = 0;
                    return Pai;
                }

            }

            novoDirectory->Pai = Pai;
            novoDirectory->Irmao = NULL;
            Atual->Irmao = novoDirectory;
            strcpy(novoDirectory->Nome, Nome);
            novoDirectory->Filho = NULL;
            novoDirectory->Tipo = 0;

        }
    } else {
        novoDirectory->Pai = Pai;
        novoDirectory->Filho = NULL;
        novoDirectory->Irmao = NULL;
        novoDirectory->Tipo = 0;
        strcpy(novoDirectory->Nome, Nome);
        Atual->Filho = novoDirectory;
    }
    return Pai;
}

//Função responsavel pela inserção de um arquivo
Directory* InserirFile(Directory* Atual, char Nome[]) {
    Directory* Pai = (Directory*) malloc(sizeof (Directory));
    Directory* Aux = Atual;
    Directory *novoDirectory = (Directory*) malloc(sizeof (Directory));
    Pai = Atual;
    if (Atual->Filho != NULL) {
        Atual = Atual->Filho;
        if (strcmp(Nome, Atual->Nome) < 0) {
            Aux = Atual;

            Pai->Filho = novoDirectory;
            novoDirectory->Pai = Pai;
            novoDirectory->Irmao = Atual;
            strcpy(novoDirectory->Nome, Nome); 
            novoDirectory->Filho = NULL;
            novoDirectory->Tipo = 1;

            while (Atual->Irmao != NULL)
            {
                Aux = Atual;
                Atual = Atual->Irmao; 

                if (strcmp(Nome, Atual->Nome) < 0) {
                    Aux->Irmao = novoDirectory;
                    novoDirectory->Pai = Pai;
                    novoDirectory->Irmao = Atual;
                    strcpy(novoDirectory->Nome, Nome);
                    novoDirectory->Filho = NULL;
                    novoDirectory->Tipo = 1;
                    return Pai;
                }

            }

            novoDirectory->Pai = Pai;
            novoDirectory->Irmao = NULL;
            Atual->Irmao = novoDirectory;
            strcpy(novoDirectory->Nome, Nome);
            novoDirectory->Filho = NULL;
            novoDirectory->Tipo = 1;

        }
    } else {
        novoDirectory->Pai = Pai;
        novoDirectory->Filho = NULL;
        novoDirectory->Irmao = NULL;
        novoDirectory->Tipo = 1;
        strcpy(novoDirectory->Nome, Nome);
        Atual->Filho = novoDirectory;
    }
    return Pai;
}

//Função responsavel por listar elementos dentro da pasta

void MostrarDiretorios(Directory* Atual) {
    if (Atual->Filho == NULL)
        printf("diretorio vazio \n");
    else {
        Atual = Atual->Filho;
        while (Atual != NULL)
        {
          if(Atual->Tipo == 0)
            printf("%s/\n", Atual->Nome);
          else
          printf("%s\n", Atual->Nome);

          Atual = Atual->Irmao;
        }
    }
}

//Função auxiliar para deletar elementos

void DeletaElementoAux(Directory *Atual) {
    if (Atual != NULL) {
        DeletaElementoAux(Atual->Filho);
        printf("foi deletado com sucesso: %s\n", Atual->Nome);
        free(Atual);
        DeletaElementoAux(Atual->Irmao);
    }
}

//Função de deletar elemento

Directory* DeletaElemento(Directory* Atual, char Nome[]) {
    int Count = 0;
    Directory *Aux = Atual;
    Directory *Anterior = Atual;
    Anterior = Atual->Filho;

    if (Atual->Filho == NULL)
          printf("comando invalido\n");
    else {
        Atual = Atual->Filho;
        if (strcmp(Nome, Atual->Nome) == 0) {
            Count++;
            if (Atual->Irmao == NULL) {
                if (Atual->Filho == NULL) {
                    free(Atual);
                    Aux->Filho = NULL;
                    return Aux;
                } else {
                    DeletaElementoAux(Atual->Filho);
                    Aux->Filho = NULL;
                    free(Atual);
                    return Aux;
                }
            } else {
                if (Atual->Filho == NULL) {
                    Aux->Filho = Atual->Irmao;
                    free(Atual);
                    return Aux;
                } else {
                    Aux->Filho = Atual->Irmao;
                    DeletaElementoAux(Atual->Filho);
                    free(Atual);
                    return Aux;
                }
            }
        }
        else {
            while (Atual->Irmao != NULL) {
                Anterior = Atual;
                Atual = Atual->Irmao;
                if (strcmp(Nome, Atual->Nome) == 0) {
                  Count++;
                    if (Atual->Irmao == NULL) {
                        if (Atual->Filho == NULL) {
                            Anterior->Irmao = NULL;
                            free(Atual);
                            return Aux;
                        } else {
                            DeletaElementoAux(Atual->Filho);
                            Anterior->Irmao = NULL;
                            free(Atual);
                            return Aux;
                        }
                    } else {
                        if (Atual->Filho = NULL) {
                            Anterior->Irmao = Atual->Irmao;
                            free(Atual);
                            return Aux;
                        } else {
                            DeletaElementoAux(Atual->Filho);
                            Anterior->Irmao = Atual->Irmao;
                            free(Atual);
                            return Aux;
                        }
                    }
                }
            }
        }
    }
    //if(Count == 0){
      //printf("Nao existe arquivo/pasta com esse nome\n");
   //}
    return Aux;
}
//Fim da função
