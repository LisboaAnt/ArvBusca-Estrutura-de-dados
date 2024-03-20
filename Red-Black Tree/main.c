#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/// ESTRUTURA DO CODIGO:  {  No / Estrutura  }

// Definição de estrutura para um nó da árvore
struct No
{
    struct No *pai;
    struct No *esquerda;
    struct No *direita;
    int color; // 0 para preto, 1 para vermelho
    int chave;
};

// Estrutura para a árvore vermelho-preto
struct Estrutura
{
    struct No *raiz;
    struct No *nil; // Sentinel (nó nulo)
};

/// FUNÇÕES PRINCIPAIS  ADICIONAR:{ leftRotate / rightRotate / RBInsertFixup / RBInsert }   REMOVER:{ / }

void leftRotate(struct Estrutura *T, struct No *x)
{
    struct No *y = x->direita;
    x->direita = y->esquerda;

    if (y->esquerda != T->nil)
    {
        y->esquerda->pai = x;
    }

    y->pai = x->pai;

    if (x->pai == T->nil)
    {
        T->raiz = y;
    }
    else if (x == x->pai->esquerda)
    {
        x->pai->esquerda = y;
    }
    else
    {
        x->pai->direita = y;
    }

    y->esquerda = x;
    x->pai = y;
}

void rightRotate(struct Estrutura *T, struct No *y)
{
    struct No *x = y->esquerda;
    y->esquerda = x->direita;

    if (x->direita != T->nil)
    {
        x->direita->pai = y;
    }

    x->pai = y->pai;

    if (y->pai == T->nil)
    {
        T->raiz = x;
    }
    else if (y == y->pai->direita)
    {
        y->pai->direita = x;
    }
    else
    {
        y->pai->esquerda = x;
    }

    x->direita = y;
    y->pai = x;
}

// Procedimento para corrigir a propriedade da árvore vermelho-preto após inserção
void RBInsertFixup(struct Estrutura *T, struct No *z)
{
    while (z->pai->color == 1)
    {
        if (z->pai == z->pai->pai->esquerda)
        {
            struct No *y = z->pai->pai->direita;
            if (y->color == 1)
            {
                z->pai->color = 0;
                y->color = 0;
                z->pai->pai->color = 1;
                z = z->pai->pai;
            }
            else
            {
                if (z == z->pai->direita)
                {
                    z = z->pai;
                    leftRotate(T, z);
                }
                z->pai->color = 0;
                z->pai->pai->color = 1;
                rightRotate(T, z->pai->pai);
            }
        }
        else
        {
            struct No *y = z->pai->pai->esquerda;
            if (y->color == 1)
            {
                z->pai->color = 0;
                y->color = 0;
                z->pai->pai->color = 1;
                z = z->pai->pai;
            }
            else
            {
                if (z == z->pai->esquerda)
                {
                    z = z->pai;
                    rightRotate(T, z);
                }
                z->pai->color = 0;
                z->pai->pai->color = 1;
                leftRotate(T, z->pai->pai);
            }
        }
    }
    (T)->raiz->color = 0;
}

// Função para inserir um nó na árvore vermelho-preto
void RBInsert(struct Estrutura *T, struct No *z)
{
    struct No *y = T->nil;
    struct No *x = T->raiz;

    while (x != T->nil)
    {
        y = x;
        if (z->chave < x->chave)
        {
            x = x->esquerda;
        }
        else
        {
            x = x->direita;
        }
    }

    z->pai = y;
    if (y == T->nil)
    {
        T->raiz = z;
    }
    else if (z->chave < y->chave)
    {
        y->esquerda = z;
    }
    else
    {
        y->direita = z;
    }

    z->esquerda = T->nil;
    z->direita = T->nil;
    z->color = 1; // Vermelho
    RBInsertFixup(T, z);
}

// REMOÇÃO : RB-TRANSPLANT RB-DELETE-FIXUP RB-DELETE

