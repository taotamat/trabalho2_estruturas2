#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <ctype.h>
#include "arvore_rubro_negra.h"
#include "ajusta_cor.h"
#include "arquivo.h"
#include "remocao.h"

/*
	
	Enunciado da questão:
	Faça um programa em C de referência cruzada que construa uma árvore binária de busca
	vermelha-preta, com:
	[OK] - todas as palavras incluídas a partir de um arquivo texto, 
	[OK] - e armazene o número de cada linha em que a palavra foi usada. 
	[OK] - Os números das linhas devem ser armazenados em uma lista encadeada associada ao nó da árvore. 
	[OK] - Depois do arquivo de entrada ter sido processado, imprima em ordem alfabética todas as palavras do arquivo texto, 
	[OK] - junto com os números das linhas onde foi usada. 

	[OK] - O programa deve permitir o usuário buscar uma palavra 
	[OK] - e o programa deve responder em quais linhas do texto ela foi utilizada, 
	[OK] - para cada palavra buscada mostre o número de passos até alcançar a palavra na árvore. 
	[OK] - Além disso, ele deve permitir excluir uma palavra de uma linha 
	[OK] - bem como acrescentar.

*/

//----------------------------------------------------------//
// Menu Principal:

int menu(){

	// FUNÇÃO QUE APRESENTA UM MENU.

	int op;
	printf("\n\n");
	
	ast();
	printf("\t\t\tMENU PRINCIPAL:\n");
	ast();
	
	printf("[1] - Ler o arquivo             \n");
	printf("[2] - Apresentacao em pre-ordem \n");
	printf("[3] - Apresentacao em in-ordem  \n");
	printf("[4] - Apresentacao em pos-ordem \n");
	printf("[5] - Buscar uma palavra        \n");
	printf("[6] - Inserir uma nova palavra  \n");
	printf("[7] - Remover uma palavra       \n");
	printf("[0] - Sair\n");

	ast();
	printf("SELECIONE A OPCAO DE DESEJADA: ");
	scanf("%d", &op);
	ast();

	printf("\n\n");

	return op; }

//----------------------------------------------------------//
// FUNÇÃO MAIN:

int main(){

	setlocale(LC_ALL, "Portuguese");

	int op;
	ARVORE *arvore;
	FILE *arq;

	arq = fopen("arquivo2.txt", "r");
	arvore = alocaARV();

	do{

		op = menu();

		switch(op){

			case 0:
				// ENCERRAR O PROGRAMA;
				ast();
				printf("\t\tPrograma encerrado!\n");
				ast();
				break;

			case 1:
				// FUNÇÃO que ler o arquivo e insere todas as palavras na árvore.
				lerARQUIVO(arq, arvore);
				break;

			case 2:
				// FUNÇÃO que apresenta as palavras na árvore em pré-ordem
				preordem(arvore->raiz);
				break;

			case 3:
				// FUNÇÃO que apresenta as palavras na árvore em in-ordem
				inordem(arvore->raiz);
				break;

			case 4:
				// FUNÇÃO que apresenta as palavras na árvore em pós-ordem
				posordem(arvore->raiz);
				break;

			case 5:
				// FUNÇÃO que busca uma palavra na árvore.
				gestaoBUSCA(arvore);
				break;

			case 6:
				// FUNÇÃO que insere uma nova palavra na árvore.
				gestaoLER(arvore);
				break;

			case 7:
				// FUNÇÃO que remove uma palavra da árvore
				gestaoREMOVER(arvore);
				break;

			default:
				// MENSAGEM DE ERRO
				ast();
				printf("Valor inválido, digite novamente:\n");
				ast();
				break;

		}

	} while(op != 0);




	return 0; }


/*

Adicionais:	

	Compilar e executar:
		gcc nomedoprograma.c -o nomedoprograma -lm && ./nomedoprograma
	
	Ler uma string que contenha espaços e limpeza de buffer:
		scanf(" %[^\n]s", (*carro).chassi);
		setbuf(stdin, NULL);
	


*/