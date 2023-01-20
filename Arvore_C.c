#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Estrutura que compoe
o nó da ávore. */
typedef struct no {
  int ID;  
  char nome[50];
  int idade;
  struct no *esquerda;
  struct no *direita;
  struct materias *cadeiras;
  long telefone;
  char endereco[100];
} No;

/* Estrutura que compoe
os nós das materias */
typedef struct materias {
  char nome_materia[50];
  float nota;
  struct materias *proxima;
} Materias;

// Protótipos de função
No* criar_no(int ID, char nome[50], int idade, long telefone, char endereco[100]);
Materias* criar_materia(char nome_materia[50], float nota);
No* inserir(No* raiz, int ID, char nome[50], int idade, long telefone, char endereco[100]);
No* excluir(No* raiz, int ID);
void modificar(No* raiz, int ID, char nome[50], int idade, long telefone, char endereco[100]);
void inserir_materia(No* raiz, int ID, char nome_materia[50], float nota);
void excluir_materia(No* raiz, int ID, char nome_materia[50]);
void modificar_materia(No* raiz, int ID, char nome_materia[50], float nota);
void imprimir_arvore(No* raiz);
void limpar_arvore(No* raiz);
void terminal(No* raiz);

// Main
int main() {
  setlocale(LC_ALL, "Portuguese_Brasil");

  No* raiz = NULL;
  terminal(raiz);
  limpar_arvore(raiz);
  return 0;
}

// Cria um nó da árvore
No* criar_no(int ID, char nome[50], int idade, long telefone, char endereco[100]) {
  No* novo_no = (No*) malloc(sizeof(No));
  novo_no->ID = ID;
  strcpy(novo_no->nome, nome);
  novo_no->idade = idade;
  novo_no->cadeiras = NULL;
  novo_no->telefone = telefone;
  strcpy(novo_no->endereco, endereco);
  novo_no->esquerda = NULL;
  novo_no->direita = NULL;
  return novo_no;
}

// Cria um nó de materia
Materias* criar_materia(char nome_materia[50], float nota) {
  Materias* novo_materia = (Materias*) malloc(sizeof(Materias));
  strcpy(novo_materia->nome_materia, nome_materia);
  novo_materia->nota = nota;
  novo_materia->proxima = NULL;
  return novo_materia;
}

// Insere um novo nó na árvore
No* inserir(No* raiz, int ID, char nome[50], int idade, long telefone, char endereco[100]) {
  if (raiz == NULL) {
    raiz = criar_no(ID, nome, idade, telefone, endereco);
    printf("Novo nó inserido na árvore!\n");
  } else if (ID < raiz->ID) {
    raiz->esquerda = inserir(raiz->esquerda, ID, nome, idade, telefone, endereco);
  } else if (ID > raiz->ID) {
    raiz->direita = inserir(raiz->direita, ID, nome, idade, telefone, endereco);
  } else {
    printf("O ID %d já existe na árvore!\n", ID);
  }
  return raiz;
}

// Excluir um nó da árvore
No* excluir(No* raiz, int ID) {
  // Se a árvore está vazia
  if (raiz == NULL) {
    printf("A árvore está vazia!\n");
    return raiz;
  }

  // Procura o nó
  if (ID < raiz->ID) {
    raiz->esquerda = excluir(raiz->esquerda, ID);
  } else if (ID > raiz->ID) {
    raiz->direita = excluir(raiz->direita, ID);
  } else {
    // Se o nó não tem filhos
    if (raiz->esquerda == NULL && raiz->direita == NULL) {
      printf("O nó %d foi excluído da árvore!\n", raiz->ID);
      free(raiz);
      raiz = NULL;
    }
    // Se o nó tem somente um filho
    else if (raiz->esquerda == NULL) {
      No* temp = raiz;
      raiz = raiz->direita;
      printf("O nó %d foi excluído da árvore!\n", temp->ID);
      free(temp);
    } else if (raiz->direita == NULL) {
      No* temp = raiz;
      raiz = raiz->esquerda;
      printf("O nó %d foi excluído da árvore!\n", temp->ID);
      free(temp);
    }
    // Se o nó tem dois filhos
    else {
      No* temp = raiz->direita;
      while (temp->esquerda != NULL) {
        temp = temp->esquerda;
      }
      raiz->ID = temp->ID;
      strcpy(raiz->nome, temp->nome);
      raiz->idade = temp->idade;
      raiz->telefone = temp->telefone;
      strcpy(raiz->endereco, temp->endereco);
      raiz->direita = excluir(raiz->direita, temp->ID);
    }
  }
  return raiz;
}

