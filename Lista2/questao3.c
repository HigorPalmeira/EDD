/*
	Autor: Higor Palmeira
	Descrição: Implemente em C uma lista de tarefas ordenada por prioridade, 
	um número inteiro entre 1 e 1.000.000 definido no registro da tarefa. 
	Cada tarefa também deve ter um campo indicando se está concluída (sim ou não).
	O programa deve permitir:
		1. Inserir novas tarefas;
		2. Listar apenas as tarefas concluídas;
		3. Listar apenas as tarefas pendentes.
	As tarefas não podem ser excluídas enquanto o programa estiver em execução. 
	Você pode escolher se a lista será duplamente encadeada ou não.
*/

#include <stdio.h>
#include <malloc.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#define TAM 100

// structs
typedef struct no {
	char titulo[TAM];
	int status; // 0 - pendente // 1 - concluida
	int prioridade;
	struct no* proximo;
} TAREFA;

// protótipos
TAREFA* criar_tarefa(char titulo[TAM], int status, int prioridade);
void inserir_tarefa(TAREFA** lista, char titulo[TAM], int status, int prioridade);
void listar_tarefas(TAREFA* lista);
void listar_tarefas_pendentes(TAREFA* lista);
void listar_tarefas_concluidas(TAREFA* lista);
TAREFA* buscaSeqPrioridade(TAREFA* lista, int chave);

// programa principal
int main() {
	setlocale(LC_ALL, "");
	
	TAREFA* lista = NULL;
	char titulo[TAM];
	int status, prioridade, resp;
	resp = 0;
	
	while(resp != 5) {
		printf("SELECIONE UMA DAS OPÇÕES ABAIXO:\n");
		printf("[ 1 ] Inserir tarefa \n[ 2 ] Listar todas as tarefas \n[ 3 ] Listar tarefas concluídas \n[ 4 ] Listar tarefas pendentes \n[ 5 ] Sair \n");
		scanf("%d", &resp);
		fflush(stdin);
		
		switch(resp) {
			case 1:
				system("cls");
				printf("\tINSERIR TAREFA\n");
				printf("Informe o título da tarefa (com máx. 100 caracteres):\n");
				fgets(titulo, TAM, stdin);
				fflush(stdin);
				
				do {
					printf("Informe qual o status da tarefa [0-Pendente / 1-Concluída]: ");
					scanf("%d", &status);
					fflush(stdin);
					if (status != 0 && status != 1) {
						printf("==>>Informe um valor válido para o status, Pendente -> 0 ou Concluída -> 1.\n");
					}
				} while(status != 0 && status != 1); // persistir até que o usuário informe um dado válido
				
				do {
					printf("Informe a prioridade da tarefa (1 até 1000000): ");
					scanf("%d", &prioridade);
					fflush(stdin);
					if (prioridade < 1 || prioridade > 1000000) {
						printf("==>>Informe um valor válido para a prioridade, em um intervalo de 1 à 1000000.\n");
					}
				} while(prioridade < 1 || prioridade > 1000000);
				
				inserir_tarefa(&lista, titulo, status, prioridade);
				puts("Tarefa inserida com sucesso!");
				getchar();
				break;
			
			case 2:
				listar_tarefas(lista);
				getchar();
				break;
				
			case 3:
				listar_tarefas_concluidas(lista);
				getchar();
				break;
				
			case 4:
				listar_tarefas_pendentes(lista);
				getchar();
				break;
		}
		
		system("cls");
	}
	
	puts("Programa encerrado!");
	
	return 0;
}

// subprogramas

TAREFA* criar_tarefa(char titulo[TAM], int status, int prioridade) {
	TAREFA* novaTarefa = (TAREFA*) malloc(sizeof(TAREFA));
	if (novaTarefa == NULL) {
		puts("Erro na alocação de memória na criação de uma nova tarefa!");
		exit(1);
	}
	novaTarefa->prioridade = prioridade;
	novaTarefa->status = status;
	strcpy(novaTarefa->titulo, titulo);
	novaTarefa->proximo = NULL;
	return novaTarefa;
}

void inserir_tarefa(TAREFA** lista, char titulo[TAM], int status, int prioridade) {
	TAREFA* novaTarefa = criar_tarefa(titulo, status, prioridade);
	if (*lista == NULL) {
		*lista = novaTarefa;
	} else {
		TAREFA* aux = buscaSeqPrioridade(*lista, prioridade);
		if (aux != NULL) {
			novaTarefa->proximo = aux->proximo;
			aux->proximo = novaTarefa;
		} else {
			aux = *lista;
			if (aux->prioridade < novaTarefa->prioridade) {
				while(aux->proximo != NULL) { 
					if (aux->proximo->prioridade < novaTarefa->prioridade) {
						aux = aux->proximo;
					} else {
						break;
					}
				}
				novaTarefa->proximo = aux->proximo;
				aux->proximo = novaTarefa;
			} else {
				novaTarefa->proximo = *lista;
				*lista = novaTarefa;
			}
		}
	}
	
}

void listar_tarefas(TAREFA* lista) {
	TAREFA* aux = lista;
	printf("\n\tTAREFAS\n");
	if (aux == NULL) printf("Não há tarefas!\n");
	else {
		while(aux != NULL) {
			puts("==================================================");
			printf("Titulo: %s\n", aux->titulo);
			switch(aux->status) {
				case 0:
					printf("Status: Pendente\n");
					break;
					
				case 1:
					printf("Status: Concluida\n");
					break;
			}
			printf("Prioridade: %d\n", aux->prioridade);
			puts("==================================================");
			aux = aux->proximo;
		}
	}
	printf("\n");
}

void listar_tarefas_pendentes(TAREFA* lista) {
	TAREFA* aux = lista;
	printf("\n\tTAREFAS PENDENTES\n");
	if (aux == NULL) printf("Não há tarefas pendentes!\n");
	else {
		while(aux != NULL) {
			if (aux->status == 0) {
				printf("Titulo: %s\n", aux->titulo);
				printf("Status: Pendente\n");
				printf("Prioridade: %d\n", aux->prioridade);
			}
			aux = aux->proximo;
		}
	}
	printf("\n");
}

void listar_tarefas_concluidas(TAREFA* lista) {
	TAREFA* aux = lista;
	printf("\n\tTAREFAS CONCLUÍDAS\n");
	if (aux == NULL) printf("Não há tarefas concluídas!\n");
	else {
		while(aux != NULL) {
			if (aux->status == 1) {
				printf("Titulo: %s\n", aux->titulo);
				printf("Status: Concluida\n");
				printf("Prioridade: %d\n", aux->prioridade);
			}
			aux = aux->proximo;
		}
	}
	printf("\n");
}

TAREFA* buscaSeqPrioridade(TAREFA* lista, int chave) {
	TAREFA* temp = lista;
	TAREFA* aux = NULL; // pode retornar null se nao houver tarefa c/ 'chave' prioridade
	while (temp != NULL && temp->prioridade <= chave) {
		if (temp->prioridade == chave) {
			aux = temp;
		}
		temp = temp->proximo;
	}
	
	return aux;
}
