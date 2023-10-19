#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct no{
    int key;
    int bal;
    struct no *esq;
    struct no *dir;
}No; 

//ARVORE AVL ANTONIO LISBOA 535865





//Funcoes principais:  {  caso1(add), caso2(add), inserir }|{  caso1R(remover),caso2R(remover),balancear, trocarNos e remover  }

//  rotação simples e duplas para a esquerda (para adicionar)
void Caso1(No **raiz, int *h) {
    No *raizU;
    raizU = (*raiz)->esq; // Pega o filho a esq do No
    
    if (raizU->bal == -1) {   // Se o filho a dir do No tiver bal = -1 rotacao simples a direita
        (*raiz)->esq = raizU->dir; 
        raizU->dir = (*raiz);
        (*raiz) = raizU; 
        (*raiz)->dir->bal = 0; 
    } 
    else { // Se o filho a esq do No tiver bal = 1 rotação dupla à direita     
        No *raizV; 
        raizV = raizU->dir; 
        raizU->dir = raizV->esq; 
        raizV->esq = raizU; 
        (*raiz)->esq = raizV->dir;  
        raizV->dir = (*raiz); 
        
        if (raizV->bal == -1) { // Se o bal do aux = -1
        (*raiz)->bal = 1; 
        raizU->bal = 0; 
        } else if (raizV->bal == 1) { // Se o bal do aux = 1
        (*raiz)->bal = 0; 
        raizU->bal = -1; 
        } else { // Se o bal do aux = 0
        (*raiz)->bal = 0;
        raizU->bal = 0; 
        }
        (*raiz) = raizV; 
    }
    (*raiz)->bal = 0; *h = 0;  // O bal do nó = 0 e a altura da árvore = 0
}

//  rotacao simples e duplas para a direita (para adicionar)
void Caso2(No **raiz, int *h) {
    No *raizU;
    raizU = (*raiz)->dir;

    if (raizU->bal == 1) {
        // Rotacao simples a esquerda
        (*raiz)->dir = raizU->esq; 
        raizU->esq = (*raiz);  
        (*raiz) = raizU; 
        (*raiz)->esq->bal = 0; 
    } 
    else {            
        No *raizV;

        raizV = raizU->esq; 
        // Rotacao dupla a esquerda
        raizU->esq = raizV->dir; 
        raizV->dir = raizU; 
        (*raiz)->dir = raizV->esq;  
        raizV->esq = (*raiz); 
        
        if (raizV->bal == 1) { 
            (*raiz)->bal = -1; 
            raizU->bal = 0; 
        } else if (raizV->bal == -1){ 
            (*raiz)->bal = 0; 
            raizU->bal = 1; 
        } else { 
            (*raiz)->bal = 0; 
            raizU->bal = 0; 
        }
        (*raiz) = raizV; 
    }
    (*raiz)->bal = 0; *h = 0;  
}


//  insere um No na arvore
void insertAVL(int x, No **raiz, int *h) {
    if ((*raiz) == NULL) {
        // Cria um novo nó e inicializa seus valores
        No *node = malloc(sizeof(No));  
        node->esq = node->dir = NULL;
        node->bal = 0;
        node->key = x;
        (*raiz) = node;

        *h = 1;
    } else {
        if (x == (*raiz)->key) {
            // Elemento ja existe nao e possivel add
            printf("Esse No: %d ja esta na arvore!\n",x);
            return;
        }
        
        if (x < (*raiz)->key) {
            // Inserir na subárvore esquerda e verificar balancearamento
            insertAVL(x, &((*raiz)->esq), h);

            if (*h == 1) {
                switch ((*raiz)->bal) {
                    case 1: 
                        (*raiz)->bal = 0; 
                        *h = 0;
                        break;
                    case 0: 
                        (*raiz)->bal = -1;
                        break;
                    case -1: 
                        Caso1(raiz, h);
                        break;
                }
            }
        } else {
            // Inserir na subárvore direita e verificar balancearamento
            insertAVL(x, &((*raiz)->dir), h);

            if (*h == 1) {
                switch ((*raiz)->bal) {
                    case -1: 
                        (*raiz)->bal = 0; 
                        *h = 0;
                        break;
                    case 0: 
                        (*raiz)->bal = 1;
                        break;
                    case 1: 
                        Caso2(raiz, h);
                        break;
                }
            }
        }
    }
}


