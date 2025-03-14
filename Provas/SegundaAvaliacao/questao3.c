#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

#define M 5

typedef struct no
{
    int dado;
    struct no* prox;
} NO;

typedef struct fila
{
    NO* inicio;
    struct fila* prox;
} FILA;

typedef struct pilha
{
    FILA* topo;
    int contagem;
} PILHA;

// prototipos
void inicializar_pilha(PILHA** p);
NO* criar_no(int dado);
FILA* criar_fila();
bool inserir_na_fila(FILA** f, int dado);
bool inserir_na_pilha(PILHA** p, FILA* f);
void processar_fila(FILA** f);

// programa principal
int main()
{
    PILHA* p;

    // inicializando a pilha:
    inicializar_pilha(&p);

    //
    FILA* f = criar_fila();
    inserir_na_fila(&f, 35);

    if (inserir_na_pilha(&p, f))
    {
        printf("\nInserido com sucesso!\n");
    }

    return 0;
}

// subprogramas
void inicializar_pilha(PILHA** p)
{
    *p = (PILHA*) malloc(sizeof(PILHA));
    (*p)->topo = NULL;
    (*p)->contagem = 0;
}

NO* criar_no(int dado)
{
    NO* novoNo = (NO*) malloc(sizeof(NO));
    if (novoNo != NULL)
    {
        novoNo->dado = dado;
        novoNo->prox = NULL;
    }

    return novoNo;
}

FILA* criar_fila()
{
    FILA* novaFila = (FILA*) malloc(sizeof(FILA));
    if (novaFila != NULL)
    {
        novaFila->inicio = NULL;
        novaFila->prox = NULL;
    }

    return novaFila;
}

bool inserir_na_fila(FILA** f, int dado)
{
    NO* novoNo = criar_no(dado);

    if (novoNo != NULL)
    {
        if ((*f)->inicio == NULL)
        {
            (*f)->inicio = novoNo;
            return true;
        }

        NO* aux = (*f)->inicio;
        while(aux->prox != NULL)
        {
            aux = aux->prox;
        }

        aux->prox = novoNo;
        return true;
    }

    return false;
}

bool inserir_na_pilha(PILHA** p, FILA* f)
{
    if ((*p)->contagem < M)
    {
        f->prox = (*p)->topo;
        (*p)->topo = f;
        (*p)->contagem++;
        return true;
    }
    else 
    {
        printf("\nPilha cheia!\n");
    }

    return false;
}

void processar_fila(FILA** f)
{
    if ((*f)->inicio != NULL)
    {
        NO* aux = (*f)->inicio;
        while(aux != NULL)
        {
            NO* temp = aux;
            aux = aux->prox;
            free(temp);
        }
    }
}

void pop()
{
    
}