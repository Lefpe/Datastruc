#include <stdio.h>
#include <stdlib.h>

typedef struct LISTA {
    int numeros;
    struct LISTA* prox;
} Lista;

Lista* novo(int numeros) {
    Lista* novon = (Lista*)malloc(sizeof(Lista));
    novon->numeros = numeros;
    novon->prox = NULL;
    return novon;
}

void insertSorted(Lista** head, int numeros) {
    Lista* novon = novo(numeros);
    if (*head == NULL || numeros < (*head)->numeros) {
        novon->prox = *head;
        *head = novon;
    } else {
        Lista* atual = *head;
        while (atual->prox != NULL && atual->prox->numeros < numeros) {
            atual = atual->prox;
        }
        novon->prox = atual->prox;
        atual->prox = novon;
    }
}

void displayList(Lista* head) {
    Lista* atual = head;
    while (atual != NULL) {
        printf("%d -> ", atual->numeros);
        atual = atual->prox;
    }
    printf("NULL\n");
}

int main() {
    Lista* head = NULL;
    int num;

    printf("Digite um número (ou qualquer valor não numérico para parar): ");
    while (scanf("%d", &num) == 1) {
        insertSorted(&head, num);
        printf("Digite um número (ou qualquer valor não numérico para parar): ");
    }

    printf("Lista encadeada ordenada:\n");
    displayList(head);

    // Liberar a memória alocada para os nós da lista
    Lista* atual = head;
    while (atual != NULL) {
        Lista* temp = atual;
        atual = atual->prox;
        free(temp);
    }

    return 0;
}
