/*
	Autor: Higor Palmeira
	Descri��o: Implemente em C duas listas circulares, cada n� com dois campos: 
	dados (um inteiro) e bitR (um indicador que pode ser 0 ou 1, do tipo char ou boolean). 
	A primeira lista � a prim�ria e a segunda � a secund�ria.
	O programa deve trocar um item da lista secund�ria por um da lista prim�ria com base no seguinte crit�rio:
		1. Percorra os n�s da lista prim�ria at� encontrar um n� com bitR = 0. Esse ser� o candidato � troca;
		2. Se o bitR do n� visitado for 1, mova-o para o final da lista, ajustando bitR para 0.
		3. Ap�s a troca, o item da lista prim�ria assume a posi��o do item na secund�ria e vice-versa;
		4. O item da lista secund�ria que ingressar na lista prim�ria deve ter bitR ajustado para 1;
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>

// structs

typedef int bool;

typedef struct no {
	int dado;
	bool bitR;
	struct no* anterior;
	struct no* proximo;
} NO;

// prot�tipos
NO* criar_elemento(int dado, bool bitR);
void inserir_elemento(NO** lista, int dado, bool bitR);
void listar_elementos(NO* lista);

void trocar_elementos(NO** lista1, NO** lista2);

// programa principal
int main() {
	setlocale(LC_ALL, "");
	
	NO* lista1 = NULL;
	NO* lista2 = NULL;
	
	int resp, dado;
	bool bitR;
	resp = 0;
	
	while(resp != 6) {
		printf("SELECIONE UMA DAS OP��ES ABAIXO:\n");
		printf("[ 1 ] Inserir dado na primeira lista (LISTA 1) \n[ 2 ] Inserir dado na segunda lista (LISTA 2) \n[ 3 ] Trocar elemento entre as listas \n[ 4 ] Listar elementos da primeira lista (LISTA 1) \n[ 5 ] Listar elementos da segunda lista (LISTA 2) \n[ 6 ] SAIR\n");
		scanf("%d", &resp);
		fflush(stdin);
		
		switch(resp) {
			case 1:
				printf("Informe o dado a ser inserido na primeira lista: ");
				scanf("%d", &dado);
				fflush(stdin);
				printf("Informe o BitR a ser armazenado com o dado (0 ou 1): ");
				scanf("%d", &bitR);
				fflush(stdin);
				
				inserir_elemento(&lista1, dado, bitR);
				printf("Elemento inserido com sucesso!\n");
				getchar();
				break;
				
			case 2:
				printf("Informe o dado a ser inserido na segunda lista: ");
				scanf("%d", &dado);
				fflush(stdin);
				printf("Informe o BitR a ser armazenado com o dado (0 ou 1): ");
				scanf("%d", &bitR);
				fflush(stdin);
				
				inserir_elemento(&lista2, dado, bitR);
				printf("Elemento inserido com sucesso!\n");
				getchar();
				break;
				
			case 3:
				printf("Um elemento da primeira lista ser� trocado por elemento da segunda lista!\n");
				trocar_elementos(&lista1, &lista2);
				getchar();
				break;
				
			case 4:
				listar_elementos(lista1);
				getchar();
				break;
				
			case 5:
				listar_elementos(lista2);
				getchar();
				break;
		}
		
		system("cls");
	}
	
	printf("Programa encerrado!\n");
	return 0;
}
// subprogramas

NO* criar_elemento(int dado, bool bitR) {
	NO* novoElemento = (NO*) malloc(sizeof(NO));
	if (novoElemento == NULL) {
		printf("Erro ao alocar mem�ria na cria��o de um novo elemento!\n");
		exit(1);
	}
	novoElemento->dado = dado;
	novoElemento->bitR = bitR;
	novoElemento->anterior = novoElemento;
	novoElemento->proximo = novoElemento;
	return novoElemento;
}

void inserir_elemento(NO** lista, int dado, bool bitR) {
	NO* novoElemento = criar_elemento(dado, bitR);
	if (*lista == NULL) {
		*lista = novoElemento;
	} else {		
		novoElemento->anterior = (*lista)->anterior;
		novoElemento->proximo = (*lista);
		(*lista)->anterior->proximo = novoElemento;
		(*lista)->anterior = novoElemento;
	}
}

void trocar_elementos(NO** lista1, NO** lista2) {
	if (*lista1 == NULL || *lista2 == NULL) {
		printf("Uma (ou as duas) lista est� vazia! N�o h� como trocar elementos!\n");
		return;
	}
	NO* temp1 = *lista1;
	NO* temp2 = *lista2;
	NO* aux = NULL;
	
	do {
		
		if (temp1->bitR == 1) {
			aux = temp1;
			temp1 = temp1->proximo;
			
			if (aux == *lista1) {
				*lista1 = temp1;
			}
			aux->anterior->proximo = aux->proximo;
			aux->proximo->anterior = aux->anterior;
			
			(*lista1)->anterior->proximo = aux;
			aux->anterior = (*lista1)->anterior;
			(*lista1)->anterior = aux;
			aux->proximo = *lista1;
			aux->bitR = 0;
			
			aux = NULL;
		} else { // bitR � igual 0; candidato a troca
			do {
				if (temp2->bitR == 0) {
					NO* ant = temp2->anterior;
					NO* prox = temp2->proximo;
					
					aux = temp2;
					
					temp1->anterior->proximo = temp2;
					temp1->proximo->anterior = temp2;
					temp2->anterior = temp1->anterior;
					temp2->proximo = temp1->proximo;
					temp2->bitR = 1;
					
					ant->proximo = temp1;
					prox->anterior = temp1;
					temp1->anterior = ant;
					temp1->proximo = prox;
					
					if (*lista1 == temp1) {
						*lista1 = temp2;
					}
					if (*lista2 == temp2) {
						*lista2 = temp1;
					}
					break;
				}
				
				temp2 = temp2->proximo;
			} while(temp2 != *lista2);
			break;
		}
	} while (temp1->proximo != *lista1);
}

void listar_elementos(NO* lista) {
	if (lista == NULL) {
		printf("Lista vazia!\n");
		return;
	}
	NO* aux = lista;
	printf("\nLista de Elementos [ Dado; BitR ]: \n");
	do {
		printf("[%d; %d] ", aux->dado, aux->bitR);
		aux = aux->proximo;
	} while(aux != lista);
	printf("\n");
}
