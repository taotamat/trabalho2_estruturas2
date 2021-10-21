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


// Função que retorna a quantidade de filhos que o NO possui.
int qnt_filhos(NO *aux) {
	// retorna a quantidade de filhos que o NO aux possui;
	int qnt;
	if( aux->esq != NULL && aux->dir != NULL )
		qnt = 2;
	else if( aux->esq == NULL && aux->dir == NULL  )
		qnt = 0;
	else
		qnt = 1;
	return qnt; }

// Remover um NO que possui 1 filho.
	// Ele realiza a troca dos valores
	// E em seguida remove a folha;
NO *remove_pai_um(NO *raiz){
	
	NO *aux;
	INFO *copia;

	if( raiz->esq != NULL )
		aux = raiz->esq;
	else
		aux = raiz->dir;

	copia = raiz->info;
	raiz->info = aux->info;
	aux->info = copia;

	raiz->esq = aux->esq;
	raiz->dir = aux->dir;

	free(aux);
	aux = NULL;

	return raiz; }


// Função que retorna o NO que possui o maior valor que se encontra na esquerda do NO aux;
NO *maior_da_esquerda(NO *aux){
	
	NO *resultado;
	resultado = NULL;

	if( aux != NULL ){
		if( aux->dir == NULL )
			resultado = aux;
		else
			resultado = maior_da_esquerda(aux->dir); }

	return resultado; }


// Função que remove um NO que possui dois filhos;
void remove_com_dois_filhos(NO **raiz){
	
	NO *no;
	INFO *info;
	
	no = maior_da_esquerda( (*raiz)->esq );

	if( no != NULL ) {

		/* Troca dos dados */
		info = (*raiz)->info;
		(*raiz)->info = no->info;
		no->info = info;

		(*raiz)->esq = no->esq;
		no->esq = NULL;

		free(no);
	} }


// Função que chama as funções de remover
void remover(ARVORE *arvore, NO **raiz, char *valor){
	
	NO *aux;
	int qnt;
	int resultado = 0;
	int comparacao;

	if(*raiz != NULL)
		comparacao = strcmp((*raiz)->info->palavra, valor);;

	if( *raiz == NULL ){
		// raiz é nula. o valor não foi encontrado.
		printf("Valor não foi encontrado! \n");
		// aux = NULL;
	} else if( comparacao == 0 ){
		// é o mesmo valor!
		qnt = qnt_filhos(*raiz);

		if(qnt == 0){
			free(*raiz);
			*raiz = NULL;
		} else if(qnt == 1)
			*raiz = remove_pai_um(*raiz);
		else
			remove_com_dois_filhos(raiz);
		
		arvore->tam = arvore->tam - 1;
		printf("Removido! \n");

	} else if( comparacao > 0  ) {
		remover(arvore, &(*raiz)->esq, valor);
	} else if( comparacao < 0  ) {
		remover(arvore, &(*raiz)->dir, valor); } 

	gestaoBALANCEAMENTO(arvore, raiz); }


// Função que chama ler o valor a ser removido e chama a remoção
void gestaoREMOVER(ARVORE *arvore){

	char palavra[101];

	printf("Digite a palavra que deseja remover: ");
	scanf(" %[^\n]s", palavra);
	setbuf(stdin, NULL);
	minusculo(palavra);

	remover(arvore, &arvore->raiz, palavra); }