#include "bellman_ford.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
int bellman_ford(GrafoListaPonderado *g,int origem,int *dist,int *pred){
    if(!g||!dist||!pred||origem<0||origem>=g->n)return 0;
    for(int i=0;i<g->n;i++){dist[i]=INT_MAX;pred[i]=-1;}
    dist[origem]=0;
    for(int i=1;i<g->n;i++){
        int mudou=0;
        for(int u=0;u<g->n;u++)for(No *e=g->adj[u];e;e=e->prox){
            if(dist[u]!=INT_MAX){
                long long alt=(long long)dist[u]+e->peso;
                if(alt>=INT_MIN&&alt<=INT_MAX&&alt<dist[e->destino]){
                    dist[e->destino]=(int)alt;pred[e->destino]=u;mudou=1;
                }
            }
        }
        if(!mudou)break;
    }
    for(int u=0;u<g->n;u++)for(No *e=g->adj[u];e;e=e->prox){
        if(dist[u]!=INT_MAX&&(long long)dist[u]+e->peso<dist[e->destino]){
            pred[e->destino]=u;
            printf("Ciclo negativo detectado: ");
            reconstruir_ciclo_negativo(g->n,e->destino,pred);
            return 0;
        }
    }
    return 1;
}
void reconstruir_ciclo_negativo(int n,int vertice,int *pred){
    if(!pred||n<=0||vertice<0)return;
    int v=vertice;
    for(int i=0;i<n;i++){if(v<0){puts("indisponivel");return;}v=pred[v];}
    if(v<0){puts("indisponivel");return;}
    int *ciclo=malloc((size_t)(n+1)*sizeof(int));
    if(!ciclo)return;
    int qtd=0,atual=v;
    do{
        if(atual<0||qtd>=n){free(ciclo);puts("indisponivel");return;}
        ciclo[qtd++]=atual;atual=pred[atual];
    }while(atual!=v);
    printf("%d",v);
    for(int i=qtd-1;i>=0;i--)printf(" -> %d",ciclo[i]);
    putchar('\n');free(ciclo);
}
