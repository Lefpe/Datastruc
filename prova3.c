#prova n3 passada
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int locator;
    char date[20];
    float price;
    char destination[50];
    struct Node* left;
    struct Node* right;
} Node;

typedef struct TicketSystem {
    Node* brazil_tree;
    Node* argentina_tree;
} TicketSystem;

Node* create_node(int locator, const char* date, float price, const char* destination) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->locator = locator;
    strcpy(new_node->date, date);
    new_node->price = price;
    strcpy(new_node->destination, destination);
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

int generate_locator() {
    return rand() % 9000 + 1000;
}

Node* insert(Node* root, Node* new_ticket) {
    if (root == NULL) {
        return new_ticket;
    }

    if (new_ticket->locator < root->locator) {
        root->left = insert(root->left, new_ticket);
    } else if (new_ticket->locator > root->locator) {
        root->right = insert(root->right, new_ticket);
    }

    return root;
}

void add_ticket(TicketSystem* system, const char* country, const char* date, float price, const char* destination) {
    int locator = generate_locator();
    Node* new_ticket = create_node(locator, date, price, destination);

    if (strcmp(country, "brazil") == 0) {
        system->brazil_tree = insert(system->brazil_tree, new_ticket);
    } else if (strcmp(country, "argentina") == 0) {
        system->argentina_tree = insert(system->argentina_tree, new_ticket);
    }
}

void search_and_print(Node* root, const char* destination) {
    if (root) {
        search_and_print(root->left, destination);
        if (strcmp(root->destination, destination) == 0) {
            printf("Locator: %d, Date: %s, Price: %.2f, Destination: %s\n", root->locator, root->date, root->price, root->destination);
        }
        search_and_print(root->right, destination);
    }
}

void search_by_destination(TicketSystem* system, const char* country, const char* destination) {
    if (strcmp(country, "brazil") == 0) {
        search_and_print(system->brazil_tree, destination);
    } else if (strcmp(country, "argentina") == 0) {
        search_and_print(system->argentina_tree, destination);
    }
}

void calculate_report(Node* root, float* total_sales, int* num_flights) {
    if (root) {
        calculate_report(root->left, total_sales, num_flights);
        *total_sales += root->price;
        (*num_flights)++;
        calculate_report(root->right, total_sales, num_flights);
    }
}

void generate_report(TicketSystem* system, const char* country) {
    float total_sales = 0;
    int num_flights = 0;

    if (strcmp(country, "brazil") == 0) {
        calculate_report(system->brazil_tree, &total_sales, &num_flights);
        printf("Brazil - Total Sales: %.2f, Number of Flights: %d\n", total_sales, num_flights);
    } else if (strcmp(country, "argentina") == 0) {
        calculate_report(system->argentina_tree, &total_sales, &num_flights);
        printf("Argentina - Total Sales: %.2f, Number of Flights: %d\n", total_sales, num_flights);
    }
}

Node* consolidate_trees(Node* root1, Node* root2) {
    if (root2 == NULL) {
        return root1;
    }
    if (root1 == NULL) {
        return root2;
    }

    root1->right = consolidate_trees(root1->right, root2);
    return consolidate_trees(root1, root2->left);
}

void consolidate_sales(TicketSystem* system) {
    system->brazil_tree = consolidate_trees(system->brazil_tree, system->argentina_tree);
    system->argentina_tree = NULL;
}

int main() {
    srand((unsigned int)time(NULL));

    TicketSystem ticket_system;
    ticket_system.brazil_tree = NULL;
    ticket_system.argentina_tree = NULL;

    // Adiciona passagens
    add_ticket(&ticket_system, "brazil", "2023-01-01", 500, "Rio de Janeiro");
    add_ticket(&ticket_system, "argentina", "2023-01-02", 600, "Buenos Aires");
    // Adicione mais passagens conforme necessário...

    // Busca por destino
    search_by_destination(&ticket_system, "brazil", "Rio de Janeiro");

    // Gera relatório
    generate_report(&ticket_system, "brazil");

    // Consolida vendas no final do ano
    consolidate_sales(&ticket_system);

    // Libera memória (opcional, dependendo do escopo do seu programa)
    // Implemente a função para liberar a memória conforme necessário

    return 0;
}
