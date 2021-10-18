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
	novo->qnt_vezes = 1;
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
		printf(" | RED   ");
	else
		printf(" | BLACK "); }

/*-------Apresentações---------*/

// Função que apresenta todos os NOs da árvore em Pré-Ordem
void preordem(NO *aux) {
	// Raiz, esquerda, direita;
	if(aux != NULL){
		printf("%s ", aux->palavra);
		apresentaCOR(aux->cor);
		printf("\t| - %d vezes. \n", aux->qnt_vezes);
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
		printf("\t| %d vezes. \n", aux->qnt_vezes);
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
		printf("\t| %d vezes. \n", aux->qnt_vezes);
	} }

/*------- Inserção ---------*/
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

	} else if( comparacao < 0 && (*raiz)->esq == NULL ) {
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
		arvore->tam = arvore->tam + 1; 

	} else if(comparacao == 0){
		// Fazer a parte de igualdade.
		insereLISTA( (*raiz)->lista_posicoes, novo->lista_posicoes->ini );
		(*raiz)->qnt_vezes = (*raiz)->qnt_vezes + 1;
		novo->lista_posicoes = NULL;
		free(novo);
	}

	gestaoBALANCEAMENTO(arvore, raiz); }


// Função que ler os dados do novo NO;
void ler(NO *no){
	printf("Digite uma string para o novo NO: ");
	scanf(" %[^\n]s", (*no).palavra);
	setbuf(stdin, NULL); }

// Função que aloca espaço para um novo NO e chama a função de leitura.
void gestaoINSERCAO(ARVORE *arvore, char *palavra, int linha, int ordem) {
	/*
	strcpy(string_destino, string_origem);
	Realiza a cópia do conteúdo de uma variável a outra.
	*/
	NO *novo;
	LISTA *lista;
	NO_LISTA *no_lista;

	novo = alocaNO();
	lista = alocaLISTA();
	no_lista = alocaNO_LISTA();

	strcpy(novo->palavra, palavra);

	no_lista->nmr_linha = linha;
	no_lista->nmr_ordem_linha = ordem;

	insereLISTA(lista, no_lista);
	novo->lista_posicoes = lista;

	inserir(arvore, &(arvore->raiz), novo); }



