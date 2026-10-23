#ifndef GRAFO_H
#define GRAFO_H
#include <stdlib.h>
typedef struct No { int destino, peso; struct No *prox; } No;
typedef struct { int n; No **adj; } GrafoListaPonderado;
static inline GrafoListaPonderado *criar_grafo(int n) {
    if(n<=0) return NULL;
    GrafoListaPonderado *g=malloc(sizeof(*g));
    if(!g) return NULL;
    g->n=n; g->adj=calloc((size_t)n,sizeof(No*));
    if(!g->adj){free(g);return NULL;} return g;
}
static inline int adicionar_aresta(GrafoListaPonderado *g,int u,int v,int peso){
    if(!g||u<0||v<0||u>=g->n||v>=g->n) return 0;
    No *a=malloc(sizeof(*a)); if(!a) return 0;
    *a=(No){v,peso,g->adj[u]}; g->adj[u]=a;return 1;
}
static inline void liberar_grafo(GrafoListaPonderado *g){
    if(!g)return;
    for(int i=0;i<g->n;i++){No *p=g->adj[i];while(p){No *next=p->prox;free(p);p=next;}}
    free(g->adj);free(g);
}
#endif
