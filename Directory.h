#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Definição da estrutura

typedef struct directory {
    char Nome[50];
    struct directory *Pai;
    struct directory *Filho;
    struct directory *Irmao;
    int Tipo;
} Directory;
//Fim da definicação da estrutura

//Inicio de declaração de Funções
Directory* Inicializar();
Directory* InserirDirectory(Directory* Atual, char Nome[]);
Directory* InserirFile(Directory* Atual, char Nome[]);
void MostrarDiretorios(Directory* Atual);
Directory* EntraDiretorio(Directory* Atual, char Nome[]);
Directory* VoltarDiretorio(Directory* Atual);
Directory* DeletaElemento(Directory* Atual, char Nome[]);
void DeletaElementoAux(Directory *Atual);
//Fim de declaração de Funções

//Função responsavel por inicializa a raiz do sistema de arquivos

Directory* Inicializar() {
    Directory* Root = (Directory*) malloc(sizeof (Directory)); //Aloca o novo elemento
    if (Root != NULL) { //Verifica se o elemento foi alocado
        Root->Pai = NULL; //Atribui null ao pai
        strcpy(Root->Nome, "root"); //Atribui o nome como root
        Root->Irmao = NULL; //atribui ao irmao null
        Root->Filho = NULL; //atribui ao filho null
        Root->Tipo = 0; //atribui ao tipo o valor 0, que no sistema 0 é considerado como uma pasta
    }
    return Root; //Retorna o elemento root
}
//Fim da função

//Função responsavel por entrar em um diretorio determinado pelo usuario

