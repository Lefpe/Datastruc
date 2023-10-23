#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// organização dos dados//
typedef struct Livros {
  char isbn[14];
  char titutlo[60];
  int ano;
  char autor[60];
  int numexemplares;
  struct Livros *head;
  struct Livros *tale;
} Livros;

// esta struct é para armazenar o catalogo//
typedef struct Catalogo {
  struct Livros *head;
  struct Livros *tale;
} Catalogo;

// inserir livros//
void inserirLivros(struct Catalogo *catalogo, char isbn[14], char titulo[60],
                   int numexemplares, int ano, char autor[60]) {
  struct Livros *novo = (struct Livros *)malloc(sizeof(struct Livros));
  strcpy(novo->isbn, isbn);
  strcpy(novo->titutlo, titulo);
  novo->numexemplares = numexemplares;
  novo->ano = ano;
  strcpy(novo->autor, autor);
  novo->head = NULL;
  novo->tale = NULL;
  // criação do catalogo //
  if (catalogo->head == NULL) {
    catalogo->head = novo;
    catalogo->tale = novo;
  } else {
    struct Livros *atual = catalogo->head;
    while (atual->tale != NULL) {
      if (strcmp(atual->isbn, isbn) == 0) {
        atual->numexemplares += numexemplares;
        free(novo);
        return;
      } else if (strcmp(atual->isbn, isbn) > 0) {
        novo->head = atual;
        novo->tale = atual->tale;
        if (atual->tale) {
          atual->tale->head = novo;
        } else {
          catalogo->head = novo;
        }
        atual->tale = novo;
        return;
      } else if (atual->tale == NULL) {
        atual->tale = novo;
        return;
      }
      atual = atual->head;
    }
  }
}

// deletar livros//
void deletarLivros(struct Catalogo *catalogo, char isbn[14], int nremover) {
  struct Livros *atual = catalogo->head;

  while (atual != NULL) {
    if (strcmp(atual->isbn, isbn) == 0) {
      if (atual->numexemplares <= nremover) {
        if (atual->head != NULL) {
          atual->head->tale = atual->tale;
        } else {
          catalogo->head = atual->tale;
        }
        if (atual->tale != NULL) {
          atual->tale->head = atual->head;
        }
        free(atual);
        return;
      } else {
        atual->numexemplares -= nremover;
        return;
      }
    }

    atual = atual->tale;
  }

  printf("Livro com ISBN %s não encontrado!", isbn);
}

// buscar livros//
void buscarLivros(struct Catalogo *catalogo, char isbn[14]) {
  struct Livros *aux = catalogo->head;

  while (aux != NULL) {
    if (strcmp(aux->isbn, isbn) == 0) {
      printf("Nome do livro: %s\n", aux->titutlo);
      printf("ISBN: %s\n", aux->isbn);
      printf("Numero de exemplares: %d\n", aux->numexemplares);
      printf("Ano de publicação: %d\n", aux->ano);
      printf("Autor: %s\n", aux->autor);
      return;
    }

    aux = aux->tale;
  }

  printf("Livro com ISBN %s não encontrado!", isbn);
}

// exibir catalogo//
void exibirCatalogo(struct Catalogo *catalogo) {
  struct Livros *livro = catalogo->head;
  while (livro != NULL) {
    printf("Nome do livro: %s\n", livro->titutlo);
    printf("ISBN: %s\n", livro->isbn);
    printf("Autor: %s\n", livro->autor);
    printf("Ano de publicação: %d\n", livro->ano);
    printf("Número de exemplares: %d\n", livro->numexemplares);
    printf("===============================\n");
    livro = livro->tale;
  }
}
//lista em ordem alfabetica//
//fim da função


int main(void) {
    struct Catalogo *catalogo;
    catalogo = (struct Catalogo *)malloc(sizeof(struct Catalogo));
    catalogo->head = NULL;
    catalogo->tale = NULL;

    int options;
    int del;
    int busca;

    while (1) {
      printf("\n-- Catálogo --\n");
      printf("Digite a opção que você deseja:\n");
      printf("1. Inserir Livros\n");
      printf("2. Deletar Livros\n");
      printf("3. Buscar Livro\n");
      printf("4. Exibir Catálogo\n");
      printf("5. Sair\n");

      scanf("%d", &options);
      switch (options){
      case 1:
          printf("-- Inserir Livro --\n");
          char isbn[14];
          char titulo[60];
          char autor[60];
          int numexemplares;
          int ano;

          printf("Digite o ISBN: ");
          scanf("%s", isbn);
          printf("Digite o Título: ");
          scanf(" %[^\n]", titulo);
          printf("Digite o Autor: ");
          scanf(" %[^\n]", autor);
          printf("Digite o Número de Exemplares: ");
          scanf("%d", &numexemplares);
          printf("Digite o Ano de Publicação: ");
          scanf("%d", &ano);

          inserirLivros(catalogo, isbn, titulo, numexemplares, ano, autor);
          break;

      case 2:
          printf("-- Deletar Livro --\n");
          char isbn_del[14];
          printf("Digite o ISBN do livro a ser removido: ");
          scanf("%s", isbn_del);

          printf("Exibindo dados do livro:\n");
          buscarLivros(catalogo, isbn_del);

          printf("Deseja remover exemplares deste livro? (1-Sim / 2-Não): ");
          scanf("%d", &del);

          if (del == 1) {
              int nremover;
              printf("Quantidade de exemplares a remover: ");
              scanf("%d", &nremover);
              deletarLivros(catalogo, isbn_del, nremover);
          } else if (del == 2) {
              printf("Operação de remoção cancelada.\n");
          } else {
              printf("Opção inválida.\n");
          }
          break;

      case 3:
          printf("-- Buscar Livro --\n");
          printf("Selecione a forma de busca:\n");
          printf("1. Por ISBN\n");
          printf("2. Por Autor\n");
          printf("Qualquer outra tecla para sair\n");
          scanf("%d", &busca);

          if (busca == 1) {
              char isbn_search[14];
              printf("Digite o ISBN do livro: ");
              scanf("%s", isbn_search);
              printf("Exibindo dados do livro:\n");
              buscarLivros(catalogo, isbn_search);
          } else if (busca == 2) {
              char autor_search[60];
              printf("Digite o nome do autor: ");
              scanf(" %[^\n]", autor_search);
              printf("Exibindo dados dos livros do autor:\n");
              // Código para buscar e exibir livros por autor
              struct Livros *aux = catalogo->head;
              while (aux != NULL) {
                  if (strcmp(aux->autor, autor_search) == 0) {
                      printf("Nome do livro: %s\n", aux->titutlo);
                      printf("ISBN: %s\n", aux->isbn);
                      printf("Número de exemplares: %d\n", aux->numexemplares);
                      printf("Ano de publicação: %d\n", aux->ano);
                      printf("Autor: %s\n", aux->autor);
                      printf("===============================\n");
                  }
                  aux = aux->tale;
              }
          } else {
              printf("Opção inválida.\n");
          }
          break;

      case 4:
          printf("-- Exibir Catálogo --\n");
          exibirCatalogo(catalogo);
          break;

      case 5:
            free(catalogo);
                exit(0);
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
    }
    }
}