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
    NO* anterior = aux;
    while(aux->prox != (*f)->inicio)
    {
        if (aux->bitR == '0')
        {
            NO* novoNo = (NO*) malloc(sizeof(NO));
            novoNo->pagina = pagina;
            novoNo->bitR = '1';
            novoNo->prox = aux->prox;
            anterior->prox = novoNo;

            if (aux == (*f)->inicio) (*f)->inicio = novoNo;
            
            if (aux == (*f)->final)
            {
                (*f)->final = novoNo;
            }

            free(aux);
            return true;
        }
        else
        {
            aux->bitR = '0';
        }

        anterior = aux;
        aux = aux->prox;
    }

}