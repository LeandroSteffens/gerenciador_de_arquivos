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
//Fim da definicação da estrutura

//Inicio de declaração de Funções
Dir* Inicializar();
Dir* InserirDir(Dir* Atual, char Nome[]);
Dir* InserirFile(Dir* Atual, char Nome[]);
void MostrarDiretorios(Dir* Atual);
Dir* EntraDiretorio(Dir* Atual, char Nome[]);
Dir* VoltarDiretorio(Dir* Atual);
Dir* DeletaElemento(Dir* Atual, char Nome[]);
void DeletaElementoAux(Dir *Atual);
//Fim de declaração de Funções

//Função responsavel por inicializa a raiz do sistema de arquivos

Dir* Inicializar() {
    Dir* Root = (Dir*) malloc(sizeof (Dir)); //Aloca o novo elemento
    if (Root != NULL) { //Verifica se o elemento foi alocado
        Root->Pai = NULL; //Atribui null ao pai
        strcpy(Root->Nome, ""); //Atribui o nome como root
        Root->Irmao = NULL; //atribui ao irmao null
        Root->Filho = NULL; //atribui ao filho null
        Root->Tipo = 0; //atribui ao tipo o valor 0, que no sistema 0 é considerado como uma pasta
    }
    return Root; //Retorna o elemento root
}
//Fim da função

//Função responsavel por entrar em um diretorio determinado pelo usuario

Dir* EntraDiretorio(Dir* Atual, char Nome[]) {
    Dir* tmp = (Dir*) malloc(sizeof (Dir)); //Aloca uma variavel temporaria
    Dir* Current = (Dir*) malloc(sizeof (Dir));
    Current = Atual;
    tmp = Atual; //Atribui a variavel o atual

    Atual = Atual->Filho; //Pega o filho do atual
    if ((strcmp(Atual->Nome, Nome) == 0)&&(Atual->Tipo == 0)) //Verifica se o nome do filho é o mesmo informado,se o tipo é uma pasta
        tmp = Atual; //Caso seja atribui ao tmp o valor do atual
    else {

        while (Atual->Irmao != NULL) { //Percorre os irmaos até encontrar um arquivo com o nome desejadp
            Atual = Atual->Irmao; //Atribui ao atual o proximo irmao
            if (strcmp(Atual->Nome, Nome) == 0 && Atual->Tipo == 0) { //Verifica se o nome do diretório é o mesmo que o usuário passou e se é uma pasta
                tmp = Atual; //tmp recebe atual
                return tmp; //retorna tmp
            }
        }
        printf("O Sistema nao pode encontrar o caminho especificado.\n\n");
        tmp = Current;
    }
    return tmp; //Retorna o valor encontrado
}

//Função responsavel por retornar a pasta pai

Dir* VoltarDiretorio(Dir* Atual) {
    if (Atual->Pai != NULL) { //Verifica se o pai existe
        Atual = Atual->Pai; //Atribui a atual o pai
    }
    return Atual; //Retorna o atual
}
//Fim da função

//Função responsavel pela inserção de uma pasta

Dir* InserirDir(Dir* Atual, char Nome[]) {
    Dir* Pai = (Dir*) malloc(sizeof (Dir)); //Aloca um elemento
    Dir* Aux = Atual;
    Dir *novoDir = (Dir*) malloc(sizeof (Dir)); //Aloca novo elemento
    Pai = Atual; //Elemento pai recebe o atual
    if (Atual->Filho != NULL) { //Verifica se se existe filho
        Atual = Atual->Filho; //Atual recebe o filho
        if (strcmp(Nome, Atual->Nome) < 0) {
            Aux = Atual;

            Pai->Filho = novoDir;
            novoDir->Pai = Pai; //Atribui ao Pai o elemento pai
            novoDir->Irmao = Atual; //Atribui ao Irmao o valor null
            strcpy(novoDir->Nome, Nome); //Atribui um nome ao novo elemento
            novoDir->Filho = NULL; //Atribui null ao filho do novo elemento
            novoDir->Tipo = 0; //Atribui 0 ao Tipo representando uma pasta
        } else {

            while (Atual->Irmao != NULL) //Percorre os diretorios enquanto ouverem irmaos
            {
                Aux = Atual;
                Atual = Atual->Irmao; //Pega o proximo irmao

                if (strcmp(Nome, Atual->Nome) < 0) {
                    Aux->Irmao = novoDir;
                    novoDir->Pai = Pai; //Atribui ao Pai o elemento pai
                    novoDir->Irmao = Atual; //Atribui ao Irmao o valor null
                    strcpy(novoDir->Nome, Nome); //Atribui um nome ao novo elemento
                    novoDir->Filho = NULL; //Atribui null ao filho do novo elemento
                    novoDir->Tipo = 0; //Atribui 0 ao Tipo representando uma pasta
                    return Pai;
                }

            }

            novoDir->Pai = Pai; //Atribui ao Pai o elemento pai
            novoDir->Irmao = NULL; //Atribui ao Irmao o valor null
            Atual->Irmao = novoDir; // Atribui como irmao do atual o novo elemento
            strcpy(novoDir->Nome, Nome); //Atribui um nome ao novo elemento
            novoDir->Filho = NULL; //Atribui null ao filho do novo elemento
            novoDir->Tipo = 0; //Atribui 0 ao Tipo representando uma pasta

        }
    } else {
        novoDir->Pai = Pai; //Atribui ao Pai o elemento pai
        novoDir->Filho = NULL; //Atribui null ao filho do novo elemento
        novoDir->Irmao = NULL; //Atribui ao Irmao o valor null
        novoDir->Tipo = 0; //Atribui 0 ao Tipo representando uma pasta
        strcpy(novoDir->Nome, Nome); //Atribui um nome ao novo elemento
        Atual->Filho = novoDir; //Atribui ao Atual filho o novo elemento
    }
    return Pai; //Retorna o elemento pai
}
//Fim da função

