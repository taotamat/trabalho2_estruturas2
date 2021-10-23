// insercao.h
void comparar(NO **raiz, char *palavra, int *comparacao1, int *comparacao2);
int temIGUAL(NO **raiz, char *palavra);
INFO *incrementaLISTA(INFO *infoRAIZ, INFO *info);
NO *addNO(NO *raiz, INFO *info, NO *filho);
int quebraNO(NO **raiz, INFO **info, INFO **sobe, NO **maior);
void raizFOLHA(NO **raiz, INFO **info, NO **pai, INFO **sobe, NO **maior, ARVORE **arvore);
NO *ajustaPONT(NO *maior2, NO **raiz, NO **maior, int caso);
void ajustaSOBE(NO **raiz, INFO **sobe, NO **pai, NO **maior, ARVORE **arvore);
void inserir(NO **raiz, INFO **info, NO **pai, INFO **sobe, NO **maior, ARVORE **arvore);
void gestaoINSERCAO(ARVORE *arvore, char *palavra, int linha, int ordem);
void gestaoLER(ARVORE *arvore);