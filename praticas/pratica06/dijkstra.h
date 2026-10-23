#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "grafo.h"
typedef struct {int vertice,distancia;} NoHeap;
typedef struct {NoHeap *dados;int capacidade,tamanho,*posicao;} MinHeap;
MinHeap *criar_min_heap(int capacidade);
void liberar_min_heap(MinHeap*h);
NoHeap extrair_minimo(MinHeap*h);
void diminuir_chave(MinHeap*h,int vertice,int distancia);
void dijkstra(GrafoListaPonderado*g,int origem,int *dist,int *pred);
void reconstruir_caminho(int origem,int destino,int *pred);
#endif