// rotação simples e duplas para a esquerda(para remover)
void Caso1R(No **raiz, int *h) {
    No *raizU; // No auxiliar para o filho a esquerda
    raizU = (*raiz)->esq; // pega o filho a esquerda do No
    
    if (raizU->bal <= 0) { 
        // Rotação simples à direita
        (*raiz)->esq = raizU->dir;
        raizU->dir = (*raiz);
        (*raiz) = raizU;

        if (raizU->bal == -1) { 
            // Se o bal do filho a esquerda do No for -1
            raizU->bal = (*raiz)->dir->bal = 0; 
            *h = 1;
        } else { 
            // Se o bal do filho a esquerda do No for 0
            raizU->bal = 1;
            (*raiz)->dir->bal = -1;
            *h = 0;
        }
    } else { 
        No *raizV; 
        raizV = raizU->dir; 

        raizU->dir = raizV->esq;
        raizV->esq = raizU;
        (*raiz)->esq = raizV->dir;
        raizV->dir = (*raiz);
        (*raiz) = raizV;

        switch (raizV->bal) { 
            case -1: 
                raizU->bal = 0; 
                (*raiz)->dir->bal = 1; 
                break;
            case 0:  
                raizU->bal = 0; 
                (*raiz)->dir->bal = 0; 
                break;
            case 1:  
                raizU->bal = -1; 
                (*raiz)->dir->bal = 0; 
                break;  
        }

        (*raiz)->bal = 0; 
        *h = 1;
    }
}


// rotacaoo simples e duplas para a direita( para remover) 
void Caso2R(No **raiz, int *h) {
    No *raizU; // No auxiliar para o filho a direita
    raizU = (*raiz)->dir; // Pega o filho a direita do No

    if (raizU->bal >= 0) {  
        // Rotação simples à esquerda
        (*raiz)->dir = raizU->esq;
        raizU->esq = (*raiz);
        (*raiz) = raizU;

        if (raizU->bal == 1) {  
            // Se o bal do filho a direita do no for 1
            raizU->bal = (*raiz)->esq->bal = 0; 
            *h = 1;
        } else { 
            // Se o bal do filho a direita do no for 0
            raizU->bal = -1;
            (*raiz)->esq->bal = 1;
            *h = 0;
        }
    } else { 
        No *raizV; // No auxiliar
        raizV = raizU->esq; 

        raizU->esq = raizV->dir;
        raizV->dir = raizU;
        (*raiz)->dir = raizV->esq;
        raizV->esq = (*raiz);
        (*raiz) = raizV;

        switch(raizV->bal) { 
            case -1: 
                raizU->bal = 0; 
                (*raiz)->esq->bal = -1; 
                break;

            case 0:  
                raizU->bal = 0; 
                (*raiz)->esq->bal = 0; 
                break;

            case 1:  
                raizU->bal = 1; 
                (*raiz)->esq->bal = 0; 
                break;  
        }

        (*raiz)->bal = 0; 
        *h = 1;
    }
}


//  Calcula o bal da árvore
void balancear(No **raiz, char ladoDeRotacao, int* h) {
  if (*h) {
    if (ladoDeRotacao == 'R') { 
      // Rotação para a direita
      switch ((*raiz)->bal) { 
        case 1: 
          (*raiz)->bal = 0; 
          break; 
        case 0: 
          (*raiz)->bal = -1; 
          *h = 0; 
          break; 
        case -1: 
          Caso1R(raiz, h); 
          break; 
      }
    } else {
      // Rotacao para a esquerda
      switch((*raiz)->bal) { 
        case -1: 
          (*raiz)->bal = 0; 
          break; 
        case 0: 
          (*raiz)->bal = 1; 
          *h = 0; 
          break; 
        case 1: 
          Caso2R(raiz, h); 
          break; 
      }
    }
  }
}


