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
bool empilhar(PILHA* p, FILA* f);
FILA* processar_fila(FILA* f);
void pop(PILHA** p);

void exibir_pilha(PILHA* p);
void exibir_fila(FILA* f);

// programa principal
int main()
{
    PILHA* p;

    // inicializando a pilha:
    inicializar_pilha(&p);

    int i, j;
    for (i=1; i<7; i++)
    {
        FILA* f = criar_fila();

        for (j=i; j<10; j++)
        {
            inserir_na_fila(&f, j*3);
        }
        empilhar(p, f);
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

bool empilhar(PILHA* p, FILA* f)
{
    if (p->contagem < M)
    {
        f->prox = p->topo;
        p->topo = f;
        p->contagem++;
        return true;
    }
    else 
    {
        while(p->topo != NULL)
        {
            p->topo = processar_fila(p->topo);
            pop(&p);
        }
    }

    return false;
}

FILA* processar_fila(FILA* f)
{
    NO* aux = f->inicio;
    while(aux != NULL)
    {
        NO* temp = aux;
        aux = aux->prox;
        free(temp);
    }

    return f;
}

void pop(PILHA** p)
{
    if ((*p)->topo != NULL)
    {
        FILA* temp = (*p)->topo;
        
        if (temp->inicio == NULL)
        {
            (*p)->topo = (*p)->topo->prox;
            (*p)->contagem--;
            free(temp);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void exibir_pilha(PILHA* p)
{
    if (p->contagem == 0) return;

    FILA* aux = p->topo;
    int i;
    printf("\nPILHA: \"\n");
    for (i=0; i<p->contagem; i++)
    {
        exibir_fila(aux);
        aux = aux->prox;
    }
    printf("\"\n");
}

void exibir_fila(FILA* f)
{
    if (f->inicio == NULL) return;

    NO* aux = f->inicio;
    printf("\nFILA: [ ");
    while(aux != NULL)
    {
        printf("%d; ", aux->dado);
        aux = aux->prox;
    }
    printf("]\n");
}