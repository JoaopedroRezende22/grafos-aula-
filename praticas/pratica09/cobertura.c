#pragma GCC diagnostic ignored "-Wmisleading-indentation"
#include "cobertura.h"
#include <stdlib.h>
#include <string.h>
Grafo *criar_grafo(int n){
 if(n<=0)return NULL;Grafo*g=malloc(sizeof(*g));if(!g)return NULL;
 g->n=n;g->adj=calloc((size_t)n*(size_t)n,1);
 if(!g->adj){free(g);return NULL;}return g;
}
void adicionar_aresta(Grafo*g,int u,int v){
 if(g&&u>=0&&u<g->n&&v>=0&&v<g->n&&u!=v){
 g->adj[(size_t)u*g->n+v]=1;g->adj[(size_t)v*g->n+u]=1;
 }
}
void liberar_grafo(Grafo*g){if(g){free(g->adj);free(g);}}
int eh_cobertura(const Grafo*g,const int*set){
 if(!g||!set)return 0;
 for(int u=0;u<g->n;u++)for(int v=u+1;v<g->n;v++)
 if(g->adj[(size_t)u*g->n+v]&&!set[u]&&!set[v])return 0;
 return 1;
}
typedef struct {const Grafo*g;int *atual,*melhor,quant,limite;} Busca;
static void buscar(Busca*b){
 if(b->quant>=b->limite)return;
 int u=-1,v=-1;
 for(int i=0;i<b->g->n&&u==-1;i++)for(int j=i+1;j<b->g->n;j++)
 if(b->g->adj[(size_t)i*b->g->n+j]&&!b->atual[i]&&!b->atual[j]){u=i;v=j;break;}
 if(u==-1){
 b->limite=b->quant;
 memcpy(b->melhor,b->atual,(size_t)b->g->n*sizeof(int));return;
 }
 b->atual[u]=1;b->quant++;buscar(b);b->quant--;b->atual[u]=0;
 b->atual[v]=1;b->quant++;buscar(b);b->quant--;b->atual[v]=0;
}
int cobertura_minima_bt(const Grafo*g,int*resultado){
 if(!g||!resultado)return -1;
 int*atual=calloc((size_t)g->n,sizeof(int));if(!atual)return -1;
 for(int i=0;i<g->n;i++)resultado[i]=1;
 Busca b={g,atual,resultado,0,g->n+1};
 buscar(&b);free(atual);return b.limite;
}
int cobertura_gulosa(const Grafo*g,int*resultado){
 if(!g||!resultado)return -1;
 memset(resultado,0,(size_t)g->n*sizeof(int));int quant=0;
 while(!eh_cobertura(g,resultado)){
 int melhor=-1,maior=0;
 for(int u=0;u<g->n;u++)if(!resultado[u]){
 int grau=0;for(int v=0;v<g->n;v++)
 if(u!=v&&g->adj[(size_t)u*g->n+v]&&!resultado[v])grau++;
 if(grau>maior){maior=grau;melhor=u;}
 }
 if(melhor<0)break;resultado[melhor]=1;quant++;
 }
 return quant;
}