struct No *acharNo(struct Estrutura *T, int chave) {
    struct No *aux = T->raiz;

    while (aux != T->nil) {
        if (chave < aux->chave) {
            aux = aux->esquerda;
        } else if (chave > aux->chave) {
            aux = aux->direita;
        } else {
            return aux;  // Encontrou o nó com a chave desejada
        }
    }

    return T->nil;  // Não encontrou o nó com a chave desejada
}

struct No *sucessor(struct Estrutura *T, int chave) {
    struct No *x = acharNo(T, chave);

    if (x == T->nil) {
        return T->nil;  // O nó com a chave desejada não foi encontrado
    }

    struct No *aux = x->direita;

    while (aux != T->nil) {
        aux = aux->esquerda;
    }

    return aux;
}


void moverPai(struct Estrutura *T, struct No **u, struct No **v) {
    if ((*u)->pai == T->nil) {
        T->raiz = *v;

    } else {
        if ((*u)->chave == (*u)->pai->esquerda->chave) {

            (*u)->pai->esquerda = *v;

        } else {

            (*u)->pai->direita = *v;

        }
    }
    (*v)->pai = (*u)->pai;
}

void RbDeleteFixUp(struct Estrutura *T, struct No *x){
    struct No *g;
    while (x != T->raiz || x->color == 0){
        if (x == x->pai->esquerda){
            g = x->pai->direita;

            if (g->color == 1){
                g->color = 0;
                x->pai->color = 1;
                leftRotate(T, x->pai);
                g = x->pai->direita;}

            if (g->esquerda->color == 0 || g->direita->color == 0){
                g->color = 1;
                x = x->pai;}

            else if (g->direita->color == 0){
                g->esquerda->color = 0;
                g->color = 1;
                rightRotate(T, g);
                g = x->pai->direita;
                g->color = x->pai->color;
                x->pai->color = 0;}

            g->direita->color = 0;
            leftRotate(T, x->pai);
            x = T->raiz;

        } else {

            g = x->pai->esquerda;
            if (g->color == 1) {
                g->color = 0;
                x->pai->color = 1;
                rightRotate(T, x->pai);
                g = x->pai->esquerda;
            }

            if (g->direita->color == 0 || g->esquerda->color == 0) {
                g->color = 1;
                x = x->pai;
            } else if (g->esquerda->color == 0) {
                g->direita->color = 0;
                g->color = 1;
                leftRotate(T, g);
                g = x->pai->esquerda;
                g->color = x->pai->color;
                x->pai->color = 0;
            }

            g->esquerda->color = 0;
            rightRotate(T, x->pai);
            x = T->raiz;
        }
    }
    x->color = 0;
}

void RBDelete(struct Estrutura *T, struct No *z){                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      return;

    struct No *x;
    struct No *y = z;
    int yCorOriginal = y->color;

    if (z->esquerda == T->nil){
        x = z->direita;
        moverPai(T,&z,&z->direita);
  
    }else if(z->direita == T->nil){
        x = z->esquerda;
        moverPai(T,&z,&z->esquerda);

    }else{y = sucessor(T,z->chave);
            yCorOriginal = y->color;
            x = y->direita;
            if(y->pai == z){
                x->pai = y;
 
                }
            else{
                moverPai(T,&y,&y->direita);              
                y->direita = z->direita;
                y->direita->pai = y;
            
            }

            moverPai(T,&z,&y);
            y->esquerda = z->esquerda;
            y->esquerda->pai = y;
            y->color = z->color;
        }

    if(yCorOriginal == 0 ){
        RbDeleteFixUp(T,x);
    }
}



///  FUNÇÕES AUX: { freeTree / isRedBlackTreeHelper / isRedBlackTree / criarlista }

void freeTree(struct No *no, struct No *nil)
{
    if (no != nil)
    {
        freeTree(no->esquerda, nil);
        freeTree(no->direita, nil);
        free(no);
    }
}