// Modifica os dados de um nó
void modificar(No* raiz, int ID, char nome[50], int idade, long telefone, char endereco[100]) {
  if (raiz == NULL) {
    printf("O nó %d não existe na árvore!\n", ID);
  } else if (ID > raiz->ID) {
    modificar(raiz->direita, ID, nome, idade, telefone, endereco);
  } else if (ID < raiz->ID) {
    modificar(raiz->esquerda, ID, nome, idade, telefone, endereco);
  } else {
    strcpy(raiz->nome, nome);
    raiz->idade = idade;
    raiz->telefone = telefone;
    strcpy(raiz->endereco, endereco);
    printf("Nó %d modificado com sucesso!\n", raiz->ID);
  }
}

// Insere uma materia ao nó
void inserir_materia(No* raiz, int ID, char nome_materia[50], float nota) {
  if (raiz == NULL) {
    printf("O nó %d não existe na árvore!\n", ID);
  } else if (ID > raiz->ID) {
    inserir_materia(raiz->direita, ID, nome_materia, nota);
  } else if (ID < raiz->ID) {
    inserir_materia(raiz->esquerda, ID, nome_materia, nota);
  } else {
    Materias* novo_materia = criar_materia(nome_materia, nota);
    novo_materia->proxima = raiz->cadeiras;
    raiz->cadeiras = novo_materia;
    printf("Materia %s inserida ao nó %d com sucesso!\n", nome_materia, raiz->ID);
  }
}

// Exclui uma materia de um nó
void excluir_materia(No* raiz, int ID, char nome_materia[50]) {
  if (raiz == NULL) {
    printf("O nó %d não existe na árvore!\n", ID);
  } else if (ID > raiz->ID) {
    excluir_materia(raiz->direita, ID, nome_materia);
  } else if (ID < raiz->ID) {
    excluir_materia(raiz->esquerda, ID, nome_materia);
  } else {
    Materias* temp = raiz->cadeiras;
    Materias* anterior = NULL;
    while (temp != NULL && strcmp(temp->nome_materia, nome_materia) != 0) {
      anterior = temp;
      temp = temp->proxima;
    }
    if (temp == NULL) {
      printf("Materia %s não está no nó %d!\n", nome_materia, raiz->ID);
    } else {
      if (anterior == NULL) {
        raiz->cadeiras = temp->proxima;
      } else {
        anterior->proxima = temp->proxima;
      }
      printf("Materia %s excluida do nó %d com sucesso!\n", nome_materia, raiz->ID);
      free(temp);
    }
  }
}

// Modifica os dados de uma materia
void modificar_materia(No* raiz, int ID, char nome_materia[50], float nota) {
  if (raiz == NULL) {
    printf("O nó %d não existe na árvore!\n", ID);
  } else if (ID > raiz->ID) {
    modificar_materia(raiz->direita, ID, nome_materia, nota);
  } else if (ID < raiz->ID) {
    modificar_materia(raiz->esquerda, ID, nome_materia, nota);
  } else {
    Materias* temp = raiz->cadeiras;
    while (temp != NULL && strcmp(temp->nome_materia, nome_materia) != 0) {
      temp = temp->proxima;
    }
    if (temp == NULL) {
      printf("Materia %s não está no nó %d!\n", nome_materia, raiz->ID);
    } else {
      temp->nota = nota;
      printf("Materia %s modificada do nó %d com sucesso!\n", nome_materia, raiz->ID);
    }
  }
}

