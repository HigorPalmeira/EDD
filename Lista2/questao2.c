/*
	Autor: Higor Palmeira
	Descrição: Escreva um programa em C que permita a criação de uma 
	lista duplamente encadeada utilizando alocação de memória dinâmica. 
	Implemente as funções de inserção, deleção e exibição de itens da lista.
*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>

// structs

typedef struct no {
	int conteudo;
	struct no* anterior;
	struct no* proximo;
} NO;

//
NO* criar_elemento(int conteudo);
void adicionar_elemento_inicio(NO** inicio, int conteudo);
void adicionar_elemento_final(NO** inicio, int conteudo);
void deletar_elemento_inicio(NO** elemento);
void deletar_elemento_final(NO** lista);
void listar_elementos_inicio(NO* lista);
void listar_elementos_fim(NO* lista);

// programa principal
int main() {
	setlocale(LC_ALL, "");

	NO* lista = NULL;
	int resp = 0;
	int v;
	
	while(resp!=7) {
		printf("\n\tSELECIONE UMA DAS OPÇÕES ABAIXO:\n");
		printf("\t[ 1 ] Adicionar um elemento no início da lista \n\t[ 2 ] Adicionar um elemento no final da lista \n\t[ 3 ] Deletar elemento no início da lista \n\t[ 4 ] Deletar elemento no final da lista \n\t[ 5 ] Listar elementos da lista (INÍCIO-->FIM) \n\t[ 6 ] Listar elementos da lista (FIM-->INÍCIO) \n\t[ 7 ] SAIR \n\t>> ");
		scanf("%d", &resp);
		fflush(stdin);
		
		switch(resp) {
			case 1:
				printf("Informe o valor a ser adicionado: ");
				scanf("%d", &v);
				fflush(stdin);
				adicionar_elemento_inicio(&lista, v);
				
				printf("Elemento adicionado com sucesso!");
				getchar();
				break;
				
			case 2:
				printf("Informe o valor a ser adicionado: ");
				scanf("%d", &v);
				fflush(stdin);
				adicionar_elemento_final(&lista, v);
				
				printf("Elemento adicionado com sucesso!");
				getchar();
				break;
				
			case 3:
				deletar_elemento_inicio(&lista);
				
				printf("Elemento removido com sucesso!");
				getchar();
				break;
				
			case 4:
				deletar_elemento_final(&lista);
				
				printf("Elemento removido com sucesso!");
				getchar();
				break;
				
			case 5:
				listar_elementos_inicio(lista);
				getchar();
				break;
				
			case 6:
				listar_elementos_fim(lista);
				getchar();
				break;
		}	
		
		system("cls");
	}
	printf("Programa encerrado!");
	
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
	novoElemento->anterior = NULL;
	novoElemento->proximo = NULL;
	return novoElemento;
}

void adicionar_elemento_inicio(NO** inicio, int conteudo) {
	NO* novoElemento = criar_elemento(conteudo);
	novoElemento->proximo = *inicio;
	if (*inicio != NULL) {
		(*inicio)->anterior = novoElemento;
	}
	*inicio = novoElemento;
}

void adicionar_elemento_final(NO** inicio, int conteudo) {
	NO* novoElemento = criar_elemento(conteudo);
	if (*inicio == NULL) {
		*inicio = novoElemento;
	} else {
		NO* aux = *inicio;
		while(aux->proximo != NULL) {
			aux = aux->proximo;
		}
		
		aux->proximo = novoElemento;
		novoElemento->anterior = aux;
	}
}

void deletar_elemento_inicio(NO** elemento) {
	if (*elemento != NULL) {
		NO* temp = *elemento;
		*elemento = (*elemento)->proximo;
		if (*elemento != NULL) {
			(*elemento)->anterior = NULL;
		}
		free(temp);
	}
}

void deletar_elemento_final(NO** lista) {
	if (*lista != NULL) {
		NO* temp = *lista;
		NO* aux = temp;
		while(temp->proximo != NULL) {
			aux = temp;
			temp = temp->proximo;
		}
		
		aux->proximo = NULL;
		free(temp);
	}
}

void listar_elementos_inicio(NO* lista) {
	NO* aux = lista;
	printf("\nLISTA DE ELEMENTOS INÍCIO-->FIM\n");
	while(aux != NULL) {
		printf("%d ", aux->conteudo);
		aux = aux->proximo;
	}
	printf("\n");
	
}

void listar_elementos_fim(NO* lista) {
	NO* aux = lista;
	printf("\nLISTA DE ELEMENTOS FIM-->INÍCIO\n");
	while(aux->proximo != NULL) {
		aux = aux->proximo;
	}
	
	while(aux != NULL) {
		printf("%d ", aux->conteudo);
		aux = aux->anterior;
	}
	printf("\n");
}