Directory* EntraDiretorio(Directory* Atual, char Nome[]) {
    Directory* tmp = (Directory*) malloc(sizeof (Directory)); //Aloca uma variavel temporaria
    Directory* Current = (Directory*) malloc(sizeof (Directory));
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

Directory* VoltarDiretorio(Directory* Atual) {
    if (Atual->Pai != NULL) { //Verifica se o pai existe
        Atual = Atual->Pai; //Atribui a atual o pai
    }
    return Atual; //Retorna o atual
}
//Fim da função

//Função responsavel pela inserção de uma pasta

Directory* InserirDirectory(Directory* Atual, char Nome[]) {
    Directory* Pai = (Directory*) malloc(sizeof (Directory)); //Aloca um elemento
    Directory* Aux = Atual;
    Directory *novoDirectory = (Directory*) malloc(sizeof (Directory)); //Aloca novo elemento
    Pai = Atual; //Elemento pai recebe o atual
    if (Atual->Filho != NULL) { //Verifica se se existe filho
        Atual = Atual->Filho; //Atual recebe o filho
        if (strcmp(Nome, Atual->Nome) < 0) {
            Aux = Atual;

            Pai->Filho = novoDirectory;
            novoDirectory->Pai = Pai; //Atribui ao Pai o elemento pai
            novoDirectory->Irmao = Atual; //Atribui ao Irmao o valor null
            strcpy(novoDirectory->Nome, Nome); //Atribui um nome ao novo elemento
            novoDirectory->Filho = NULL; //Atribui null ao filho do novo elemento
            novoDirectory->Tipo = 0; //Atribui 0 ao Tipo representando uma pasta
        } else {

            while (Atual->Irmao != NULL) //Percorre os diretorios enquanto ouverem irmaos
            {
                Aux = Atual;
                Atual = Atual->Irmao; //Pega o proximo irmao

                if (strcmp(Nome, Atual->Nome) < 0) {
                    Aux->Irmao = novoDirectory;
                    novoDirectory->Pai = Pai; //Atribui ao Pai o elemento pai
                    novoDirectory->Irmao = Atual; //Atribui ao Irmao o valor null
                    strcpy(novoDirectory->Nome, Nome); //Atribui um nome ao novo elemento
                    novoDirectory->Filho = NULL; //Atribui null ao filho do novo elemento
                    novoDirectory->Tipo = 0; //Atribui 0 ao Tipo representando uma pasta
                    return Pai;
                }

            }

            novoDirectory->Pai = Pai; //Atribui ao Pai o elemento pai
            novoDirectory->Irmao = NULL; //Atribui ao Irmao o valor null
            Atual->Irmao = novoDirectory; // Atribui como irmao do atual o novo elemento
            strcpy(novoDirectory->Nome, Nome); //Atribui um nome ao novo elemento
            novoDirectory->Filho = NULL; //Atribui null ao filho do novo elemento
            novoDirectory->Tipo = 0; //Atribui 0 ao Tipo representando uma pasta

        }
    } else {
        novoDirectory->Pai = Pai; //Atribui ao Pai o elemento pai
        novoDirectory->Filho = NULL; //Atribui null ao filho do novo elemento
        novoDirectory->Irmao = NULL; //Atribui ao Irmao o valor null
        novoDirectory->Tipo = 0; //Atribui 0 ao Tipo representando uma pasta
        strcpy(novoDirectory->Nome, Nome); //Atribui um nome ao novo elemento
        Atual->Filho = novoDirectory; //Atribui ao Atual filho o novo elemento
    }
    return Pai; //Retorna o elemento pai
}
//Fim da função

//Função responsavel pela inserção de um arquivo
Directory* InserirFile(Directory* Atual, char Nome[]) {
    Directory* Pai = (Directory*) malloc(sizeof (Directory)); //Aloca um elemento
    Directory* Aux = Atual;
    Directory *novoDirectory = (Directory*) malloc(sizeof (Directory)); //Aloca novo elemento
    Pai = Atual; //Elemento pai recebe o atual
    if (Atual->Filho != NULL) { //Verifica se se existe filho
        Atual = Atual->Filho; //Atual recebe o filho
        if (strcmp(Nome, Atual->Nome) < 0) {
            Aux = Atual;

            Pai->Filho = novoDirectory;
            novoDirectory->Pai = Pai; //Atribui ao Pai o elemento pai
            novoDirectory->Irmao = Atual; //Atribui ao Irmao o valor null
            strcpy(novoDirectory->Nome, Nome); //Atribui um nome ao novo elemento
            novoDirectory->Filho = NULL; //Atribui null ao filho do novo elemento
            novoDirectory->Tipo = 1; //Atribui 0 ao Tipo representando uma pasta
        } else {

            while (Atual->Irmao != NULL) //Percorre os diretorios enquanto ouverem irmaos
            {
                Aux = Atual;
                Atual = Atual->Irmao; //Pega o proximo irmao

                if (strcmp(Nome, Atual->Nome) < 0) {
                    Aux->Irmao = novoDirectory;
                    novoDirectory->Pai = Pai; //Atribui ao Pai o elemento pai
                    novoDirectory->Irmao = Atual; //Atribui ao Irmao o valor null
                    strcpy(novoDirectory->Nome, Nome); //Atribui um nome ao novo elemento
                    novoDirectory->Filho = NULL; //Atribui null ao filho do novo elemento
                    novoDirectory->Tipo = 1; //Atribui 0 ao Tipo representando uma pasta
                    return Pai;
                }

            }

            novoDirectory->Pai = Pai; //Atribui ao Pai o elemento pai
            novoDirectory->Irmao = NULL; //Atribui ao Irmao o valor null
            Atual->Irmao = novoDirectory; // Atribui como irmao do atual o novo elemento
            strcpy(novoDirectory->Nome, Nome); //Atribui um nome ao novo elemento
            novoDirectory->Filho = NULL; //Atribui null ao filho do novo elemento
            novoDirectory->Tipo = 1; //Atribui 0 ao Tipo representando uma pasta

        }
    } else {
        novoDirectory->Pai = Pai; //Atribui ao Pai o elemento pai
        novoDirectory->Filho = NULL; //Atribui null ao filho do novo elemento
        novoDirectory->Irmao = NULL; //Atribui ao Irmao o valor null
        novoDirectory->Tipo = 1; //Atribui 0 ao Tipo representando uma pasta
        strcpy(novoDirectory->Nome, Nome); //Atribui um nome ao novo elemento
        Atual->Filho = novoDirectory; //Atribui ao Atual filho o novo elemento
    }
    return Pai; //Retorna o elemento pai
}
//Fim da função

//Função responsavel por listar elementos dentro da pasta

void MostrarDiretorios(Directory* Atual) {
    if (Atual->Filho == NULL) //Verifica se existem arquivos
        printf("\n Diretorio Vazio \n\n"); //Exibe mensagem caso não houver
    else {
        Atual = Atual->Filho; //Pega o filho do elemento atual
        printf("\n");
        while (Atual != NULL) //Percorre enquanto o atual for diferente de null
        {
          if(Atual->Tipo == 0)
            printf("%s/\n", Atual->Nome); //Imprime o nome do atual
          else
          printf("%s\n", Atual->Nome); //Imprime o nome do atual

          Atual = Atual->Irmao; //Pega o proximo irmao
        }
        printf("\n");
    }
}
//Fim da função

//Função auxiliar para deletar elementos

void DeletaElementoAux(Directory *Atual) {
    if (Atual != NULL) { //Veritica se o atual é diferente de null
        DeletaElementoAux(Atual->Filho); //Chama a função novamente passando o proximo filho
        printf("Foi Deletado Com Sucesso: %s\n", Atual->Nome);
        free(Atual); //libera atual
        DeletaElementoAux(Atual->Irmao); //Chama a função novamente passando o proximo irmao
    }
}
//Fim da função

//Função de deletar elemento

Directory* DeletaElemento(Directory* Atual, char Nome[]) {
    int Count = 0;
    Directory *Aux = Atual;
    Directory *Anterior = Atual;
    Anterior = Atual->Filho;

    if (Atual->Filho == NULL) //Verifica se o diretórito é vazio
          printf("Nao existe arquivo/pasta com esse nome\n");
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
    if(Count == 0){
      printf("Nao existe arquivo/pasta com esse nome\n");
    }
    return Aux;
}
//Fim da função
