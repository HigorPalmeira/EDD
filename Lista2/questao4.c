/*
	Autor: Higor Palmeira
	Descrição: Escreva um programa em C que implemente uma lista circular duplamente encadeada.
	1. Devem ser implementadas as funções de inserção, deleção e listagem da lista;
	2. A lista deve ser ordenada por um campo de sua escolha;
	3. Deve oferecer duas opções de listagem:
		1. Ordem crescente
		2. Ordem decrescente.
*/

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <locale.h>

// structs
typedef struct no {
	int conteudo;
	struct no* proximo;
	struct no* anterior;	
} NO;

// protótipos
NO* criar_elemento(int conteudo);
void inserir_elemento(NO** pont, int conteudo);
void listar_ordem_crescente(NO* pont);
void listar_ordem_decrescente(NO* pont);
int deletar_elemento(NO** pont, int conteudo);

// programa principal
int main() {
	setlocale(LC_ALL, "");
	NO* lista = NULL;
	int resp, conteudo;
	resp = 0;
	
	while(resp != 5) {
		printf("SELECIONE UMA DAS OPÇÕES ABAIXO:\n");
		printf("[ 1 ] Inserir valor \n[ 2 ] Listar valores (Ordem Crescente) \n[ 3 ] Listar valores (Ordem Decrescente) \n[ 4 ] Deletar valor \n[ 5 ] Sair\n");
		scanf("%d", &resp);
		fflush(stdin);
		system("cls");
		
		switch(resp) {
			case 1:
				printf("INSERIR VALOR\n");
				printf("Informe o valor a ser inserido: ");
				scanf("%d", &conteudo);
				fflush(stdin);
				inserir_elemento(&lista, conteudo);
				getchar();
				break;
				
			case 2:
				listar_ordem_crescente(lista);
				getchar();
				break;
				
			case 3:
				listar_ordem_decrescente(lista);
				getchar();
				break;
				
			case 4:
				printf("DELETAR VALOR\n");
				printf("Informe o valor a ser deletado: ");
				scanf("%d", &conteudo);
				fflush(stdin);
				
				switch(deletar_elemento(&lista, conteudo)) {
					case 0:
						printf("A lista está vazia! Não há valores a ser deletados.\n");
						break;
						
					case 1:
						printf("O valor informado foi deletado com sucesso!\n");
						break;
						
					case -1:
						printf("O valor informado não foi encontrado na lista!\n");
						break;
				}
				getchar();
				break;
		}
		
		system("cls");
	}
	
	printf("Programa encerrado!\n");
	return 0;
}
// subprogramas
NO* criar_elemento(int conteudo) {
	NO* novoElemento = (NO*) malloc(sizeof(NO));
	if (novoElemento == NULL) {
		printf("Erro na alocação de memória na criação de um elemento!\n");
		exit(1);
	}
	novoElemento->conteudo = conteudo;
	novoElemento->anterior = novoElemento;
	novoElemento->proximo = novoElemento;
	return novoElemento;
}

void inserir_elemento(NO** pont, int conteudo) {
	NO* novoElemento = criar_elemento(conteudo);
	
	if (*pont == NULL) {
		*pont = novoElemento;
	} else {
		NO* aux = *pont;
		do {
			
			if (conteudo <= aux->conteudo) {
				novoElemento->proximo = aux;
				novoElemento->anterior = aux->anterior;
				aux->anterior->proximo = novoElemento;
				aux->anterior = novoElemento;
				
				if (aux == *pont) {
					*pont = novoElemento;
				}
				break;
			}
			aux = aux->proximo;
		} while(aux != *pont);
		
		if (aux == *pont) {
			novoElemento->proximo = *pont;
			novoElemento->anterior = (*pont)->anterior;
			(*pont)->anterior->proximo = novoElemento;
			(*pont)->anterior = novoElemento;
		}
	}
}

void listar_ordem_crescente(NO* pont) {
	if (pont == NULL) {
		printf("Lista vazia!\n");
		return;
	}
	NO* aux = pont;
	printf("\nLista Ordem Crescente: \n");
	do {
		printf("%d ", aux->conteudo);
		aux = aux->proximo;
	} while(aux != pont);
	printf("\n");
}

void listar_ordem_decrescente(NO* pont) {
	if (pont == NULL) {
		printf("Lista  Vazia!\n");
	}
	NO* aux = pont->anterior;
	printf("\nLista Ordem Decrescente: \n");
	do {
		printf("%d ", aux->conteudo);
		aux = aux->anterior;
	} while(aux != pont->anterior);
	printf("\n");
}

int deletar_elemento(NO** pont, int conteudo) {
	if (*pont == NULL) {
		return 0;
	}
	
	NO* aux = *pont;
	
	if (aux->proximo == *pont && aux->anterior == *pont) {
		*pont = NULL;
		free(aux);
		return 1;
	}
	
	do {
		
		if (conteudo == aux->conteudo) {
			aux->proximo->anterior = aux->anterior;
			aux->anterior->proximo = aux->proximo;
			if (aux == *pont) {
				*pont = aux->proximo;
			}
			free(aux);
			return 1;
		}
		
		aux = aux->proximo;
	} while (aux != *pont);
	
	return -1;
}