int isRedBlackTreeHelper(struct No *no, struct No *nil, int *blackHeight)
{
    if (no == nil)
    {
        *blackHeight = 1;
        return 1; // Árvore vazia é uma árvore rubro-negra
    }

    int leftBlackHeight, rightBlackHeight;

    // Verifica as propriedades da subárvore esquerda
    int leftIsEstrutura = isRedBlackTreeHelper(no->esquerda, nil, &leftBlackHeight);

    // Verifica as propriedades da subárvore direita
    int rightIsEstrutura = isRedBlackTreeHelper(no->direita, nil, &rightBlackHeight);

    // Verifica se as propriedades de cor estão sendo atendidas
    if ((no->color == 1 && (no->esquerda->color == 1 || no->direita->color == 1)) || leftBlackHeight != rightBlackHeight)
    {
        return 0; // Não é uma árvore rubro-negra
    }

    *blackHeight = leftBlackHeight + (no->color == 0); // Incrementa a altura preta se o nó atual for preto

    return leftIsEstrutura && rightIsEstrutura;
}

int isRedBlackTree(struct Estrutura *T)
{
    int blackHeight; // Altura preta da árvore
    return isRedBlackTreeHelper(T->raiz, T->nil, &blackHeight);
}

//  cria a lista
void criarlista(int *array, int amount)
{
    srand(time(NULL));

    // Inicialize um array de valores únicos
    int *valoresUnicos = (int *)malloc(amount * sizeof(int));
    for (int i = 0; i < amount; i++)
    {
        valoresUnicos[i] = i;
    }

    // Embaralhe os valores únicos para garantir que sejam aleatórios
    for (int i = amount - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = valoresUnicos[i];
        valoresUnicos[i] = valoresUnicos[j];
        valoresUnicos[j] = temp;
    }

    // Copie os valores embaralhados para o array de saída
    for (int i = 0; i < amount; i++)
    {
        array[i] = valoresUnicos[i];
    }

    // Libere a memória alocada
    free(valoresUnicos);
}

/// MAIN:

int main()
{

    for (int i =0; i<100;++i){
        printf("%i",i);



    struct Estrutura minhaArvore;
    minhaArvore.nil = malloc(sizeof(struct No));
    minhaArvore.nil->color = 0; // Preto
    minhaArvore.nil->esquerda = minhaArvore.nil->direita = minhaArvore.nil->pai = NULL;
    minhaArvore.raiz = minhaArvore.nil;

    int *listaNRand = malloc(sizeof(int) * 1000); // Guarda espaco para a list

    criarlista(listaNRand, 100);


    for (int i = 0; i < 100; ++i){
        struct No *novoNo = malloc(sizeof(struct No));
        novoNo->chave = listaNRand[i];
        RBInsert(&minhaArvore, novoNo);


    }
        // E ou não uma RBT?
    if (isRedBlackTree(&minhaArvore)){
        printf("\033[1;32m A arvore E uma arvore rubro-negra.\033[0m\n");}
    else{
        printf("\033[1;31m A arvore NAO E uma arvore rubro-negra.\033[0m\n");}


    for (int i = 0; i < 10; ++i){
        
        struct No *novoNo = malloc(sizeof(struct No));
        novoNo = acharNo(&minhaArvore,listaNRand[i]);

       RBDelete(&minhaArvore, novoNo);
    }    

    if (isRedBlackTree(&minhaArvore)){
        printf("\033[1;32m A arvore E uma arvore rubro-negra.\033[0m\n\n");}
    else{
        printf("\033[1;31m A arvore NAO E uma arvore rubro-negra.\033[0m\n\n");}

    // Liberar a memória alocada para a árvore
    freeTree(minhaArvore.raiz, minhaArvore.nil);
    free(minhaArvore.nil);
    }
    return 0;
}
