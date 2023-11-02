#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct links {
  char nome[50];
  char link[100];
};
struct pilhas {
  int front;           // topo da pilha //
  int second;          // segunda pilha //
  int size;            // tamanho da pilha //
  struct links *array; // array de pilhas //
};
struct inverso {
  struct pilhas inversa;
};

void criarpilha(struct pilhas *p, int s) {
  p->front = -1;
  p->second = s;
  p->struct links *array = (struct links *)malloc(s * sizeof(struct links));
}
void ordeminverso(struct pilhas *p) {
  struct inverso *inversa;
  p->array[p->front].nome = p->array[p->front].link;
}
int main(void) {
  struct pilhas *p;
  int s;
  int options;
  printf("Digite o link: \n");
  scanf("%s", p->array[p->front].link);
  printf("Digite o nome: \n");
  scanf("%s", p->array[p->front].nome);
  printf("Deseja exibir o histórico? \n");
  scanf("%d", &options);
  if (options == 1) {
    printf("--exibindo histórico-- \n");
    printf("%s :nome\n", p->array[p->front].nome);
    printf("%s :link\n", p->array[p->front].link);
    else {
      printf("Encerrando o programa...");
    }
    return 0;
  }
}
