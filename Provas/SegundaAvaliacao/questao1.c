#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

#define M 5

typedef struct {
    int dados[M];
    int topo;
} pilha;

bool push(pilha* p, int dado)
{
    if (p->topo < M - 1)
    {
        p->topo++;
        p->dados[p->topo] = dado;

        return true;
    }

    return false;
}

int main()
{
    pilha* p = (pilha*) malloc(sizeof(pilha));
    p->topo = -1;

    int i;
    for (i=0; i<M; i++)
    {
        push(p, i*2);
    }

    printf("\nTopo da pilha: %d\n", p->topo);

    if (push(p, 25))
    {
        printf("\nElemento %d foi inserido na pilha!\n", p->dados[p->topo]);
    }
    else
    {
        printf("\nElemento nao inserido!\n");
    }

    return 0;
}