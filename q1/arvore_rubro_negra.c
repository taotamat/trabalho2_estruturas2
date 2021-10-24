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

INFO *alocaINFO(){
	INFO *novo;
	novo = (INFO *) malloc(sizeof(INFO));
	novo->lista_posicoes = NULL;
	novo->qnt_vezes = 1;
	return novo; }


NO *alocaNO(){
	NO *novo;
	novo = (NO *) malloc(sizeof(NO));
	novo->info = NULL;
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
		printf("RED    \n");
	else
		printf("BLACK  \n"); }

/*-------Apresentações---------*/

// Apresenta as posições que uma posição 
void apresentaLISTA(NO_LISTA *aux) {
	if(aux != NULL){
		printf("%d, ", aux->nmr_linha);
		apresentaLISTA(aux->prox);
	} }

void apresentaNO(NO *aux){
	ast();
	printf("%s - ", aux->info->palavra);
	apresentaCOR(aux->cor);
	printf("Esta palavra aparece %d vezes. \n", aux->info->qnt_vezes);
	printf("Linhas: \n");
	apresentaLISTA(aux->info->lista_posicoes->ini);
	printf("\n"); }

// Função que apresenta todos os NOs da árvore em Pré-Ordem
void preordem(NO *aux) {
	// Raiz, esquerda, direita;
	if(aux != NULL){
		apresentaNO(aux);
		preordem(aux->esq);
		preordem(aux->dir);
	} }

// Função que apresenta todos os NOs da árvore em IN-Ordem
void inordem(NO *aux) {
	// esquerda, Raiz, direita;
	if(aux != NULL){
		inordem(aux->esq);
		apresentaNO(aux);
		inordem(aux->dir);
	} }

// Função que apresenta todos os NOs da árvore em Pós-Ordem
void posordem(NO *aux) {
	// esquerda, direita, raiz;
	if(aux != NULL){
		posordem(aux->esq);
		posordem(aux->dir);
		apresentaNO(aux);
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
		comparacao = strcmp(novo->info->palavra, (*raiz)->info->palavra);

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
		insereLISTA( (*raiz)->info->lista_posicoes, novo->info->lista_posicoes->ini );
		(*raiz)->info->qnt_vezes = (*raiz)->info->qnt_vezes + 1;
		novo->info->lista_posicoes = NULL;
		free(novo);
	}

	gestaoBALANCEAMENTO(arvore, raiz); }


// Função que ler os dados do novo NO;
void ler(NO *no){
	printf("Digite uma string para o novo NO: ");
	scanf(" %[^\n]s", no->info->palavra);
	setbuf(stdin, NULL); }




// Função que aloca espaço para um novo NO e chama a função de leitura.
void gestaoINSERCAO(ARVORE *arvore, char *palavra, int linha, int ordem) {
	/*
	strcpy(string_destino, string_origem);
	Realiza a cópia do conteúdo de uma variável a outra.
	*/
	NO *novo;
	INFO *info;
	LISTA *lista;
	NO_LISTA *no_lista;

	novo = alocaNO();
	info = alocaINFO();
	lista = alocaLISTA();
	no_lista = alocaNO_LISTA();

	strcpy(info->palavra, palavra);

	no_lista->nmr_linha = linha;
	no_lista->nmr_ordem_linha = ordem;

	insereLISTA(lista, no_lista);
	info->lista_posicoes = lista;

	novo->info = info;

	inserir(arvore, &(arvore->raiz), novo); }



void gestaoLER(ARVORE *arvore){
	
	char palavra[101];
	int linha;
	int ordem;

	printf("Digite a palavra que deseja inserir: ");
	scanf(" %[^\n]s", palavra);
	setbuf(stdin, NULL);
	minusculo(palavra);

	printf("Digite a linha dessa palavra: ");
	scanf("%d", &linha);
	
	printf("Digite a ordem (numero inteiro) que essa palavra aparece na linha: ");
	scanf("%d", &ordem);

	gestaoINSERCAO(arvore, palavra, linha, ordem); }


// 
NO *buscar(NO *raiz, char *palavra, int *passos) {

	NO *encontrado;
	int comparacao;
	encontrado = NULL;

	if( raiz != NULL ){

		(*passos) = (*passos) + 1;
		comparacao = strcmp(raiz->info->palavra, palavra);

		if( comparacao == 0 ){
			encontrado = raiz;
		} else if( comparacao > 0 ) {
			encontrado = buscar(raiz->esq, palavra, passos);
		} else if( comparacao < 0 ){
			encontrado = buscar(raiz->dir, palavra, passos); }
	}

	return encontrado; }


void gestaoBUSCA(ARVORE *arvore){
	char palavra[101];
	NO *encontrado;
	int passos = 0;
	FILE *buscaARQ;
	clock_t tempo;

	printf("Digite a palavra que deseja buscar: ");
	scanf(" %[^\n]s", palavra);
	setbuf(stdin, NULL);
	minusculo(palavra);
	//
	buscaARQ = fopen("busca.csv", "a");
	tempo = clock();

	encontrado = buscar(arvore->raiz, palavra, &passos);
	
	// marcarTEMPO(FILE *arq, char *palavra, clock_t *tempo, int i, int caso, int *passos, char *foiENC)
	if(encontrado != NULL){
		printf("Palavra encontrada! \n\n");
		printf("Quantidade de passos para encontrar a palavra: %d \n", passos);
		apresentaNO(encontrado);
		marcarTEMPO(buscaARQ, palavra, &tempo, 0, 2, passos, "SIM");
	} else {
		printf("Esta palavra nao foi encontrada! \n");
		marcarTEMPO(buscaARQ, palavra, &tempo, 0, 2, passos, "NAO");
	}

	fclose(buscaARQ); }




















