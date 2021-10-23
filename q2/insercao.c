#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <locale.h>
#include "arvore23.h"
#include "arquivo.h"
#include "insercao.h"

// insercao.c
// funcoes destinadas a realizar a inserção de uma informação na árvore.

// comparacao1 e comparacao2 recebem 0 qnd as duas strings são iguais.
// comparacao1 e comparacao2 recebem -1 qnd a string da nova info é menor que a info da raiz
// comparacao1 e comparacao2 recebem 1 qnd a string da nova info é maior que a info da raiz.
void comparar(NO **raiz, INFO **info, int *comparacao1, int *comparacao2){
	
	/*
	strcmp:
	se Return value < 0 então indica str1 é menor que str2.
	se Return value > 0 então indica str2 é menor que str1. */

	if( (*raiz)->info1 != NULL ){
		*comparacao1 = strcmp( (*info)->palavra, (*raiz)->info1->palavra );

		if( *comparacao1 < 0 )
			*comparacao1 = -1;
		else if( *comparacao1 > 0 )
			*comparacao1 = 1;
	}

	if( (*raiz)->info2 != NULL ){
		*comparacao2 = strcmp( (*info)->palavra, (*raiz)->info2->palavra ); 

		if( *comparacao2 < 0 )
			*comparacao2 = -1;
		else if( *comparacao2 > 0 )
			*comparacao2 = 1;
	} }

// Função que verifica se a palavra da info já foi inserida no nó.
// Retorna 1 se a info1 da raiz fir igual a info a ser inserida.
// Retorna 2 se a info2 da raiz for igual a info a ser inserida.
// Retorna 0 se nenhum adas informações da raiz for igual com a informação a ser inserida.
int temIGUAL(NO **raiz, INFO **info){

	int comparacao1=-2, comparacao2=-2;
	int igual = 0;

	comparar(raiz, info, &comparacao1, &comparacao2);

	if( comparacao1 == 0 )
		igual = 1;
	else if (comparacao2 == 0)
		igual = 2;

	return igual; }

// Função que insere em um nó já existente.
// Caso seja encontrado a palavra no Nó raiz é necessário incrementar a lista do Nó raiz com a posição da nova info
INFO *incrementaLISTA(INFO *infoRAIZ, INFO *info){

	insereLISTA( infoRAIZ->lista_posicoes, info->lista_posicoes->ini );
	infoRAIZ->qnt_vezes = infoRAIZ->qnt_vezes + 1; }

// Função que adiciona um novo Nó.
NO *addNO(NO *raiz, INFO *info, NO *filho){
	
	/*
		0: conteúdo das strings são iguais
		< 0: conteúdo da string1 é menor do que string2
		> 0: conteúdo da string1 é maior do que string2 */

	int comparacao;

	comparar(&raiz, &info, &comparacao, NULL);

	if( comparacao == 1 ){
		
		raiz->info2 = info;
		raiz->dir = filho;

	} else {
		
		raiz->info2 = raiz->info1;
		raiz->dir = raiz->cen;
		raiz->info1 = info;
		raiz->cen = filho; }

	return raiz; }

// Função que quebra o nó em dois.
int quebraNO(NO **raiz, INFO **info, INFO **sobe, NO **maior) {

	int comparacao1 = -2;
	int comparacao2 = -2;
	int caso;

	comparar(raiz, info, &comparacao1, &comparacao2);
	
	if( *maior == NULL )
		*maior = alocaNO();

	if( comparacao1 == -1 ){
		// Info1 da raiz é o valor central.
		*sobe = (*raiz)->info1;
		(*raiz)->info1 = *info;
		(*maior)->info1 = (*raiz)->info2;
		caso = 1;
	
	}  else if( ( comparacao1 == 1 && (*raiz)->nmrINFO == 1) || comparacao2 == -1 ){
		// a nova info é o valor central.
		*sobe = *info;
		(*maior)->info1 = (*raiz)->info2; 
		caso = 2;

	} else if( comparacao2 == 1 ) {
		// Info2 da raiz é o valor central.
		*sobe = (*raiz)->info2;
		(*maior)->info1 = *info;
		caso = 3;
	}

	info = NULL;
	(*raiz)->info2 = NULL;
	*maior = ajustaNMRS(*maior);
	*raiz = ajustaNMRS(*raiz); 
	return caso; }

// Função que insere a informação na raiz FOLHA.
void raizFOLHA(NO **raiz, INFO **info, NO **pai, INFO **sobe, NO **maior, ARVORE **arvore){

	NO *novo;
	int caso;

	if( (*raiz)->nmrINFO == 1 ){
		// Raiz só possui uma única informação.
		*raiz = addNO(*raiz, *info, NULL);
		*raiz = ajustaNMRS(*raiz);

	} else {
		// Raiz possui duas informações e terá que ser quebrado.
		caso = quebraNO(raiz, info, sobe, maior);
		if( *pai == NULL ){
			// Raiz não possui um pai.
			novo = alocaNO();

			novo->info1 = *sobe;
			novo->esq = *raiz;
			novo->cen = *maior;
			novo = ajustaNMRS(novo);

			(*arvore)->raiz = novo;
			*sobe = NULL;
		} 
	} }

