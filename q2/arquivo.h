// arquivo.h

// Funcoes do arquivo arquivo.c
//char temACENTO(char *c);
void minusculo(char *palavra);
int tratarCARACTER(char *c);
char lerPALAVRA(FILE *arq, char *palavra, int *linha, int *ordem);
void marcarTEMPO(FILE *arq, char *palavra, clock_t *tempo, int i, int caso, int passos, char *foiENC);
void lerARQUIVO(FILE *arq, ARVORE *arvore);