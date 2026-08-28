#include <stdlib.h>
#include "grafo_lista.h"

static int existe_aresta_lista(GrafoLista *g, int u, int v) {
    No *atual = g->adj[u];

    while (atual != NULL) {
        if (atual->destino == v) {
            return 1;
        }

        atual = atual->prox;
    }

    return 0;
}

static int inserir_no(GrafoLista *g, int u, int v) {
    No *novo = malloc(sizeof(No));

    if (novo == NULL) {
        return 0;
    }

    novo->destino = v;
    novo->prox = g->adj[u];
    g->adj[u] = novo;

    return 1;
}

GrafoLista *criar_grafo_lista(int n) {
    if (n <= 0) {
        return NULL;
    }

    GrafoLista *g = malloc(sizeof(GrafoLista));

    if (g == NULL) {
        return NULL;
    }

    g->n = n;
    g->adj = calloc(n, sizeof(No *));

    if (g->adj == NULL) {
        free(g);
        return NULL;
    }

    return g;
}

void inserir_aresta_lista(GrafoLista *g, int u, int v) {
    if (g == NULL || u < 0 || u >= g->n ||
        v < 0 || v >= g->n || u == v) {
        return;
    }

    if (existe_aresta_lista(g, u, v)) {
        return;
    }

    if (!inserir_no(g, u, v)) {
        return;
    }

    if (!inserir_no(g, v, u)) {
        No *remover = g->adj[u];
        g->adj[u] = remover->prox;
        free(remover);
    }
}

void remover_aresta_lista(GrafoLista *g, int u, int v) {
    if (g == NULL || u < 0 || u >= g->n ||
        v < 0 || v >= g->n) {
        return;
    }

    No *atual = g->adj[u];
    No *anterior = NULL;

    while (atual != NULL) {
        if (atual->destino == v) {
            if (anterior == NULL) {
                g->adj[u] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }

            free(atual);
            break;
        }

        anterior = atual;
        atual = atual->prox;
    }

    atual = g->adj[v];
    anterior = NULL;

    while (atual != NULL) {
        if (atual->destino == u) {
            if (anterior == NULL) {
                g->adj[v] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }

            free(atual);
            break;
        }

        anterior = atual;
        atual = atual->prox;
    }
}

int grau_lista(GrafoLista *g, int u) {
    if (g == NULL || u < 0 || u >= g->n) {
        return -1;
    }

    int grau = 0;
    No *atual = g->adj[u];

    while (atual != NULL) {
        grau++;
        atual = atual->prox;
    }

    return grau;
}

int sao_adjacentes_lista(GrafoLista *g, int u, int v) {
    if (g == NULL || u < 0 || u >= g->n ||
        v < 0 || v >= g->n) {
        return 0;
    }

    return existe_aresta_lista(g, u, v);
}

void liberar_grafo_lista(GrafoLista *g) {
    if (g == NULL) {
        return;
    }

    for (int i = 0; i < g->n; i++) {
        No *atual = g->adj[i];

        while (atual != NULL) {
            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }

    free(g->adj);
    free(g);
}