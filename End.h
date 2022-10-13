#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char Nome[50];
    struct node *prox;
} end;

int tam;

void InicializaEnd(end *End);
void MostraEnd(end *End);
end *AlocaElemento();
int VerificaVazio(end *End);
void FinalizaPilha(end *End);
void InsereElementoEnd(end *End, char v[]);
void *DesempilhaElementoEnd(end *End);

// Fução responsavel por inicializar o caixa

void InicializaEnd(end *End) {
    End->prox = NULL;
    tam = 0;
}

// Função responsavel por verificar se o caixa está vazio

int VerificaVazio(end *End) {
    if (End->prox == NULL)
        return 1;
    else
        return 0;
}

// Função responsavel por alocar e retornar novo elemento que será inserido no caixa

end *AlocaElemento() {
    end *novo = (end *) malloc(sizeof (end));
    return novo;
}



// Função resonsavel por listar o caminho percorrido

void MostraEnd(end *End) {

    if (VerificaVazio(End)) {
        printf("nao existe URL\n\n");
        return;
    }

    end* tmp;
    tmp = End->prox;
    while (tmp != NULL) {
        printf("%s-", tmp->Nome);
        tmp = tmp->prox;
    }
    printf(">");
}


// Função responsavel por finalizar a end e liberar toda a memoria alocada

void FinalizaPilha(end *End) {
    if (!VerificaVazio(End)) {
        end *proxNode, *atual;

        atual = End->prox;
        while (atual != NULL) {
            proxNode = atual->prox;
            free(atual);
            atual = proxNode;
        }
    }
}

// Função responsavel por inserir um novo elemento no end

void InsereElementoEnd(end *End, char v[]) {
    end *novo = AlocaElemento();
    strcpy(novo->Nome, v);
    novo->prox = NULL;

    if (VerificaVazio(End))
        End->prox = novo;
    else {
        end *tmp = End->prox;

        while (tmp->prox != NULL)
            tmp = tmp->prox;

        tmp->prox = novo;
    }
    tam++;
}

void *DesempilhaElementoEnd(end *End) {
    if (End->prox == NULL) {
        printf("pilha ja vazia\n\n");
        return NULL;
    } else {
        end *ultimo = End->prox, *penultimo = End;

        while (ultimo->prox != NULL) {
            penultimo = ultimo;
            ultimo = ultimo->prox;
        }

        penultimo->prox = NULL;
        tam--;
    }
}
