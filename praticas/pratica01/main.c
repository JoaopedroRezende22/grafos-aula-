#include <assert.h>
#include <stdio.h>

#include "grafo_lista.h"
#include "grafo_matriz.h"

static void testar_matriz(void) {
    GrafoMatriz *grafo = criar_grafo_matriz(5);

    assert(grafo != NULL);
    inserir_aresta_matriz(grafo, 0, 1);
    inserir_aresta_matriz(grafo, 0, 2);
    inserir_aresta_matriz(grafo, 1, 3);

    assert(grau_matriz(grafo, 0) == 2);
    assert(sao_adjacentes_matriz(grafo, 1, 0));

    remover_aresta_matriz(grafo, 0, 2);
    assert(!sao_adjacentes_matriz(grafo, 0, 2));
    assert(grau_matriz(grafo, 0) == 1);

    printf("Matriz de adjacencia:\n");
    for (int i = 0; i < grafo->n; i++) {
        for (int j = 0; j < grafo->n; j++) {
            printf("%d ", grafo->adj[i][j]);
        }
        printf("\n");
    }

    liberar_grafo_matriz(grafo);
}

static void testar_lista(void) {
    GrafoLista *grafo = criar_grafo_lista(5);

    assert(grafo != NULL);
    inserir_aresta_lista(grafo, 0, 1);
    inserir_aresta_lista(grafo, 0, 2);
    inserir_aresta_lista(grafo, 1, 3);

    assert(grau_lista(grafo, 0) == 2);
    assert(sao_adjacentes_lista(grafo, 1, 0));

    remover_aresta_lista(grafo, 0, 2);
    assert(!sao_adjacentes_lista(grafo, 0, 2));
    assert(grau_lista(grafo, 0) == 1);

    printf("\nLista de adjacencia:\n");
    for (int i = 0; i < grafo->n; i++) {
        printf("%d:", i);
        for (No *atual = grafo->adj[i]; atual != NULL; atual = atual->prox) {
            printf(" %d", atual->destino);
        }
        printf("\n");
    }

    liberar_grafo_lista(grafo);
}

int main(void) {
    testar_matriz();
    testar_lista();

    puts("\nTodos os testes passaram.");

    return 0;
}
