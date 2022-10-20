#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Definição da estrutura

typedef struct dir {
    char Nome[50];
    struct dir *Pai;
    struct dir *Filho;
    struct dir *Irmao;
    int Tipo;
} Dir;

//Inicio de declaração de Funções
Dir* Inicializar();
Dir* InserirDir(Dir* Atual, char Nome[]);
Dir* InserirFile(Dir* Atual, char Nome[]);
void MostrarDiretorios(Dir* Atual);
Dir* EntraDiretorio(Dir* Atual, char Nome[]);
Dir* VoltarDiretorio(Dir* Atual);
Dir* DeletaElemento(Dir* Atual, char Nome[]);
void DeletaElementoAux(Dir *Atual);

//Função responsavel por inicializa a raiz do sistema de arquivos

Dir* Inicializar() {
    Dir* Root = (Dir*) malloc(sizeof (Dir));
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

Dir* EntraDiretorio(Dir* Atual, char Nome[]) {
    Dir* tmp = (Dir*) malloc(sizeof (Dir));
    Dir* Current = (Dir*) malloc(sizeof (Dir));
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
        printf("comando invalido\n");
        tmp = Current;
    }
    return tmp;
}

//Função responsavel por retornar a pasta pai

Dir* VoltarDiretorio(Dir* Atual) {
    if (Atual->Pai != NULL) {
        Atual = Atual->Pai;
    }else
        printf("comando invalido\n");
    return Atual;
}

//Função responsavel pela inserção de uma pasta

Dir* InserirDir(Dir* Atual, char Nome[]) {
    Dir* Pai = (Dir*) malloc(sizeof (Dir));
    Dir* Aux = Atual;
    Dir *novoDir = (Dir*) malloc(sizeof (Dir));
    Pai = Atual;
    if (Atual->Filho != NULL) {
        Atual = Atual->Filho;
        if (strcmp(Nome, Atual->Nome) < 0) {
            Aux = Atual;

            Pai->Filho = novoDir;
            novoDir->Pai = Pai;
            novoDir->Irmao = Atual;
            strcpy(novoDir->Nome, Nome);
            novoDir->Filho = NULL;
            novoDir->Tipo = 0;
        } else {

            while (Atual->Irmao != NULL)
            {
                Aux = Atual;
                Atual = Atual->Irmao;

                if (strcmp(Nome, Atual->Nome) < 0) {
                    Aux->Irmao = novoDir;
                    novoDir->Pai = Pai;
                    novoDir->Irmao = Atual;
                    strcpy(novoDir->Nome, Nome);
                    novoDir->Filho = NULL;
                    novoDir->Tipo = 0;
                    return Pai;
                }

            }

            novoDir->Pai = Pai;
            novoDir->Irmao = NULL;
            Atual->Irmao = novoDir;
            strcpy(novoDir->Nome, Nome);
            novoDir->Filho = NULL;
            novoDir->Tipo = 0;

        }
    } else {
        novoDir->Pai = Pai;
        novoDir->Filho = NULL;
        novoDir->Irmao = NULL;
        novoDir->Tipo = 0;
        strcpy(novoDir->Nome, Nome);
        Atual->Filho = novoDir;
    }
    return Pai;
}

//Função responsavel pela inserção de um arquivo
Dir* InserirFile(Dir* Atual, char Nome[]) {
    Dir* Pai = (Dir*) malloc(sizeof (Dir));
    Dir* Aux = Atual;
    Dir *novoDir = (Dir*) malloc(sizeof (Dir));
    Pai = Atual;
    if (Atual->Filho != NULL) {
        Atual = Atual->Filho;
        if (strcmp(Nome, Atual->Nome) < 0) {
            Aux = Atual;

            Pai->Filho = novoDir;
            novoDir->Pai = Pai;
            novoDir->Irmao = Atual;
            strcpy(novoDir->Nome, Nome);
            novoDir->Filho = NULL;
            novoDir->Tipo = 1;
        } else {

            while (Atual->Irmao != NULL)
            {
                Aux = Atual;
                Atual = Atual->Irmao;

                if (strcmp(Nome, Atual->Nome) < 0) {
                    Aux->Irmao = novoDir;
                    novoDir->Pai = Pai;
                    novoDir->Irmao = Atual;
                    strcpy(novoDir->Nome, Nome);
                    novoDir->Filho = NULL;
                    novoDir->Tipo = 1;
                    return Pai;
                }

            }

            novoDir->Pai = Pai;
            novoDir->Irmao = NULL;
            Atual->Irmao = novoDir;
            strcpy(novoDir->Nome, Nome);
            novoDir->Filho = NULL;
            novoDir->Tipo = 1;

        }
    } else {
        novoDir->Pai = Pai;
        novoDir->Filho = NULL;
        novoDir->Irmao = NULL;
        novoDir->Tipo = 1;
        strcpy(novoDir->Nome, Nome);
        Atual->Filho = novoDir;
    }
    return Pai;
}

//Função responsavel por listar elementos dentro da pasta

void MostrarDiretorios(Dir* Atual) {
    if (Atual->Filho == NULL)
        printf("\n diretorio vazio \n\n");
    else {
        Atual = Atual->Filho;
        while (Atual != NULL)
        {
          if(Atual->Tipo == 0)
            printf("%s-\n", Atual->Nome);
          else
          printf("%s\n", Atual->Nome);

          Atual = Atual->Irmao;
        }
    }
}

//Função auxiliar para deletar elementos

void DeletaElementoAux(Dir *Atual) {
    if (Atual != NULL) {
        DeletaElementoAux(Atual->Filho);
        //printf("deletado com sucesso: %s\n", Atual->Nome);
        free(Atual);
        DeletaElementoAux(Atual->Irmao);
    }
}

//Função de deletar elemento

Dir* DeletaElemento(Dir* Atual, char Nome[]) {
    int Count = 0;
    Dir *Aux = Atual;
    Dir *Anterior = Atual;
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
        
        if(Count == 0){
      printf("comando invalido\n");
    }
    
    }
    
    return Aux;
}