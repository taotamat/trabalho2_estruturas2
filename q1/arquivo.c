#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <locale.h>
#include "arvore_rubro_negra.h"
#include "ajusta_cor.h"
#include "arquivo.h"
#include "remocao.h"

#define RED 1
#define BLACK 0

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
	return aceito;
}

// Função que ler o arquivo
void lerPALAVRA(FILE *arq, char *palavra, int *linha, int *ordem) {
	
	int trava = 0;
	int i = 0;
	char c;

	do{
		c = fgetc(arq);

		if( c == EOF || arq == NULL || c == '\n' || c == ' ' ) {
			
			trava = 1;
			palavra[i] = '\0';

			if( c == ' ' ){
				*ordem = *ordem + 1;

			} else if( c == '\n' ){
				*ordem = 1;
				*linha = *linha + 1;
			}
		
		} else {

			if(tratarCARACTER(&c) == 1){
				palavra[i] = c; // Todos os caracteres na linha deverão
				i++; }
		}


	} while(trava == 0); }


// Função que ler o arquivo e manda para as funções de inserções.
	// Segue a ordem:
		// Ler uma linha.
		// O conteúdo é armazenado em linha.
void lerARQUIVO(FILE *arq, ARVORE *arvore){
	
	char palavra[100];
	int trava = 0;

	int linha = 0;
	int ordem = 1;


	do{

		lerPALAVRA(arq, palavra, &linha, &ordem);
		minusculo(palavra);

		if( palavra[0] == '\0' ) {
			// Todo o arquivo foi lido e o laço de repetição deve ser interrompido;
			trava = 1;
		} else {
			gestaoINSERCAO(arvore, palavra, linha, ordem);
		}

	} while(trava == 0);

	printf("Aquivo lido!\n");

}



// 