// Imprime a árvore
void imprimir_arvore(No* raiz) {
  if (raiz != NULL) {
    printf("ID: %d\n", raiz->ID);
    printf("Nome: %s\n", raiz->nome);
    printf("Idade: %d\n", raiz->idade);
    printf("Telefone: %ld\n", raiz->telefone);
    printf("Endereço: %s\n", raiz->endereco);
    printf("Materias:\n");
    Materias* temp = raiz->cadeiras;
    while (temp != NULL) {
      printf("\t%s.............Nota: %.2f\n", temp->nome_materia, temp->nota);
      temp = temp->proxima;
    }
    printf("\n");
    imprimir_arvore(raiz->esquerda);
    imprimir_arvore(raiz->direita);
  }
}

// Limpa a árvore
void limpar_arvore(No* raiz) {
  if (raiz != NULL) {
    Materias* temp = raiz->cadeiras;
    while (temp != NULL) {
      Materias* aux = temp->proxima;
      free(temp);
      temp = aux;
    }
    limpar_arvore(raiz->esquerda);
    limpar_arvore(raiz->direita);
    free(raiz);
  }
}

// Terminal
void terminal(No* raiz) {
  int opcao;
  int ID;
  char nome[50];
  int idade;
  long telefone;
  char endereco[100];
  char nome_materia[50];
  float nota;
  printf("\n\n");
  printf("\t\t\t\t\t\tÁrvore Binária de Busca\n\n");
  printf("\t\t\t\t\t\t    Menu\n\n");
  printf("\t\t\t\t1 - Inserir um nó\n");
  printf("\t\t\t\t2 - Excluir um nó\n");
  printf("\t\t\t\t3 - Modificar os dados de um nó\n");
  printf("\t\t\t\t4 - Inserir uma materia a um nó\n");
  printf("\t\t\t\t5 - Excluir uma materia de um nó\n");
  printf("\t\t\t\t6 - Modificar os dados de uma materia\n");
  printf("\t\t\t\t7 - Imprimir árvore\n");
  printf("\t\t\t\t0 - Sair\n\n");
  printf("Digite a opção desejada: ");
  scanf("%d", &opcao);
  switch(opcao) {
    case 1:
      printf("Digite o ID do nó: ");
      scanf("%d", &ID);
      printf("Digite o nome do nó: ");
      scanf("%s", nome);
      printf("Digite a idade do nó: ");
      scanf("%d", &idade);
      printf("Digite o telefone do nó: ");
      scanf("%ld", &telefone);
      printf("Digite o endereço do nó: ");
      scanf("%s", endereco);
      raiz = inserir(raiz, ID, nome, idade, telefone, endereco);
      break;
    case 2:
      printf("Digite o ID do nó a ser excluído: ");
      scanf("%d", &ID);
      raiz = excluir(raiz, ID);
      break;
    case 3:
      printf("Digite o ID do nó a ser modificado: ");
      scanf("%d", &ID);
      printf("Digite o novo nome do nó: ");
      scanf("%s", nome);
      printf("Digite a nova idade do nó: ");
      scanf("%d", &idade);
      printf("Digite o novo telefone do nó: ");
      scanf("%ld", &telefone);
      printf("Digite o novo endereço do nó: ");
      scanf("%s", endereco);
      modificar(raiz, ID, nome, idade, telefone, endereco);
      break;
    case 4:
      printf("Digite o ID do nó a inserir uma materia: ");
      scanf("%d", &ID);
      printf("Digite o nome da materia: ");
      scanf("%s", nome_materia);
      printf("Digite a nota da materia: ");
      scanf("%f", &nota);
      inserir_materia(raiz, ID, nome_materia, nota);
      break;
    case 5:
      printf("Digite o ID do nó a excluir uma materia: ");
      scanf("%d", &ID);
      printf("Digite o nome da materia a ser excluída: ");
      scanf("%s", nome_materia);
      excluir_materia(raiz, ID, nome_materia);
      break;
    case 6:
      printf("Digite o ID do nó a modificar uma materia: ");
      scanf("%d", &ID);
      printf("Digite o nome da materia a ser modificada: ");
      scanf("%s", nome_materia);
      printf("Digite a nova nota da materia: ");
      scanf("%f", &nota);
      modificar_materia(raiz, ID, nome_materia, nota);
      break;
    case 7:
      imprimir_arvore(raiz);
      break;
    case 0:
      limpar_arvore(raiz);
      break;
    default:
      printf("Opção inválida!\n");
  }
  if (opcao != 0) {
    terminal(raiz);
  }
}