NO *ajustaPONT(NO *maior2, NO **raiz, NO **maior, int caso){

	if(caso == 1){
		maior2->esq = (*raiz)->cen;
		maior2->cen = (*raiz)->dir;
		maior2->dir = NULL;
		(*raiz)->cen = *maior;

	} else if(caso == 2){
		maior2->esq = *maior;
		maior2->cen = (*raiz)->dir;
		maior2->dir = NULL;
		
	} else {
		maior2->esq = (*raiz)->dir;
		maior2->cen = *maior;
	}

	(*raiz)->dir = NULL;
	(*raiz) = ajustaNMRS(*raiz);
	maior2 = ajustaNMRS(maior2);

	return maior2; }

// Função que organiza aquela informação que subiu na árvore.
void ajustaSOBE(NO **raiz, INFO **sobe, NO **pai, NO **maior, ARVORE **arvore){

	int caso;
	NO *novo;
	NO *maior2;
	INFO *sobe2;

	novo = NULL;
	maior2 = NULL;
	sobe2 = NULL;

	if( (*raiz)->nmrINFO == 1 ){
		// A raiz possui espaço, então o valor que sobe será adicionado nele.
		*raiz = addNO(*raiz, *sobe, *maior);
		//(*raiz)->dir = *maior;
		*maior = NULL;
		*sobe = NULL;
		*raiz = ajustaNMRS(*raiz);
	
	} else {
		// A raiz não possui mais espaço. Então deverá ser quebrado.
		caso = quebraNO(raiz, sobe, &sobe2, &maior2);
		maior2 = ajustaPONT(maior2, raiz, maior, caso);

		maior2 = ajustaNMRS(maior2);
		*raiz = ajustaNMRS(*raiz);

		if( *pai == NULL ){	
			// O pai dessa raiz é nula.
			novo = alocaNO();
			novo->info1 = sobe2;
			novo->esq = *raiz;
			novo->cen = maior2;
			*sobe = NULL;
			*maior = NULL;
			sobe2 = NULL;
			maior = NULL;

			novo = ajustaNMRS(novo);

			(*arvore)->raiz = novo;
		
		} else {
			// O pai dessa raiz não é NULA.
			*sobe = sobe2;
			*maior = maior2;
		}
	} }

// Função que insere um valor na árvore.
void inserir(NO **raiz, INFO **info, NO **pai, INFO **sobe, NO **maior, ARVORE **arvore) {

	//NO **destino;
	int comparacao1=-2, comparacao2=-2;
	int c = -2;

	if(*raiz != NULL)
		c = temIGUAL(raiz, info);
	
	if( *raiz == NULL ){
		// Primeiro item a ser inserido na árvore.
		*raiz = alocaNO();
		(*raiz)->info1 = *info;
		*raiz = ajustaNMRS(*raiz);

	} else if( c != 0 ){
		// A nova info possue uma palavra que já foi inserida na árvore.
		// Nesse caso é feito apenas o incremento na lista do Nó dessa árvore.
		if( c == 1 )
			(*raiz)->info1 = incrementaLISTA((*raiz)->info1, *info);
		else
			(*raiz)->info2 = incrementaLISTA((*raiz)->info2, *info);

	} else if ((*raiz)->nmrFILHOS == 0 ){
		// A raiz é folha!
		raizFOLHA(raiz, info, pai, sobe, maior, arvore);

	} else {
		// A raiz não é NULA.
		// A raiz não possue a mesma palavra que a raiz.
		// A raiz não é folha.
		comparar(raiz, info, &comparacao1, &comparacao2);

		if( comparacao1 == -1 ) {
			// foi pra esquerda
			inserir(&(*raiz)->esq, info, raiz, sobe, maior, arvore);
		} else if( ( comparacao1 == 1 && (*raiz)->nmrINFO == 1) || comparacao2 == -1 ) {
			// foi pro centro
			inserir(&(*raiz)->cen, info, raiz, sobe, maior, arvore);
		} else if( comparacao2 == 1 ) {
			// foi pra direita
			inserir(&(*raiz)->dir, info, raiz, sobe, maior, arvore);
		}

		if( *sobe != NULL )
			ajustaSOBE(raiz, sobe, pai, maior, arvore);
	} }

// leva uma nova informação para a função de inserção.
void gestaoINSERCAO(ARVORE *arvore, char *palavra, int linha, int ordem){
	


	INFO *info, *sobe;
	NO *pai, *maior;
	LISTA *lista;
	NO_LISTA *no_lista;

	sobe = NULL;
	pai = maior = NULL;

	info = alocaINFO();
	lista = alocaLISTA();
	no_lista = alocaNO_LISTA();

	// Preenche os dados do nó da lista
	no_lista->nmr_linha = linha; 
	no_lista->nmr_ordem_linha = ordem; 

	// Insere no Nó na lista
	insereLISTA(lista, no_lista);
	
	// atribui a lista para a lista_posicoes da info
	info->lista_posicoes = lista;

	// copia a palavra para a palavra da info.
	strcpy(info->palavra, palavra);

	inserir(&arvore->raiz, &info, &pai, &sobe, &maior, &arvore); }


