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
    char palavra[50]; // String que armazena a palavra.
    LISTA *lista_posicoes; // Lista de posições onde a palavra se encontra no texto.
    int qnt_vezes; // Quantidade de vezes q a palavra aparece no texto.
} INFO;

typedef struct NO { 
    INFO *info;
    struct NO *esq; // Filho da esquerda
    struct NO *dir; // Filho da direita
    int cor; // cor do nó
} NO;

typedef struct ARVORE {
	NO *raiz; // Raiz da árvore
	int tam; // Quantidade de Nós inseridos
} ARVORE;

// funções presentes em arvore_rubro_negra.c
void ast();
NO_LISTA *alocaNO_LISTA();
LISTA *alocaLISTA();
NO *alocaNO();
ARVORE *alocaARV();
int cor(NO *H);
void trocaCor(NO *H);
void apresentaCOR(int cor);
void apresentaLISTA(NO_LISTA *aux);
void apresentaNO(NO *aux);
void preordem(NO *aux);
void inordem(NO *aux);
void posordem(NO *aux);
int vazia(LISTA *lista);
void insereLISTA(LISTA *lista, NO_LISTA *no);
void inserir(ARVORE *arvore, NO **raiz, NO *novo);
void ler(NO *no);
void gestaoINSERCAO(ARVORE *arvore, char *palavra, int linha, int ordem);
void gestaoLER(ARVORE *arvore);
NO *buscar(NO *raiz, char *palavra, int *passos);
void gestaoBUSCA(ARVORE *arvore);
