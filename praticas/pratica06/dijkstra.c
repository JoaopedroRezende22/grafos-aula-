#include "dijkstra.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
static void troca(MinHeap*h,int a,int b){
 NoHeap t=h->dados[a];h->dados[a]=h->dados[b];h->dados[b]=t;
 h->posicao[h->dados[a].vertice]=a;h->posicao[h->dados[b].vertice]=b;
}
MinHeap *criar_min_heap(int n){
 if(n<=0)return NULL;MinHeap*h=malloc(sizeof(*h));if(!h)return NULL;
 h->dados=malloc((size_t)n*sizeof(NoHeap));h->posicao=malloc((size_t)n*sizeof(int));
 if(!h->dados||!h->posicao){free(h->dados);free(h->posicao);free(h);return NULL;}
 h->capacidade=n;h->tamanho=n;
 for(int i=0;i<n;i++){h->dados[i]=(NoHeap){i,INT_MAX};h->posicao[i]=i;}
 return h;
}
void liberar_min_heap(MinHeap*h){if(h){free(h->dados);free(h->posicao);free(h);}}
NoHeap extrair_minimo(MinHeap*h){
 NoHeap erro={-1,INT_MAX};if(!h||h->tamanho==0)return erro;
 NoHeap r=h->dados[0];h->posicao[r.vertice]=-1;
 --h->tamanho;if(h->tamanho){
 h->dados[0]=h->dados[h->tamanho];h->posicao[h->dados[0].vertice]=0;
 int i=0;while(1){int a=2*i+1,b=a+1,k=i;
 if(a<h->tamanho&&h->dados[a].distancia<h->dados[k].distancia)k=a;
 if(b<h->tamanho&&h->dados[b].distancia<h->dados[k].distancia)k=b;
 if(k==i)break;troca(h,i,k);i=k;}
 }return r;
}
void diminuir_chave(MinHeap*h,int v,int d){
 if(!h||v<0||v>=h->capacidade)return;int i=h->posicao[v];
 if(i<0||i>=h->tamanho||d>=h->dados[i].distancia)return;
 h->dados[i].distancia=d;while(i>0&&h->dados[(i-1)/2].distancia>d){
 int p=(i-1)/2;troca(h,p,i);i=p;}
}
void dijkstra(GrafoListaPonderado*g,int origem,int *dist,int *pred){
 if(!g||!dist||!pred||origem<0||origem>=g->n)return;
 for(int i=0;i<g->n;i++){dist[i]=INT_MAX;pred[i]=-1;}
 MinHeap*h=criar_min_heap(g->n);if(!h)return;
 dist[origem]=0;diminuir_chave(h,origem,0);
 while(h->tamanho){
 NoHeap u=extrair_minimo(h);if(u.distancia==INT_MAX)break;
 for(No*e=g->adj[u.vertice];e;e=e->prox){
 if(e->peso<0){fprintf(stderr,"Peso negativo ignorado.\n");continue;}
 int v=e->destino;
 if(h->posicao[v]>=0&&dist[u.vertice]<=INT_MAX-e->peso&&
 dist[u.vertice]+e->peso<dist[v]){
 dist[v]=dist[u.vertice]+e->peso;pred[v]=u.vertice;diminuir_chave(h,v,dist[v]);}
 }
 }liberar_min_heap(h);
}
void reconstruir_caminho(int origem,int destino,int *pred){
 if(!pred||origem<0||destino<0)return;
 int caminho[1024],t=0,v=destino;
 while(v!=origem&&v!=-1&&t<1024){caminho[t++]=v;v=pred[v];}
 if(v!=origem){puts("Caminho nao encontrado.");return;}
 printf("%d",origem);for(int i=t-1;i>=0;i--)printf(" -> %d",caminho[i]);putchar('\n');
}
