#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct no 
{
    struct no* prox;
    int pagina;
    char bitR; // 0 ou 1;
} NO;

typedef struct 
{
    NO* inicio;
    NO* final;
} FILA_CIRCULAR;

// prototipos

// programa principal
int main()
{
    FILA_CIRCULAR* f;

    return 0;
}

// subprogramas



bool algoritmo_relogio(FILA_CIRCULAR** f, int pagina)
{
    if ((*f)->inicio == NULL) return true;

    NO* aux = (*f)->inicio;
    while(aux->prox != (*f)->inicio)
    {
        NO* temp = aux;
        if (aux->bitR == '0')
        {
            //remover_no(*f, aux);

            aux->pagina = pagina;
            aux->bitR = '1';
        }
        else
        {
            aux->bitR = '0';
        }

        aux = aux->prox;
    }
}

void remover_no(FILA_CIRCULAR* f, NO* no)
{

}