//reposição//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char data[20];
  float peso;
  char destino[50];
} Frete;

typedef struct Node {
  Frete info;
  struct Node *prox;
} Node;

typedef struct {
  Node *inicio;
  Node *fim;
} Fila;


void inicializarFila(Fila *fila) {
  fila->inicio = NULL;
  fila->fim = NULL;
}


void enfileirar(Fila *fila, char data[], float peso, char destino[]) {
  Node *novoNode = (Node *)malloc(sizeof(Node));
  strcpy(novoNode->info.data, data);
  novoNode->info.peso = peso;
  strcpy(novoNode->info.destino, destino);
  novoNode->prox = NULL;

  if (peso > 1000) {
    printf("Atenção: O produto excede 1000 kg e será remanejado para outro caminhão.\n");
  }

  if (fila->fim == NULL) {
    fila->inicio = novoNode;
    fila->fim = novoNode;
  } else {
    fila->fim->prox = novoNode;
    fila->fim = novoNode;
  }
}


Frete desenfileirar(Fila *fila) {
  if (fila->inicio == NULL) {
    Frete freteVazio = {"", 0.0, ""};
    return freteVazio;
  }

  Node *temp = fila->inicio;
  Frete freteDesenfileirado = temp->info;

  fila->inicio = fila->inicio->prox;
  free(temp);

  if (fila->inicio == NULL) {
    fila->fim = NULL;
  }

  return freteDesenfileirado;
}


void transportar(Fila *fila, char destino[]) {
  Fila filaTemporaria;
  inicializarFila(&filaTemporaria);

  float pesoTotal = 0;

  while (fila->inicio != NULL && pesoTotal + fila->inicio->info.peso <= 1000) {
    Frete freteDesenfileirado = desenfileirar(fila);

    if (strcmp(freteDesenfileirado.destino, destino) == 0) {
      pesoTotal += freteDesenfileirado.peso;
      printf("Carga para %s transportada: %s\n", destino, freteDesenfileirado.data);
    } else {
      enfileirar(&filaTemporaria, freteDesenfileirado.data, freteDesenfileirado.peso, freteDesenfileirado.destino);
    }
  }

  
  while (filaTemporaria.inicio != NULL) {
    Frete frete = desenfileirar(&filaTemporaria);
    enfileirar(fila, frete.data, frete.peso, frete.destino);
  }

  if (pesoTotal > 0) {
    printf("Peso total transportado para %s: %.2f kg\n", destino, pesoTotal);
  } else {
    printf("Nenhum frete para %s transportado.\n", destino);
  }
}


float calcularPesoTotal(Fila *fila) {
  float pesoTotal = 0;
  Node *atual = fila->inicio;

  while (atual != NULL) {
    pesoTotal += atual->info.peso;
    atual = atual->prox;
  }

  return pesoTotal;
}


void imprimirFila(Fila *fila) {
  Node *atual = fila->inicio;

  while (atual != NULL) {
    printf("Data: %s, Peso: %.2f kg, Destino: %s\n", atual->info.data, atual->info.peso, atual->info.destino);
    atual = atual->prox;
  }

  printf("\n");
}

int main() {
  Fila fila;
  inicializarFila(&fila);

  int opcao;
  char data[20], destino[50];
  float peso;

  do {
    printf("\n-------MENU-------\n");
    printf("1. Inserir frete\n");
    printf("2. Transportar para destino\n");
    printf("3. Calcular peso total\n");
    printf("0. Sair\n");
    printf("Escolha uma opção:\n");
    scanf("%d", &opcao);

    switch (opcao) {
      case 1:
        printf("Digite a data de transporte (ex: dia/mês/ano): ");
        scanf("%s", data);
        printf("Digite o peso do produto (em kg): ");
        scanf("%f", &peso);
        printf("verificar produto: ");
        scanf("%s", destino);
        enfileirar(&fila, data, peso, destino);
        break;
      case 2:
        printf("Digite o destino para transportar: ");
        scanf("%s", destino);
        transportar(&fila, destino);
        break;
      case 3:
        printf("Peso total na fila: %.2f kg\n", calcularPesoTotal(&fila));
        break;
      case 0:
        printf("Saindo do programa.\n");
        break;
      default:
        printf("Opção inválida.\n");
    }

    imprimirFila(&fila);

  } while (opcao != 0);

  return 0;
}
