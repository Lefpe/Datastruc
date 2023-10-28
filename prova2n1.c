#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Livros {
  char isbn[14];
  char titulo[60];
  int ano;
  char autor[60];
  int numexemplares;
  struct Livros *head;
  struct Livros *tail;
} Livros;

typedef struct Catalogo {
  struct Livros *head;
  struct Livros *tail;
} Catalogo;

void inserirLivros(struct Catalogo *catalogo, char isbn[14], char titulo[60],
                   int numexemplares, int ano, char autor[60]) {
  struct Livros *novo = (struct Livros *)malloc(sizeof(struct Livros));
  strcpy(novo->isbn, isbn);
  strcpy(novo->titulo, titulo);
  novo->numexemplares = numexemplares;
  novo->ano = ano;
  strcpy(novo->autor, autor);
  novo->head = NULL;
  novo->tail = NULL;

  if (catalogo->head == NULL) {
    catalogo->head = novo;
    catalogo->tail = novo;
  } else {
    struct Livros *atual = catalogo->head;
    while (atual->tail != NULL) {
      if (strcmp(atual->isbn, isbn) == 0) {
        atual->numexemplares += numexemplares;
        free(novo);
        return;
      } else if (strcmp(atual->isbn, isbn) > 0) {
        novo->head = atual;
        novo->tail = atual->tail;
        if (atual->tail) {
          atual->tail->head = novo;
        } else {
          catalogo->head = novo;
        }
        atual->tail = novo;
        return;
      } else if (atual->tail == NULL) {
        atual->tail = novo;
        return;
      }
      atual = atual->head;
    }
  }
}

void deletarLivros(struct Catalogo *catalogo, char isbn[14], int nremover) {
  struct Livros *atual = catalogo->head;

  while (atual != NULL) {
    if (strcmp(atual->isbn, isbn) == 0) {
      if (atual->numexemplares <= nremover) {
        if (atual->head != NULL) {
          atual->head->tail = atual->tail;
        } else {
          catalogo->head = atual->tail;
        }
        if (atual->tail != NULL) {
          atual->tail->head = atual->head;
        }
        free(atual);
        return;
      } else {
        atual->numexemplares -= nremover;
        return;
      }
    }
    atual = atual->tail;
  }

  printf("Livro com ISBN %s não encontrado!", isbn);
}

void removerporano(struct Catalogo *catalogo, int ano) {
  struct Livros *atual = catalogo->head;
  struct Livros *prev = NULL;
  while (atual != NULL) {
    if (atual->ano == ano) {
      if (prev == NULL) {
        catalogo->head = atual->tail;
      } else {
        prev->tail = atual->tail;
      }
      free(atual);
      atual = prev != NULL ? prev->tail : catalogo->head;
    } else {
      prev = atual;
      atual = atual->tail;
    }
  }
}

void informarquantidade(struct Catalogo *catalogo, int ano) {
  struct Livros *atual = catalogo->head;
  int quantidade = 0;
  while (atual != NULL) {
    if (atual->ano == ano) {
      quantidade++;
    }
    atual = atual->tail;
  }
  if (quantidade == 0) {
    printf("Não há livros no catálogo do ano %d\n", ano);
  } else {
    printf("Quantidade de livros publicados no ano %d: %d\n", ano, quantidade);
  }
}

void listarnomeautoraposano(struct Catalogo *catalogo, char autor[60], int ano) {
  struct Livros *atual = catalogo->head;
  int livroEncontrado = 0;

  while (atual != NULL) {
    if (atual->ano == ano && strcmp(atual->autor, autor) == 0) {
      printf("%s\n", atual->titulo);
      livroEncontrado = 1;
    }
    atual = atual->tail;
  }

  if (!livroEncontrado) {
    printf("Não há livros do autor %s no ano %d.\n", autor, ano);
  }
}

void buscarLivros(struct Catalogo *catalogo, char isbn[14]) {
  struct Livros *aux = catalogo->head;

  while (aux != NULL) {
    if (strcmp(aux->isbn, isbn) == 0) {
      printf("Nome do livro: %s\n", aux->titulo);
      printf("ISBN: %s\n", aux->isbn);
      printf("Número de exemplares: %d\n", aux->numexemplares);
      printf("Ano de publicação: %d\n", aux->ano);
      printf("Autor: %s\n", aux->autor);
      return;
    }

    aux = aux->tail;
  }

  printf("Livro com ISBN %s não encontrado!", isbn);
}

