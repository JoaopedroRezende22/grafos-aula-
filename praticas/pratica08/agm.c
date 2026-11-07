#pragma GCC diagnostic ignored "-Wmisleading-indentation"
#include "agm.h"
#include <limits.h>
#include <stdlib.h>
DSU *criar_dsu(int n){
 if(n<=0)return NULL;DSU*d=malloc(sizeof(*d));if(!d)return NULL;
 d->pai=malloc((size_t)n*sizeof(int));d->rank=calloc((size_t)n,sizeof(int));
 if(!d->pai||!d->rank){free(d->pai);free(d->rank);free(d);return NULL;}
 d->n=n;for(int i=0;i<n;i++)d->pai[i]=i;return d;
}
int find(DSU*d,int x){if(d->pai[x]!=x)d->pai[x]=find(d,d->pai[x]);return d->pai[x];}
int unir(DSU*d,int x,int y){
 x=find(d,x);y=find(d,y);if(x==y)return 0;
 if(d->rank[x]<d->rank[y]){int t=x;x=y;y=t;}
 d->pai[y]=x;if(d->rank[x]==d->rank[y])d->rank[x]++;return 1;
}
void liberar_dsu(DSU*d){if(d){free(d->pai);free(d->rank);free(d);}}
static int comparar(const void*a,const void*b){
 const Aresta*x=a,*y=b;return (x->peso>y->peso)-(x->peso<y->peso);
}
int kruskal(int n,const Aresta*arestas,int m,Aresta*saida){
 if(n<=0||m<0||(!arestas&&m)||!saida)return -1;
 Aresta*copia=malloc((size_t)(m?m:1)*sizeof(Aresta));DSU*d=criar_dsu(n);
 if(!copia||!d){free(copia);liberar_dsu(d);return -1;}
 for(int i=0;i<m;i++)copia[i]=arestas[i];
 qsort(copia,(size_t)m,sizeof(Aresta),comparar);
 int k=0;for(int i=0;i<m&&k<n-1;i++){
 int u=copia[i].u,v=copia[i].v;
 if(u>=0&&u<n&&v>=0&&v<n&&unir(d,u,v))saida[k++]=copia[i];
 }
 free(copia);liberar_dsu(d);return k;
}
typedef struct {int v,chave;} Item;
typedef struct {Item *a;int *pos,tam;} Heap;
static void trocar(Heap*h,int i,int j){
 Item t=h->a[i];h->a[i]=h->a[j];h->a[j]=t;
 h->pos[h->a[i].v]=i;h->pos[h->a[j].v]=j;
}
static void subir(Heap*h,int i){
 while(i&&h->a[(i-1)/2].chave>h->a[i].chave){int p=(i-1)/2;trocar(h,p,i);i=p;}
}
static int tirar(Heap*h){
 int v=h->a[0].v;h->pos[v]=-1;--h->tam;
 if(h->tam){h->a[0]=h->a[h->tam];h->pos[h->a[0].v]=0;
 int i=0;while(1){int a=2*i+1,b=a+1,k=i;
 if(a<h->tam&&h->a[a].chave<h->a[k].chave)k=a;
 if(b<h->tam&&h->a[b].chave<h->a[k].chave)k=b;
 if(i==k)break;trocar(h,i,k);i=k;}}
 return v;
}
int prim(int n,const Aresta*arestas,int m,Aresta*saida){
 if(n<=0||m<0||(!arestas&&m)||!saida)return -1;
 Heap h={malloc((size_t)n*sizeof(Item)),malloc((size_t)n*sizeof(int)),n};
 int *pai=malloc((size_t)n*sizeof(int));
 if(!h.a||!h.pos||!pai){free(h.a);free(h.pos);free(pai);return -1;}
 for(int i=0;i<n;i++){h.a[i]=(Item){i,i?INT_MAX:0};h.pos[i]=i;pai[i]=-1;}
 int k=0;
 while(h.tam){
 int peso=h.a[0].chave;
 int u=tirar(&h);if(pai[u]!=-1){
 saida[k++]=(Aresta){pai[u],u,peso};
 }
 for(int i=0;i<m;i++){
 int v=-1;
 if(arestas[i].u==u)v=arestas[i].v;
 else if(arestas[i].v==u)v=arestas[i].u;
 if(v>=0&&v<n&&h.pos[v]>=0&&arestas[i].peso<h.a[h.pos[v]].chave){
 int p=h.pos[v];h.a[p].chave=arestas[i].peso;pai[v]=u;subir(&h,p);
 }
 }
 }
 free(h.a);free(h.pos);free(pai);return k;
}
