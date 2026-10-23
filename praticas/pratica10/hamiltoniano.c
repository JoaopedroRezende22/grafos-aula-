#pragma GCC diagnostic ignored "-Wmisleading-indentation"
#include "hamiltoniano.h"
#include <stdlib.h>
Grafo *criar_grafo(int n){
 if(n<=0)return NULL;Grafo*g=malloc(sizeof(*g));if(!g)return NULL;
 g->adj=calloc((size_t)n*(size_t)n,1);
 if(!g->adj){free(g);return NULL;}g->n=n;return g;
}
void adicionar_aresta(Grafo*g,int u,int v){
 if(g&&u>=0&&u<g->n&&v>=0&&v<g->n&&u!=v){
 g->adj[(size_t)u*g->n+v]=1;g->adj[(size_t)v*g->n+u]=1;
 }
}
void liberar_grafo(Grafo*g){if(g){free(g->adj);free(g);}}
static int busca(const Grafo*g,int*c,int *usado,int tam,int ciclo){
 if(tam==g->n)return !ciclo||g->adj[(size_t)c[tam-1]*g->n+c[0]];
 for(int v=0;v<g->n;v++)if(!usado[v]&&
 (tam==0||g->adj[(size_t)c[tam-1]*g->n+v])){
 c[tam]=v;usado[v]=1;
 if(busca(g,c,usado,tam+1,ciclo))return 1;
 usado[v]=0;
 }
 return 0;
}
int encontrar_caminho_hamiltoniano_bt(const Grafo*g,int*caminho,int ciclo){
 if(!g||!caminho)return 0;
 int*usado=calloc((size_t)g->n,sizeof(int));if(!usado)return 0;
 int existe=busca(g,caminho,usado,0,ciclo);
 free(usado);return existe;
}