// TRoca pai com filho.
void trocarNos(No **primeiroNo, No **segundoNo) {
  No* bakcupraiz; //  auxiliar para realizar a troca
  int backupBal; //  Vauxiliar para realizar a troca

  // Troca dos nós
  bakcupraiz = (*segundoNo);
  (*segundoNo) = (*primeiroNo);
  (*primeiroNo) = bakcupraiz;

  // Troca dos filhos esquerdos
  bakcupraiz = (*segundoNo)->esq;
  (*segundoNo)->esq = (*primeiroNo)->esq;
  (*primeiroNo)->esq = bakcupraiz;
  
  // Troca dos filhos direitos
  bakcupraiz = (*segundoNo)->dir;
  (*segundoNo)->dir = (*primeiroNo)->dir;
  (*primeiroNo)->dir = bakcupraiz;

  // Troca do BAL
  backupBal = (*segundoNo)->bal;
  (*segundoNo)->bal = (*primeiroNo)->bal;
  (*primeiroNo)->bal = backupBal;
}


// Remover e ajusta
void remover(int x, No **raiz, int *h) {
    if ((*raiz) == NULL) { // Se raiz = null não tem oq remover
        printf("Nó raiz nulo!\n"); 
        *h = 0; 
    } else {
        if (x < (*raiz)->key) { // Se o x for menor vair para o filho esq
            remover(x, &(*raiz)->esq, h); //Remover
            balancear(raiz, 'L', h); // Balanceamento
        } else {
            if (x > (*raiz)->key) { // Se o x for maior vair para o filho dir
                remover(x, &(*raiz)->dir, h); // remove
                balancear(raiz, 'R', h); // balancea
            } else { // X = raiz
                No *backupraiz;
                backupraiz = (*raiz);
                if ((*raiz)->esq == NULL) { //se o filho esquerdo é nulo, substitua pelo filho direito
                    (*raiz) = (*raiz)->dir;
                    *h = 1; 
                    free(backupraiz); // free no atual
                } else {
                    if ((*raiz)->dir == NULL) { // se o filho direito for nulo, substitua pelo filho esquerdo
                        (*raiz) = (*raiz)->esq;
                        *h = 1;
                        free(backupraiz); // free no atual
                    } else { // else busca o no sucessor para a remoção
                        No *sucessor;
                        sucessor = (*raiz)->dir;
                        if (sucessor->esq == NULL) { // Se o filho esquerdo do filho direito for nulo, substitua
                            sucessor->esq = (*raiz)->esq;
                            sucessor->bal = (*raiz)->bal;
                            (*raiz) = sucessor;
                            *h = 1;
                            free(backupraiz); // free no atual
                        } else { //  busque o nó sucessor e faça a troca
                            No *Nsucessor;
                            while (sucessor->esq != NULL) {
                                Nsucessor = sucessor;
                                sucessor = sucessor->esq;
                            }
                            trocarNos(raiz, &Nsucessor->esq);
                            remover(x, &(*raiz)->dir, h);
                        }
                        balancear(raiz, 'R', h); // Balancea 
                    }
                }
            }
        }
    }
}



/////////////// FUNCOES AUX PARA MELHOR ENTENDIMENTO: alturaAvl, checkAVL, freeAVL, criarlista, ContNos

//  calcula a altura da árvore
int alturaAvl(No *raiz) {
    int he, hd;

    if (raiz == NULL) {
        return 0; // Se a árvore estiver vazia, a altura é 0
    } else {
        he = alturaAvl(raiz->esq); // Calcula a altura da sub-árvore esquerda
        hd = alturaAvl(raiz->dir); // Calcula a altura da sub-árvore direita
    }

    if (he > hd) {
        return he + 1; // Retorna a altura da sub-árvore esquerda + 1
    } else {
        return hd + 1; // Retorna a altura da sub-árvore direita + 1
    }
}