//Função responsavel pela inserção de um arquivo
Dir* InserirFile(Dir* Atual, char Nome[]) {
    Dir* Pai = (Dir*) malloc(sizeof (Dir)); //Aloca um elemento
    Dir* Aux = Atual;
    Dir *novoDir = (Dir*) malloc(sizeof (Dir)); //Aloca novo elemento
    Pai = Atual; //Elemento pai recebe o atual
    if (Atual->Filho != NULL) { //Verifica se se existe filho
        Atual = Atual->Filho; //Atual recebe o filho
        if (strcmp(Nome, Atual->Nome) < 0) {
            Aux = Atual;

            Pai->Filho = novoDir;
            novoDir->Pai = Pai; //Atribui ao Pai o elemento pai
            novoDir->Irmao = Atual; //Atribui ao Irmao o valor null
            strcpy(novoDir->Nome, Nome); //Atribui um nome ao novo elemento
            novoDir->Filho = NULL; //Atribui null ao filho do novo elemento
            novoDir->Tipo = 1; //Atribui 0 ao Tipo representando uma pasta
        } else {

            while (Atual->Irmao != NULL) //Percorre os diretorios enquanto ouverem irmaos
            {
                Aux = Atual;
                Atual = Atual->Irmao; //Pega o proximo irmao

                if (strcmp(Nome, Atual->Nome) < 0) {
                    Aux->Irmao = novoDir;
                    novoDir->Pai = Pai; //Atribui ao Pai o elemento pai
                    novoDir->Irmao = Atual; //Atribui ao Irmao o valor null
                    strcpy(novoDir->Nome, Nome); //Atribui um nome ao novo elemento
                    novoDir->Filho = NULL; //Atribui null ao filho do novo elemento
                    novoDir->Tipo = 1; //Atribui 0 ao Tipo representando uma pasta
                    return Pai;
                }

            }

            novoDir->Pai = Pai; //Atribui ao Pai o elemento pai
            novoDir->Irmao = NULL; //Atribui ao Irmao o valor null
            Atual->Irmao = novoDir; // Atribui como irmao do atual o novo elemento
            strcpy(novoDir->Nome, Nome); //Atribui um nome ao novo elemento
            novoDir->Filho = NULL; //Atribui null ao filho do novo elemento
            novoDir->Tipo = 1; //Atribui 0 ao Tipo representando uma pasta

        }
    } else {
        novoDir->Pai = Pai; //Atribui ao Pai o elemento pai
        novoDir->Filho = NULL; //Atribui null ao filho do novo elemento
        novoDir->Irmao = NULL; //Atribui ao Irmao o valor null
        novoDir->Tipo = 1; //Atribui 0 ao Tipo representando uma pasta
        strcpy(novoDir->Nome, Nome); //Atribui um nome ao novo elemento
        Atual->Filho = novoDir; //Atribui ao Atual filho o novo elemento
    }
    return Pai; //Retorna o elemento pai
}
//Fim da função

//Função responsavel por listar elementos dentro da pasta

