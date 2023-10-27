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


}

// buscar livros//
void buscarLivros(struct Catalogo *catalogo, char isbn[14]) {
  struct Livros *aux = catalogo->head;
  //usado uma função auxiliar//

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
void listaAlfabetica(struct Catalogo *catalogo, int ordem) {
    struct Livros *livro = catalogo->head;
    if (ordem == 1) {
        // Listar em ordem alfabética crescente (A a Z)
        printf("-- Lista em ordem alfabética crescente --\n");
        while (livro) {
            printf("Nome do livro: %s\n", livro->titutlo);
            printf("ISBN: %s\n", livro->isbn);
            printf("Autor: %s\n", livro->autor);
            printf("Ano de publicação: %d\n", livro->ano);
            printf("Número de exemplares: %d\n", livro->numexemplares);
            printf("===============================\n");
            livro = livro->tale;
        }
    } else if (ordem == 2) {
        // Listar em ordem alfabética decrescente (Z a A)
        printf("-- Lista em ordem alfabética decrescente --\n");

        // Encontre o último livro
        while (livro->tale != NULL) {
            livro = livro->tale;
        }

        while (livro) {
            printf("Nome do livro: %s\n", livro->titutlo);
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
//fim da função
//listar por ano//
void informarquantidade (struct Catalogo *catalogo, int ano){
  struct Livros *atual = catalogo->head;
  int quantidade = 0;
  while (atual != NULL) {
    if (atual->ano == ano) {
      quantidade++;
      
    }
    else {
      printf("não há livros nesta data");
    }
  }
}

//fim da função//
//nome de autor por ano //
void listarnomeautoraposano (struct Catalogo *catalogo, char autor[60], int ano){
  struct Livros *atual = catalogo->head;
  int livroEncontrado = 0; // Variável para verificar se há livros do autor na data especificada
  
  while (atual != NULL) {
    if (atual->ano == ano) {
      if (strcmp(atual->autor, autor) == 0) {
        printf("%s\n", atual->titutlo);
        livroEncontrado = 1; // Configura a variável para indicar que há pelo menos um livro do autor na data especificada
      }
    }
    atual = atual->tale;
  }
  
  if (!livroEncontrado) {
    printf("Não há livros do autor %s nesta data.\n", autor);
  }
}

//fim da função//

//remover livros por ano//
void removerporano(struct Catalogo *catalogo, int ano) {
  struct Livros *atual = catalogo->head;
  struct Livros *prev = NULL;
  while (atual != NULL) {
    if (atual->ano == ano) {
      if (prev == NULL) {
        catalogo->head = atual->tale;
      } else {
        prev->tale = atual->tale;
      }
      free(atual);
      atual = prev != NULL ? prev->tale : catalogo->head;
    } else {
      prev = atual;
      atual = atual->tale;
    }
  }
}
//fim da função//


int main(void) {
    struct Catalogo *catalogo;
    catalogo = (struct Catalogo *)malloc(sizeof(struct Catalogo));
    catalogo->head = NULL;
    catalogo->tale = NULL;

    int options;
    int del;
    int busca;
//optei por usar um menu desta forma para que a lista ficasse em loop, pois usando somente switch, a lista fechava ao inserir um valor, não armazenando e não conseguindo acessar alguns ponteiros//
    while (1) {
    printf("\n-- Catálogo --\n");
    printf("Digite a opção que você deseja:\n");
    printf("1. Inserir Livros\n");
    printf("2. Deletar Livros\n");
    printf("3. Buscar Livro\n");
    printf("4. Exibir Catálogo\n");
    printf("5. listar em ordem alfabética");
    printf("6. Sair\n");
    printf("8.deletar livros por ano");
    printf ("7.informar livros por ano");

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
        printf("Deseja buscar após determinado ano? (1 - Sim / 2 - Não): ");
        scanf("%d", &buscaporano);

        if (buscaporano == 1) {
          printf("Digite o ano inicial de publicação dos livros a serem "
                 "pesquisados: ");
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
    }
    if (buscaporano == 2) {

    } else {
      printf("Exibindo dados dos livros do autor %s:\n", autor_search);
    }
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
  }
  else {
    printf("Opção inválida.\n");
  }
  break;

      case 4:
          printf("-- Exibir Catálogo --\n");
          exibirCatalogo(catalogo);
          break;

      case 5:
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
                break;
        case 6:
         free(catalogo);
                exit(0);
        break;
        case 7:
           void informarQuantidadeLivrosPorAno(struct Catalogo *catalogo, int anoInicio, int anoFim) {
  struct Livros *atual = catalogo->head;
  int quantidade = 0;
  while (atual != NULL) {
    if (atual->ano >= anoInicio && atual->ano <= anoFim) {
      quantidade++;
    }
    atual = atual->tale;
  }
  printf("Quantidade de livros publicados entre %d e %d: %d\n", anoInicio, anoFim, quantidade);
}
   
        break;
      case 8:
        //deletar livros por ano //
  printf("Digite o ano inicial de publicação dos livros a serem pesquisados: ");
  scanf("%d", &lo);
  printf("Deseja buscar após determinado ano? (1 - Sim / 2 - Não): ");
  scanf("%d", &buscaporano);
  
  if (buscaporano == 1) {
    int anoDeletar;
    printf("Digite o ano inicial de publicação dos livros a serem deletados: ");
    scanf("%d", &anoDeletar);

    // Código para deletar livros por ano
    removerporano(catalogo, anoDeletar);
      
  } else if (buscaporano == 2) {
    informarquantidade(catalogo, lo);
  }
      break;

            default:
                printf("Opção inválida. Tente novamente.\n");
              
                break;
        
        
    }
    }
}
// acho que tem algum bug em informar por ano, provavelmente por parametros de
// chaves, já que fiquei tão focado na lógica e não vi estes detalhes//
