#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H
#include "grafo.h"
int bellman_ford(GrafoListaPonderado *g,int origem,int *dist,int *pred);
void reconstruir_ciclo_negativo(int n,int vertice,int *pred);
#endif
