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

// Função que insere os dados do tempo marcado no arquivo *arq.
void marcarTEMPO(FILE *arq, char *palavra, clock_t *tempo, int i){
	double total;
	double tempo_final;

	double mili;
	double seg;

	tempo_final = clock();
	total = tempo_final - *tempo;

	mili = total / CLOCKS_PER_SEC;
	seg = mili * 1000;

	fprintf(arq, "%d,%s,%lf,%lf\n", i, palavra, mili, seg); }

// Função que ler o arquivo e manda para as funções de inserções.
	// Segue a ordem:
		// Ler uma linha.
		// O conteúdo é armazenado em linha.
void lerARQUIVO(FILE *arq, ARVORE *arvore){
	
	char palavra[100];
	int trava = 0;
	char c;
	int i = 0;

	int linha = 0;
	int ordem = 1;

	FILE *insercaoARQ; // // Árquivo onde os resultados do teste de tempo serão salvos;
	clock_t tempo_total; // tempo total para ler do arquivo e inserir todas as palavras.
	clock_t tempo_palavra; // tempo para inserir tal palavra.

	insercaoARQ = fopen("insercao.csv", "w");
	fprintf(insercaoARQ, "nmr,palavra,milissegundos,segundos\n");

	tempo_total = clock();

	do{

		c = lerPALAVRA(arq, palavra, &linha, &ordem);
		minusculo(palavra);

		if( palavra[0] == '\0' ) {
			// Todo o arquivo foi lido e o laço de repetição deve ser interrompido;
			trava = 1;
		} else {
			i++;
			tempo_palavra = clock();
			gestaoINSERCAO(arvore, palavra, linha, ordem);
			marcarTEMPO(insercaoARQ, palavra, &tempo_palavra, i);
		}

		if(c == 10){
			linha++;}
		

	} while(trava == 0);


	fprintf(arq, "\n");

	marcarTEMPO(insercaoARQ, "TOTAL:", &tempo_total, 0);
	printf("Aquivo lido!\nTotal de Palavras inseridas = %d \n", i);
	fclose(insercaoARQ); }