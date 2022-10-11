#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char Nome[50];
    struct node *prox;
} url;

int tam;

void InicializaUrl(url *Url);
void MostraUrl(url *Url);
url *AlocaElemento();
int VerificaVazio(url *Url);
void FinalizaPilha(url *Url);
void InsereElementoUrl(url *Url, char v[]);
void *DesempilhaElementoUrl(url *Url);

// Fução responsavel por inicializar o caixa

void InicializaUrl(url *Url) {
    Url->prox = NULL;
    tam = 0;
}

// Função responsavel por verificar se o caixa está vazio

int VerificaVazio(url *Url) {
    if (Url->prox == NULL)
        return 1;
    else
        return 0;
}

// Função responsavel por alocar e retornar novo elemento que será inserido no caixa

url *AlocaElemento() {
    url *novo = (url *) malloc(sizeof (url));
    return novo;
}



// Função resonsavel por listar o caminho percorrido

void MostraUrl(url *Url) {

    if (VerificaVazio(Url)) {
        printf("Nao existe URL\n\n");
        return;
    }

    url* tmp;
    tmp = Url->prox;
    while (tmp != NULL) {
        printf("%s\\", tmp->Nome);
        tmp = tmp->prox;
    }
    printf(">");
}


// Função responsavel por finalizar a url e liberar toda a memoria alocada

void FinalizaPilha(url *Url) {
    if (!VerificaVazio(Url)) {
        url *proxNode, *atual;

        atual = Url->prox;
        while (atual != NULL) {
            proxNode = atual->prox;
            free(atual);
            atual = proxNode;
        }
    }
}

// Função responsavel por inserir um novo elemento no url

void InsereElementoUrl(url *Url, char v[]) {
    url *novo = AlocaElemento();
    strcpy(novo->Nome, v);
    novo->prox = NULL;

    if (VerificaVazio(Url))
        Url->prox = novo;
    else {
        url *tmp = Url->prox;

        while (tmp->prox != NULL)
            tmp = tmp->prox;

        tmp->prox = novo;
    }
    tam++;
}

void *DesempilhaElementoUrl(url *Url) {
    if (Url->prox == NULL) {
        printf("PILHA ja vazia\n\n");
        return NULL;
    } else {
        url *ultimo = Url->prox, *penultimo = Url;

        while (ultimo->prox != NULL) {
            penultimo = ultimo;
            ultimo = ultimo->prox;
        }

        penultimo->prox = NULL;
        tam--;
    }
}
