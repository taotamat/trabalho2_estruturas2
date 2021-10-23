#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <locale.h>
#include "arvore23.h"
#include "arquivo.h"
#include "insercao.h"

// arquivo.c

// transforma todos os caracteres de uma string em MINUSCULAS;
void minusculo(char *palavra){
	int tam;
	tam = strlen(palavra)-1;
	while(tam >= 0){
		if( isalpha(palavra[tam]) != 0 )
			palavra[tam] = tolower(palavra[tam]);
		tam--;
	} }

// Função que verifica se a variavel é aceitavel
	// A função verifica se o caractere é um caracter especial
	// A função verifica se o caractere é um número
	// A função verifica se o caractere é uma letra
		// CASO SEJA UMA LETRA:
		// A função verifica se a letra possue acento com a função temACENTO(char c);
int tratarCARACTER(char *c) {
	// Função retorna 1 se for aceito e 0 se NÃO for aceito.
	int aceito;
	if( ispunct(*c) != 0 || isdigit(*c) != 0){
		// Caractere é um caractere especial.
		aceito = 0;
	} else {
		//*c = temACENTO(c);
		aceito = 1;
	}

	return aceito; }

// Função que ler o arquivo
char lerPALAVRA(FILE *arq, char *palavra, int *linha, int *ordem) {
	
	int trava = 0;
	int i = 0;
	char c;

	do{
		c = fgetc(arq);
		if( c == EOF || arq == NULL || c == '\n' || c == 32) {			
			trava = 1;
			palavra[i] = '\0';
		} else {
			if(tratarCARACTER(&c) == 1){
				palavra[i] = c; // Todos os caracteres na linha deverão
				i++; 
			}
		}
	} while(trava == 0);
	
	return c; }

// Função que ler o arquivo e manda para as funções de inserções.
	// Segue a ordem:
		// Ler uma linha.
		// O conteúdo é armazenado em linha.
void lerARQUIVO(FILE *arq, ARVORE *arvore){
	
	char palavra[100];
	int trava = 0;

	int linha = 1;
	int ordem = 1;

	char c;

	do{

		c = lerPALAVRA(arq, palavra, &linha, &ordem);
		minusculo(palavra);

		if( palavra[0] == '\0' ) {
			// Todo o arquivo foi lido e o laço de repetição deve ser interrompido;
			trava = 1;
		} else {
			gestaoINSERCAO(arvore, palavra, linha, ordem);
		}

		if(c == 10){
			linha++;}

	} while(trava == 0);

	printf("Aquivo lido!\n"); }