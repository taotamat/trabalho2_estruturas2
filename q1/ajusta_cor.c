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


/*-------Rotações---------*/

NO *rotacionaEsquerda(NO *A){
    NO *B;
    B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = RED;
    return B; }

NO *rotacionaDireita(NO *A){
	NO *B;
	B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = RED;
    return B; }


/* -    AJUSTES   - */

NO *gestaoBALANCEAMENTO(ARVORE *arvore, NO **aux){


    if(cor((*aux)->dir) == RED)
        *aux = rotacionaEsquerda(*aux);


    if( (*aux)->esq != NULL && cor((*aux)->esq) == RED && cor((*aux)->esq->esq) == RED)
        *aux = rotacionaDireita(*aux);


    if( cor((*aux)->esq) == RED && cor((*aux)->dir) == RED )
        trocaCor(*aux);


    if( *aux == arvore->raiz && cor(*aux) == RED )
        (*aux)->cor = BLACK;

    return (*aux); }


