#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "arvore_rubro_negra.h"
#include "ajusta_cor.h"
#include "arquivo.h"

#define RED 1
#define BLACK 0

// arquivo.c

// transforma todos os caracteres de uma string em MAIUSCULAS;
void maiusculo(char *palavra){
	int tam;
	tam = strlen(palavra)-1;
	while(tam >= 0){
		if( isalpha(palavra[tam]) != 0 )
			palavra[tam] = toupper(palavra[tam]);
		tam--;
	} }

// Função que ler o arquivo
void lerLINHA(FILE *arq, char *linha) {
	int aux = 0;
	int i = 0;
	char c;
	do{
		c = fgetc(arq);

		if( c == EOF || arq == NULL || c == '\n') {
			aux = 1;
			linha[i] = '\0';
		} else {
			linha[i] = c; // Todos os caracteres na linha deverão
			i++; }

	} while(aux == 0); }

// Função que ler o arquivo e manda para as funções de inserções.
	// Segue a ordem:
		// Ler uma linha.
		// O conteúdo é armazenado em linha.
void lerARQUIVO(FILE *arq, ARVORE *arvore){
	char linha[301];
	//     :)
}



// 
