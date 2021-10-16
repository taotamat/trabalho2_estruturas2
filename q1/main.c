#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "arvore_rubro_negra.h"
#include "ajusta_cor.h"
#include "arquivo.h"

/*
	
	Enunciado da questão:
	

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
	
	printf("[1] - Inserir uma nova palavra  \n");
	printf("[2] - Apresentacao em pre-ordem \n");
	printf("[3] - Apresentacao em in-ordem  \n");
	printf("[4] - Apresentacao em pos-ordem \n");
	printf("[5] - Opcao 5\n");
	printf("[6] - Opcao 6\n");
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

	int op;
	ARVORE *arvore;

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
				// FUNÇÃO TAL
				gestaoLER(arvore);
				break;

			case 2:
				// FUNÇÃO TAL
				preordem(arvore->raiz);
				break;

			case 3:
				// FUNÇÃO TAL
				inordem(arvore->raiz);
				break;

			case 4:
				// FUNÇÃO TAL
				posordem(arvore->raiz);
				break;

			case 5:
				// FUNÇÃO TAL
				break;

			case 6:
				// FUNÇÃO TAL
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