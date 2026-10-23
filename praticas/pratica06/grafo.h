#pragma GCC diagnostic ignored "-Wmisleading-indentation"
#ifndef GRAFO_H
#define GRAFO_H
#include <stdlib.h>
typedef struct No {int destino,peso;struct No *prox;} No;
typedef struct {int n;No **adj;} GrafoListaPonderado;
static inline GrafoListaPonderado *criar_grafo(int n){
 if(n<1)return NULL;
 GrafoListaPonderado *g=malloc(sizeof(*g));if(!g)return NULL;
 g->adj=calloc((size_t)n,sizeof(No*));if(!g->adj){free(g);return NULL;}g->n=n;return g;
}
static inline int adicionar_aresta(GrafoListaPonderado*g,int u,int v,int peso){
 if(!g||u<0||v<0||u>=g->n||v>=g->n)return 0;
 No *e=malloc(sizeof(*e));if(!e)return 0;
 *e=(No){v,peso,g->adj[u]};g->adj[u]=e;return 1;
}
static inline void liberar_grafo(GrafoListaPonderado*g){
 if(!g)return;for(int i=0;i<g->n;i++){No *e=g->adj[i];while(e){No *p=e->prox;free(e);e=p;}}free(g->adj);free(g);
}
#endif