// Função que checa se a árvore é AVL
int checkAVL(No *raiz, int maxNodes, int *count){

    if(raiz->esq != NULL){
       checkAVL(raiz->esq, maxNodes, count); // Checa a sub-árvore esquerda
    }

    if(raiz->dir != NULL){
        checkAVL(raiz->dir, maxNodes, count); // Checa a sub-árvore direita
    }

    int he = alturaAvl(raiz->esq); // Altura da sub-árvore esquerda
    int hd = alturaAvl(raiz->dir); // Altura da sub-árvore direita

    if(hd - he > 1 || hd - he < -1){ // Se a diferença entre as alturas das sub-árvores for maior que 1 ou menor que - 1, a árvore não é AVL 
        return 0;
    }else{  // Se a diferença entre as alturas das sub-árvores estiver entre 0, -1 e 1, a árvore é AVL
        (*count)++;
    }

    if(*count == maxNodes){ // Se o número de nós da árvore for igual ao número máximo de nós, a árvore é AVL
        return 1;
    }
}

// Função que limpa a árvore e libera a memória alocada
void freeAVL(No *raiz) {
    if (raiz == NULL) {
        return; // Se o nó for nulo, não há nada para liberar
    }

    freeAVL(raiz->esq); // Libera a subárvore esquerda recursivamente
    freeAVL(raiz->dir); // Libera a subárvore direita recursivamente

    free(raiz); // Libera o nó atual
}

//  cria a lista
void criarlista(int *array, int amount) {
    srand(time(NULL));

    // Inicialize um array de valores únicos
    int *valoresUnicos = (int *)malloc(amount * sizeof(int));
    for (int i = 0; i < amount; i++) {
        valoresUnicos[i] = i;
    }

    // Embaralhe os valores únicos para garantir que sejam aleatórios
    for (int i = amount - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = valoresUnicos[i];
        valoresUnicos[i] = valoresUnicos[j];
        valoresUnicos[j] = temp;
    }

    // Copie os valores embaralhados para o array de saída
    for (int i = 0; i < amount; i++) {
        array[i] = valoresUnicos[i];
    }

    // Libere a memória alocada
    free(valoresUnicos);
}

// Função que conta os nós da árvore
int ContNos(No *raiz, int *count){ 
    if(raiz->esq != NULL){ // chama a função recursivamente
        ContNos(raiz->esq, count); // Conta os nós da sub-árvore esq
    }
 
    (*count)++; // contador de nós

    if(raiz->dir != NULL){ // chama a função recursivamente
        ContNos(raiz->dir, count); // Conta os nós da sub-árvore dir
    }
}


//////////////MINHA MAIN
int main() {

    int *listaNRand = malloc(sizeof(int) * 100000);//Guarda espaco para a list

    for (int i = 0; i < 1000; i++) { //1000 arvore avl

        printf("\n \033[1;31m Arvore numero: {%d}\n", i+1);

        int h, Nnos = 0;


        criarlista(listaNRand, 100000); // Gere uma lista de números aleatórios de 0 a 100 000

        No *raiz = NULL;

        for (int j = 0; j < 10000; j++) {insertAVL(listaNRand[j], &raiz, &h);} //Insere os 10000 nos na avl

        ContNos(raiz, &Nnos);



        printf("\033[0mArvore com : %d nos\n", Nnos);

        Nnos = 0; //Zera

        if (checkAVL(raiz, 10000, &Nnos) == 0) {printf("Nao é uma arvore AVL\n");} else {printf("Eh uma arvore avl\n");} //Verica se e avl

        for (int k = 0; k < 1000; k++) {remover(listaNRand[k], &raiz, &h);} //remove os 1000

        Nnos = 0;


        ContNos(raiz, &Nnos); // conta

        printf("Arvore com : %d nos\n", Nnos);

        if (checkAVL(raiz, 1000, &Nnos) == 0) {printf("Nao é uma arvore AVL\n");} else {printf("Eh uma arvore avl\n");}//Verica se e avl

        freeAVL(raiz); //Free na arvore para nao pesar
    }

    free(listaNRand); //apaga a lista
    return 0;
}