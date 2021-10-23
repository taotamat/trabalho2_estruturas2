#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <locale.h>
#include "arvore23.h"
#include "arquivo.h"
#include "insercao.h"

// arvore23.c

void ast(){

	printf("-------------------------------------------------------------\n"); }


/*----------------------Alocações----------------------*/

NO_LISTA *alocaNO_LISTA(){
	NO_LISTA *novo;
	novo = (NO_LISTA *) malloc(sizeof(NO_LISTA));
	novo->prox = NULL;
	novo->nmr_linha = 1;
	novo->nmr_ordem_linha = 1;
	return novo; }

LISTA *alocaLISTA(){
	LISTA *nova;
	nova = (LISTA *) malloc(sizeof(LISTA));
	nova->ini = NULL;
	nova->fim = NULL;
	return nova; }

INFO *alocaINFO(){
	INFO *novo;
	novo = (INFO *) malloc(sizeof(INFO));
	novo->lista_posicoes = NULL;
	novo->qnt_vezes = 1;
	return novo; }

NO *alocaNO(){
	NO *novo;
	novo = (NO *) malloc(sizeof(NO));
	novo->info1 = NULL;
	novo->info2 = NULL;
	novo->esq = NULL;
	novo->cen = NULL;
	novo->dir = NULL;
	return novo; }

ARVORE *alocaARV(){
	ARVORE *nova;
	nova = (ARVORE *) malloc(sizeof(ARVORE));
	nova->tam = 0;
	nova->raiz = NULL;
	return nova; }

/*----------------------Apresentações----------------------*/

// Apresenta as posições que uma posição 
void apresentaLISTA(NO_LISTA *aux) {
	if(aux != NULL){
		printf("%d, ", aux->nmr_linha);
		apresentaLISTA(aux->prox);
	} }

void apresentaINFO(INFO *info){
	if( info != NULL ) {
		ast();
		printf("%s - ", info->palavra);
		printf("Esta palavra aparece %d vezes. \n", info->qnt_vezes);
		printf("Linhas: \n");
		apresentaLISTA(info->lista_posicoes->ini);
		printf("\n");
	} }

// Função que apresenta todos os NOs da árvore em Pré-Ordem
void preordem(NO *aux) {
	// Raiz, esquerda, direita;
	if(aux != NULL){
		apresentaINFO(aux->info1);
		apresentaINFO(aux->info2);
		printf("\n\n");
		preordem(aux->esq);
		preordem(aux->cen);
		preordem(aux->dir);
	} }

// Função que apresenta todos os NOs da árvore em IN-Ordem
void inordem(NO *aux) {
	// esquerda, Raiz, direita;
	if(aux != NULL){
		inordem(aux->esq);
		apresentaINFO(aux->info1);
		printf("\n");
		inordem(aux->cen);
		apresentaINFO(aux->info2);
		inordem(aux->dir);
	} }

// Função que apresenta todos os NOs da árvore em Pós-Ordem
void posordem(NO *aux) {
	// esquerda, direita, raiz;
	if(aux != NULL){
		posordem(aux->esq);
		posordem(aux->cen);
		posordem(aux->dir);
		apresentaINFO(aux->info1);
		apresentaINFO(aux->info2);
	} }

/* ----------------------------------- FUNÇÕES BÁSICAS ----------------------------------- */

// Função que devolve a quantidade de filhos que o Nó possui;
int qntFILHOS(NO *no){
	
	int qnt = 0;

	if(no->esq != NULL)
		qnt++;

	if(no->cen != NULL)
		qnt++;

	if(no->dir != NULL)
		qnt++;

	return qnt; }

// Função que devolve a quantidade de informações presentes no Nó
int qntINFO(NO *no) {

	int qnt = 0;

	if( no->info1 != NULL )
		qnt++;

	if( no->info2 != NULL )
		qnt++;

	return qnt; }

// Função que ajusta o número de filhos e informações que um Nó possui
NO *ajustaNMRS(NO *no){
	no->nmrINFO = qntINFO(no);
	no->nmrFILHOS = qntFILHOS(no);
	return no; }

// Função que verifica se a LISTA está vazia.
	// retorna 0 caso NÃO esteja vazia.
	// retorna 1 caso SIM estaja vazia.
int vazia(LISTA *lista){
	int vazia = 0;
	if( (*lista).ini == NULL ){
		vazia = 1; }
	return vazia; }

// Inserir na lista
void insereLISTA(LISTA *lista, NO_LISTA *no){

	int trava = 0;
	NO_LISTA *ant, *aux;

	if( vazia(lista) == 1 ){ // Se a Lista tá vazia
		// No vai ser o primeiro e o último item da lista;
		(*lista).ini = no;
		(*lista).fim = no;

	} else if( (*no).nmr_linha < lista->ini->nmr_linha ){ // Se o novo elemento tem que ficar na primeira posição.

		(*no).prox = (*lista).ini;
		(*lista).ini = no;


	} else if( (*no).nmr_linha > lista->fim->nmr_linha ){ // Se a info do no for maior que a do último item da lista

		lista->fim->prox = no;
		(*lista).fim = no;

	} else { // Se ele tem que ir para o meio da fila

		aux = lista->ini;
		ant = NULL;

		while( aux != NULL){


			if(trava == 0){

				if( (*no).nmr_linha < aux->nmr_linha  ) {
					// Informação do no é menor ou igual a informação de aux;

					(*ant).prox = no; // O proximo do anterior recebe o endereço do novo elemento.
					(*no).prox = aux; // O proximo do novo elemento recebe o endereço do elemento aux.
					trava = 1; 		  // Trava recebe 1 e evita que outras comparações sejam feitas;
				}
			}

			ant = aux;
			aux = (*aux).prox;
		}
	} }

/* ----------------------------------- FUNÇÕES ARVORES ----------------------------------- */

INFO *buscar(NO *raiz, char *palavra, int *passos){

	INFO *encontrado;
	int c = -2;
	int comparacao1 = -2, comparacao2 = -2;
	encontrado = NULL;

	if( raiz != NULL ){

		c = temIGUAL(&raiz, palavra);

		if( c != 0 ){
			// A raiz possui a palavra buscada!
			if( c == 1 )
				encontrado = raiz->info1;
			else
				encontrado = raiz->info2;

		} else {

			comparar(&raiz, palavra, &comparacao1, &comparacao2);
			*passos = *passos + 1;

			if( comparacao1 == -1 ) {
				// foi pra esquerda
				encontrado = buscar(raiz->esq, palavra, passos);
			} else if( ( comparacao1 == 1 && raiz->nmrINFO == 1) || comparacao2 == -1 ) {
				// foi pro centro
				encontrado = buscar(raiz->cen, palavra, passos);
			} else if( comparacao2 == 1 ) {
				// foi pra direita
				encontrado = buscar(raiz->dir, palavra, passos);
			}
		}
	}
	return encontrado; }



void gestaoBUSCA(ARVORE *arvore){
	
	char palavra[101];
	INFO *encontrado;
	int passos = 0;

	printf("Digite a palavra que deseja buscar: ");
	scanf(" %[^\n]s", palavra);
	setbuf(stdin, NULL);
	minusculo(palavra);
	//

	encontrado = buscar(arvore->raiz, palavra, &passos);
	
	if(encontrado != NULL){
		printf("Palavra encontrada! \n\n");
		printf("Quantidade de passos para encontrar a palavra: %d \n", passos);
		apresentaINFO(encontrado);
	} else 
		printf("Esta palavra nao foi encontrada! \n"); }



