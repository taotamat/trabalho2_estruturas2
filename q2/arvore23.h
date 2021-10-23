// arvore23.h
// Structs:
typedef struct NO_LISTA{
    int nmr_linha; // linha onde a palavra se encontra no arquivo.
    int nmr_ordem_linha; // posição onde a palavra se encontra na linha.
    struct NO_LISTA *prox; // Proximo nó presente na lista.
} NO_LISTA;

typedef struct LISTA{
    struct NO_LISTA *ini; // Nó inicial da lista.
    struct NO_LISTA *fim; // Nó final da lista.
} LISTA;


typedef struct INFO {
    char palavra[101]; // String que armazena a palavra.
    LISTA *lista_posicoes; // Lista de posições onde a palavra se encontra no texto.
    int qnt_vezes; // Quantidade de vezes q a palavra aparece no texto.
} INFO;

typedef struct NO {

	INFO *info1;
	INFO *info2;

	struct NO *esq;
	struct NO *cen;
	struct NO *dir;

	int nmrINFO; // Número informações cadastradas.
	int nmrFILHOS; // Numero de filhos que o Nó possui.
} NO;

typedef struct ARVORE {
	NO *raiz;
	int tam; // Qnt de Nó cadastrados na árvore;
} ARVORE;

// funcoes em arvore23.c
void ast();
NO_LISTA *alocaNO_LISTA();
LISTA *alocaLISTA();
INFO *alocaINFO();
NO *alocaNO();
ARVORE *alocaARV();
void apresentaLISTA(NO_LISTA *aux);
void apresentaINFO(INFO *info);
void preordem(NO *aux);
void inordem(NO *aux);
void posordem(NO *aux);
int qntFILHOS(NO *no);
int qntINFO(NO *no);
NO *ajustaNMRS(NO *no);
int vazia(LISTA *lista);
void insereLISTA(LISTA *lista, NO_LISTA *no);

