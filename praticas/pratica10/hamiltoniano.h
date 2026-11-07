#ifndef HAMILTONIANO_H
#define HAMILTONIANO_H
typedef struct {int n;unsigned char *adj;} Grafo;
Grafo *criar_grafo(int n);
void adicionar_aresta(Grafo*g,int u,int v);
void liberar_grafo(Grafo*g);
/* caminho recebe n vertices; ciclo exige tambem aresta de retorno */
int encontrar_caminho_hamiltoniano_bt(const Grafo*g,int *caminho,int ciclo);
#endif
