#ifndef COBERTURA_H
#define COBERTURA_H
typedef struct {int n; unsigned char *adj;} Grafo;
Grafo *criar_grafo(int n);
void adicionar_aresta(Grafo *g,int u,int v);
void liberar_grafo(Grafo *g);
int eh_cobertura(const Grafo *g,const int *selecionados);
int cobertura_minima_bt(const Grafo *g,int *resultado);
int cobertura_gulosa(const Grafo *g,int *resultado);
#endif
