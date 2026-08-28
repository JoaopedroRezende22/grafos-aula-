#include <stdlib.h>
#include "grafo_matriz.h"

GrafoMatriz *criar_grafo_matriz(int n) {
    if (n <= 0) {
        return NULL;
    }

    GrafoMatriz *g = malloc(sizeof(GrafoMatriz));
    if (g == NULL) {
        return NULL;
    }

    g->n = n;
    g->adj = malloc(n * sizeof(int *));
    if (g->adj == NULL) {
        free(g);
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        g->adj[i] = calloc(n, sizeof(int));

        if (g->adj[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(g->adj[j]);
            }

            free(g->adj);
            free(g);
            return NULL;
        }
    }

    return g;
}

void inserir_aresta_matriz(GrafoMatriz *g, int u, int v) {
    if (g == NULL || u < 0 || u >= g->n ||
        v < 0 || v >= g->n || u == v) {
        return;
    }

    g->adj[u][v] = 1;
    g->adj[v][u] = 1;
}

void remover_aresta_matriz(GrafoMatriz *g, int u, int v) {
    if (g == NULL || u < 0 || u >= g->n ||
        v < 0 || v >= g->n) {
        return;
    }

    g->adj[u][v] = 0;
    g->adj[v][u] = 0;
}

int grau_matriz(GrafoMatriz *g, int u) {
    if (g == NULL || u < 0 || u >= g->n) {
        return -1;
    }

    int grau = 0;

    for (int v = 0; v < g->n; v++) {
        grau += g->adj[u][v];
    }

    return grau;
}

int sao_adjacentes_matriz(GrafoMatriz *g, int u, int v) {
    if (g == NULL || u < 0 || u >= g->n ||
        v < 0 || v >= g->n) {
        return 0;
    }

    return g->adj[u][v];
}

void liberar_grafo_matriz(GrafoMatriz *g) {
    if (g == NULL) {
        return;
    }

    for (int i = 0; i < g->n; i++) {
        free(g->adj[i]);
    }

    free(g->adj);
    free(g);
}