void exibirCatalogo(struct Catalogo *catalogo) {
  struct Livros *livro = catalogo->head;
  printf("-- Catálogo de Livros --\n");
  while (livro != NULL) {
    printf("Nome do livro: %s\n", livro->titulo);
    printf("ISBN: %s\n", livro->isbn);
    printf("Autor: %s\n", livro->autor);
    printf("Ano de publicação: %d\n", livro->ano);
    printf("Número de exemplares: %d\n", livro->numexemplares);
    printf("===============================\n");
    livro = livro->tail;
  }
}

void listaAlfabetica(struct Catalogo *catalogo, int ordem) {
  struct Livros *livro = catalogo->head;
  if (ordem == 1) {
    printf("-- Lista em ordem alfabética crescente --\n");
    while (livro) {
      printf("Nome do livro: %s\n", livro->titulo);
      printf("ISBN: %s\n", livro->isbn);
      printf("Autor: %s\n", livro->autor);
      printf("Ano de publicação: %d\n", livro->ano);
      printf("Número de exemplares: %d\n", livro->numexemplares);
      printf("===============================\n");
      livro = livro->tail;
    }
  } else if (ordem == 2) {
    printf("-- Lista em ordem alfabética decrescente --\n");
    while (livro->tail != NULL) {
      livro = livro->tail;
    }
    while (livro) {
      printf("Nome do livro: %s\n", livro->titulo);
      printf("ISBN: %s\n", livro->isbn);
      printf("Autor: %s\n", livro->autor);
      printf("Ano de publicação: %d\n", livro->ano);
      printf("Número de exemplares: %d\n", livro->numexemplares);
      printf("===============================\n");
      livro = livro->head;
    }
  } else {
    printf("Opção inválida para ordenação alfabética.\n");
  }
}

int main(void) {
  struct Catalogo *catalogo;
  catalogo = (struct Catalogo *)malloc(sizeof(struct Catalogo));
  catalogo->head = NULL;
  catalogo->tail = NULL;

  int options;
  int del;
  int busca;
  int lo;
  int buscaporano;

  while (1) {
    printf("\n-- Catálogo --\n");
    printf("Digite a opção que você deseja:\n");
    printf("1. Inserir Livros\n");
    printf("2. Deletar Livros\n");
    printf("3. Buscar Livro\n");
    printf("4. Exibir Catálogo\n");
    printf("5. Listar em ordem alfabética\n");
    printf("6. Sair\n");

    scanf("%d", &options);

    switch (options) {
      case 1: {
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
      }
      case 2: {
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
      }
      case 3: {
        printf("-- Buscar Livro --\n");
        printf("Selecione a forma de busca:\n");
        printf("1. Por ISBN\n");
        printf("2. Por Autor\n");

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
          printf("Deseja buscar após determinado ano? (1 - Sim / 2 - Não): ");
          scanf("%d", &buscaporano);

          if (buscaporano == 1) {
            int lo;
            printf("Digite o ano inicial de publicação dos livros a serem pesquisados: ");
            scanf("%d", &lo);
            printf("Exibindo dados dos livros do autor %s a partir do ano %d:\n",
                  autor_search, lo);
            listarnomeautoraposano(catalogo, autor_search, lo);
          } else if (buscaporano == 2) {
            printf("Exibindo dados dos livros do autor %s:\n", autor_search);
            listarnomeautoraposano(catalogo, autor_search, 0);
          } else {
            printf("Opção inválida.\n");
          }
        }
        break;
      }
      case 4: {
        printf("-- Exibir Catálogo --\n");
        exibirCatalogo(catalogo);
        break;
      }
      case 5: {
        printf("Lista em ordem alfabética:\n");
        printf("1. Ordem crescente (A a Z)\n");
        printf("2. Ordem decrescente (Z a A)\n");
        scanf("%d", &lo);

        if (lo == 1) {
          listaAlfabetica(catalogo, 1);
        } else if (lo == 2) {
          listaAlfabetica(catalogo, 2);
        } else {
          printf("Opção inválida.\n");
        }
        break;
      }
      case 6: {
        free(catalogo);
        exit(0);
        break;
      }
      default:
        printf("Opção inválida. Tente novamente.\n");
        break;
    }
  }
  return 0;
}
//havia esquecido de declarar variáveis//
