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

void ast(){

	printf("-------------------------------------------------------------\n"); }


/*-------Alocações---------*/

NO_LISTA *alocaNO_LISTA(){
	NO_LISTA *novo;
	novo = (NO_LISTA *) malloc(sizeof(NO_LISTA));
	novo->ant = NULL;
	novo->prox = NULL;
	return novo; }

LISTA *alocaLISTA(){
	LISTA *nova;
	nova = (LISTA *) malloc(sizeof(LISTA));
	nova->ini = NULL;
	nova->fim = NULL;
	return nova; }

NO *alocaNO(){
	NO *novo;
	novo = (NO *) malloc(sizeof(NO));
	novo->lista_posicoes = NULL;
	novo->qnt_vezes = 0;
	novo->esq = NULL;
	novo->dir = NULL;
	novo->cor = RED;
	return novo; }

ARVORE *alocaARV(){
	ARVORE *nova;
	nova = (ARVORE *) malloc(sizeof(ARVORE));
	nova->tam = 0;
	nova->raiz = NULL;
	return nova; }

/*-------Gestão básica das CORES---------*/

int cor(NO *H){
	int resultado;
    if(H == NULL)
        resultado = BLACK;
    else
        resultado = H->cor; 
    return resultado; }

void trocaCor(NO *H){
    H->cor = !H->cor;
    if(H->esq != NULL)
        H->esq->cor = !H->esq->cor;
    if(H->dir != NULL)
        H->dir->cor = !H->dir->cor; }

void apresentaCOR(int cor){
	if(cor == RED)
		printf("- \tVERMELHO     |\n");
	else
		printf("- \tPRETO        |\n"); }

/*-------Apresentações---------*/

// Função que apresenta todos os NOs da árvore em Pré-Ordem
void preordem(NO *aux) {
	// Raiz, esquerda, direita;
	if(aux != NULL){
		printf("%s ", aux->palavra);
		apresentaCOR(aux->cor);
		preordem(aux->esq);
		preordem(aux->dir);
	} }

// Função que apresenta todos os NOs da árvore em IN-Ordem
void inordem(NO *aux) {
	// esquerda, Raiz, direita;
	if(aux != NULL){
		inordem(aux->esq);
		printf("%s ", aux->palavra);
		apresentaCOR(aux->cor);
		inordem(aux->dir);
	} }

// Função que apresenta todos os NOs da árvore em Pós-Ordem
void posordem(NO *aux) {
	// esquerda, direita, raiz;
	if(aux != NULL){
		posordem(aux->esq);
		posordem(aux->dir);
		printf("%s ", aux->palavra);
		apresentaCOR(aux->cor);
	} }

/*------- Inserção ---------*/

// Função recursiva que insere o novo NO na árvore.
void inserir(ARVORE *arvore, NO **raiz, NO *novo) {

	/*
	strcmp:
	0: conteúdo das strings são iguais
	< 0: conteúdo da string1 é menor do que string2
	> 0: conteúdo da string1 é maior do que string2

	*/

	int comparacao;

	if(*raiz != NULL)
		comparacao = strcmp(novo->palavra, (*raiz)->palavra);

	if( *raiz == NULL ){
		// arvore não possue uma raiz, então o novo é a nova raiz.
		*raiz = novo;
		arvore->tam = arvore->tam + 1;

	} else if( comparacao < 0 && (*raiz)->esq != NULL ) {
		// Se o dado de novo NO for menor e o filho esquerdo do NO aux NÃO FOR NULL, 
		// Então o novo NO vai ser comparado ao filho esquerdo do NO aux.
		inserir(arvore, &((*raiz)->esq), novo);

	} else if( comparacao <= 0 && (*raiz)->esq == NULL ) {
		// Se o dado de novo NO for menor e o filho esquerdo do NO aux FOR NULL, 
		// Então o novo NO será o novo filho esquerdo do NO aux.
		(*raiz)->esq = novo;
		arvore->tam = arvore->tam + 1;

	} else if( comparacao > 0 && (*raiz)->dir != NULL ) {
		// Se o dado de novo NO for maior e o filho direito do NO aux NÃO FOR NULL, 
		// Então o novo NO vai ser comparado ao filho direito do NO aux.
		inserir(arvore, &((*raiz)->dir), novo);

	} else if( comparacao > 0 && (*raiz)->dir == NULL ) {
		// Se o dado de novo NO for maior e o filho direito do NO aux FOR NULL, 
		// Então o novo NO será o novo filho direito do NO aux.
		(*raiz)->dir = novo;
		arvore->tam = arvore->tam + 1; }

	gestaoBALANCEAMENTO(arvore, raiz); }


// Função que ler os dados do novo NO;
void ler(NO *no){
	printf("Digite uma string para o novo NO: ");
	scanf(" %[^\n]s", (*no).palavra);
	setbuf(stdin, NULL); }

// Função que aloca espaço para um novo NO e chama a função de leitura.
void gestaoLER(ARVORE *arvore) {
	NO *novo;
	novo = alocaNO();
	ler(novo);
	maiusculo((*novo).palavra);
	inserir(arvore, &(arvore->raiz), novo); }



