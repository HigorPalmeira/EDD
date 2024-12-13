/*
	Autor: Higor Palmeira
	Descrição: Escreva um programa em C que permita a criação de uma lista encadeada 
	utilizando alocação de memória dinâmica. 
	Implemente as funções de inserção, deleção e exibição de itens da lista.
*/
#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <stdlib.h>

// structs
typedef struct aux {
	int conteudo;
	struct aux *proxima;
} LISTA;

// subprogramas

LISTA* criarElemento(int conteudo) {
	LISTA* novoElemento = (LISTA*) malloc(sizeof(LISTA));
	novoElemento->conteudo = conteudo;
	novoElemento->proxima = NULL;
	return novoElemento;
}

void inserirElemento(LISTA** inicio, int conteudo) {
	LISTA* novoElemento = criarElemento(conteudo);
	novoElemento->proxima = *inicio;
	*inicio = novoElemento;
}

void deletarElemento(LISTA** elemento) {
	if (*elemento != NULL) {
		LISTA* aux = *elemento;
		*elemento = (*elemento)->proxima;
		free(aux);
	}
}

void listarElementos(LISTA* lista) {
	LISTA* aux = lista;
	printf("\nLISTA DE ELEMENTOS: \n");
	while(aux != NULL) {
		printf("%d ", aux->conteudo);
		aux = aux->proxima;
	}
	printf("\n");
}

// programa principal
int main() {
	setlocale(LC_ALL, "");
	
	LISTA* lista = NULL;
	int resp = 0;
	int v;
	
	while (resp != 4) {
		printf("SELECIONE UMA DAS OPÇÕES ABAIXO:\n");
		printf("[ 1 ] Inserir um elemento \n[ 2 ] Deletar um elemento \n[ 3 ] Listar todos os elementos \n[ 4 ] SAIR\n");
		scanf("%d", &resp);
		fflush(stdin);
		
		switch(resp) {
			case 1:
				printf("Informe o valor a ser inserido: ");
				scanf("%d", &v);
				fflush(stdin);
				inserirElemento(&lista, v);
				printf("\n\nElemento inserido com sucesso!");
				getchar();
				break;
				
			case 2:
				deletarElemento(&lista);
				printf("\n\nElemento deletado com sucesso!");
				getchar();
				break;
				
			case 3:
				listarElementos(lista);
				getchar();
				break;
		}
		
		system("cls");
	}
	
	printf("O programa foi encerrado!");
		
	return 0;
}
