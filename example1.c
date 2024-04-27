
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa



typedef struct graph {
    int vertices;
    int *visited;
    struct Node **adj_list;
} GPH;

typedef struct stack {
    int top;
    int capacity;
    int *array;
} STK;

NODE *create_node(int v) {
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void add_edge(GPH *g, int src, int dest) {
    NODE *nn = create_node(dest);
    nn->next = g->adj_list[src];
    g->adj_list[src] = nn;
    nn = create_node(src);
    nn->next = g->adj_list[dest];
    g->adj_list[dest] = nn;
}

GPH *create_graph(int v) {
    int i;
    GPH *graf = malloc(sizeof(GPH));
    graf->vertices = v;
    graf->adj_list = malloc(sizeof(NODE *));
    graf->visited = malloc(sizeof(int) * v);

    for (i = 0; i < v; i++) {
        graf->adj_list[i] = NULL;
        graf->visited[i] = 0;
    }
    return graf;
}

STK *create_stack(int scap) {
    STK *s = malloc(sizeof(STK));
    s->array = malloc(scap * sizeof(int));
    s->top = -1;
    s->capacity = scap;
    return s;
}

void push(int pushed, STK *stack) {
    stack->top = stack->top + 1;
    stack->array[stack->top] = pushed;
}

void DFS(GPH *graf, STK *stack, int vertex_number) {
    NODE *adj_list = graf->adj_list[vertex_number];
    NODE *aux = adj_list;
    graf->visited[vertex_number] = 1;
    printf("%d ", vertex_number);
    push(vertex_number, stack);
    while (aux != NULL) {
        int con_ver = aux->data;
        if (graf->visited[con_ver] == 0) {
            DFS(graf, stack, con_ver);
        }
        aux = aux->next;
    }
}

void insert_edges(GPH *graf, int edg_nr, int nr_vertices) {
    int src, dest, i;
    printf("adauga %d munchii (de la 1 la %d)\n", edg_nr, nr_vertices);
    for (i = 0; i < edg_nr; i++) {
        scanf("%d%d", &src, &dest);
        add_edge(graf, src, dest);
    }
}

void wipe(GPH *g, int nr_vertices) {
    for (int i = 0; i < nr_vertices; i++) {
        g->visited[i] = 0;
    }
}

void can_be_reached(GPH *graf, int nr_vertices, STK *s1, STK *s2)// 0 sau 1 daca poate fi sau nu ajuns
{
    int *canbe = calloc(5, sizeof(int));
    for (int i = 0; i < nr_vertices; i++) // aici i tine loc de numar adica de restaurant
    {
        for (int j = 0; j < 5; j++) {
            DFS(graf, s1, i);
            wipe(graf, nr_vertices);
            DFS(graf, s2, j);
            for (j = 0; j < nr_vertices; j++) {
                for (i = 0; i < nr_vertices; i++) {
                    if ((s1->array[i] == j) && (s2->array[j] == i)) {
                        *canbe = 1;
                    }
                }
            }
        }
    }
    if (*canbe) {
        printf("da ma se poate");
    } else {
        printf("nu ma nu am ce sa fac");
    }
}


int main() {

    int nrv;
    int edg_nr;
    int src, dest;
    int i;
    int vortex_1;
    int vortex_2;
    int ans;

    printf("cate noduri are girafa?");
    scanf("%d", &nrv);

    printf("cate muchii are giraful?");
    scanf("%d", &edg_nr);

    GPH *graf = create_graph(nrv);
    STK *s1 = create_stack(2 * nrv);
    STK *s2 = create_stack(2 * nrv);

    insert_edges(graf, edg_nr, nrv);
    can_be_reached(graf, nrv, s1, s2);
    //totul pare sa mearga
}