#ifndef TPS_H
#define TPS_H
#include "hamiltoniano.h"
/* Matriz de custos completa, em ordem linha-major. */
int *grafo_para_tsp(const Grafo*g);
int tsp_forca_bruta(const int*pesos,int n,int *rota);
int tsp_vizinho_mais_proximo(const int*pesos,int n,int *rota);
int tsp_insercao(const int*pesos,int n,int *rota);
#endif