void MostrarDiretorios(Dir* Atual) {
    if (Atual->Filho == NULL) //Verifica se existem arquivos
        printf("\n diretorio Vazio \n\n"); //Exibe mensagem caso não houver
    else {
        Atual = Atual->Filho; //Pega o filho do elemento atual
        while (Atual != NULL) //Percorre enquanto o atual for diferente de null
        {
          if(Atual->Tipo == 0)
            printf("%s-\n", Atual->Nome); //Imprime o nome do atual
          else
          printf("%s\n", Atual->Nome); //Imprime o nome do atual

          Atual = Atual->Irmao; //Pega o proximo irmao
        }
    }
}
//Fim da função

//Função auxiliar para deletar elementos

void DeletaElementoAux(Dir *Atual) {
    if (Atual != NULL) { //Veritica se o atual é diferente de null
        DeletaElementoAux(Atual->Filho); //Chama a função novamente passando o proximo filho
        printf("Foi Deletado Com Sucesso: %s\n", Atual->Nome);
        free(Atual); //libera atual
        DeletaElementoAux(Atual->Irmao); //Chama a função novamente passando o proximo irmao
    }
}
//Fim da função

//Função de deletar elemento

Dir* DeletaElemento(Dir* Atual, char Nome[]) {
    int Count = 0;
    Dir *Aux = Atual;
    Dir *Anterior = Atual;
    Anterior = Atual->Filho;

    if (Atual->Filho == NULL) //Verifica se o diretórito é vazio
          printf("comando invalido\n");
    else { //Caso não esteja vazio
        Atual = Atual->Filho; //Atual recebe o filho
        if (strcmp(Nome, Atual->Nome) == 0) { //Verifica se o filho é o arquivo desejado
            Count++;
            if (Atual->Irmao == NULL) { //Verifica se o arquivo não tem irmaos
                if (Atual->Filho == NULL) { //Verifica se o arquivo não tem filhos
                    free(Atual); //libera o atual
                    Aux->Filho = NULL; //atribui null no elemento filho da pasta pai
                    return Aux; //retorna a pasta pai
                } else { //caso tenha filhos
                    DeletaElementoAux(Atual->Filho); //chama função auxiliar para deletar demais elementos
                    Aux->Filho = NULL; //O filho da pasta pai passa a ser o irmao do atual
                    free(Atual); //libera o atual
                    return Aux; //retorna a pasta pai
                }
            } else { //se houverem irmaos
                if (Atual->Filho == NULL) { //verifica se não tem filhos
                    Aux->Filho = Atual->Irmao; //O filho da pasta pai passa a ser o irmao do atual
                    free(Atual); //Libera o atual
                    return Aux; //Retorna a pasta pai
                } else { //caso tenha filhos
                    Aux->Filho = Atual->Irmao; //O filho da pasta pai passa a ser o irmao do atual
                    DeletaElementoAux(Atual->Filho); //chama função auxiliar para deletar demais elementos
                    free(Atual); //Libera o atual
                    return Aux; //Retorna a pasta pai
                }
            }
        }
        else { //caso o filho não seja o valor desejado
            while (Atual->Irmao != NULL) { //Percorre o atual enquanto auverem pastas
                Anterior = Atual; //Anterior recebe atual
                Atual = Atual->Irmao; //Atual recebe o proximo irmao
                if (strcmp(Nome, Atual->Nome) == 0) { //Compara se é o arquivo desejado
                  Count++;
                    if (Atual->Irmao == NULL) {  //Verifica se não tem irmaos
                        if (Atual->Filho == NULL) { //Verifica se não tem filhos
                            Anterior->Irmao = NULL; //Irmão do anterior recebe null
                            free(Atual); //Libera o atual
                            return Aux; //retorna a pasta pai
                        } else { //caso tenha filhos
                            DeletaElementoAux(Atual->Filho); //chama função auxiliar para deletar demais elementos
                            Anterior->Irmao = NULL; //Irmão do anterior recebe null
                            free(Atual); //Libera o atual
                            return Aux; //retorna a pasta pai
                        }
                    } else { //Caso tenha irmaos
                        if (Atual->Filho = NULL) { //Verifica se não tem filhos
                            Anterior->Irmao = Atual->Irmao; //Anterior recebe o proximo como irmao
                            free(Atual); //Libera o atual
                            return Aux; //retorna o pai
                        } else { //Caso tenha filhos
                            DeletaElementoAux(Atual->Filho); //chama função auxiliar para deletar demais elementos
                            Anterior->Irmao = Atual->Irmao;  //Anterior recebe o proximo como irmao
                            free(Atual); //Libera o atual
                            return Aux; //retorna o pai
                        }
                    }
                }
            }
        }
    }
    return Aux;
}
//Fim da função