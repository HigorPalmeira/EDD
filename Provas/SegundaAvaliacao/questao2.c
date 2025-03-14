#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

#define M 5

typedef struct {
    int dados[M];
    int topo;
} pilha;

int pop(pilha **p)
{
    if ((*p)->topo == -1)
    {
        return -1;
    }

    (*p)->topo--;
    return (*p)->dados[(*p)->topo+1];
}

int main()
{
    pilha* p = (pilha*) malloc(sizeof(pilha));
    p->topo = -1;
    
    int retorno = pop(&p);

    if (retorno == -1)
    {
        printf("\nA pilha estah vazia!\n");
    }

    p->topo++;
    p->dados[p->topo] = 35;

    retorno = pop(&p);
    if (retorno != -1) printf("\nO elemento %d foi removido da pilha!\n", retorno);

    retorno = pop(&p);
    if (retorno == -1)
    {
        printf("\nA pilha estah vazia!\n");
    }

    return 0;
}