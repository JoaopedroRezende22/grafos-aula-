#pragma GCC diagnostic ignored "-Wmisleading-indentation"
#include "tps.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>
int *grafo_para_tsp(const Grafo*g){
 if(!g)return NULL;
 int*p=malloc((size_t)g->n*(size_t)g->n*sizeof(int));if(!p)return NULL;
 for(int i=0;i<g->n;i++)for(int j=0;j<g->n;j++)
 p[(size_t)i*g->n+j]=(i==j)?0:(g->adj[(size_t)i*g->n+j]?1:2);
 return p;
}
typedef struct {const int*p;int n,*atual,*melhor,*usado,melhor_custo;} Estado;
static void permutar(Estado*s,int pos,int custo){
 if(custo>=s->melhor_custo)return;
 if(pos==s->n){
 int total=custo+s->p[(size_t)s->atual[pos-1]*s->n];
 if(total<s->melhor_custo){
 s->melhor_custo=total;memcpy(s->melhor,s->atual,(size_t)s->n*sizeof(int));
 }
 return;
 }
 for(int v=1;v<s->n;v++)if(!s->usado[v]){
 int anterior=s->atual[pos-1];
 s->atual[pos]=v;s->usado[v]=1;
 permutar(s,pos+1,custo+s->p[(size_t)anterior*s->n+v]);
 s->usado[v]=0;
 }
}
int tsp_forca_bruta(const int*p,int n,int*rota){
 if(!p||!rota||n<=0)return -1;
 if(n==1){rota[0]=0;return 0;}
 int *atual=malloc((size_t)n*sizeof(int)),*usado=calloc((size_t)n,sizeof(int));
 if(!atual||!usado){free(atual);free(usado);return -1;}
 atual[0]=0;usado[0]=1;
 Estado s={p,n,atual,rota,usado,INT_MAX};
 permutar(&s,1,0);free(atual);free(usado);
 return s.melhor_custo;
}
int tsp_vizinho_mais_proximo(const int*p,int n,int*rota){
 if(!p||!rota||n<=0)return -1;
 int*usado=calloc((size_t)n,sizeof(int));if(!usado)return -1;
 rota[0]=0;usado[0]=1;int custo=0;
 for(int i=1;i<n;i++){
 int u=rota[i-1],v=-1;
 for(int j=1;j<n;j++)if(!usado[j]&&(v<0||p[(size_t)u*n+j]<p[(size_t)u*n+v]))v=j;
 rota[i]=v;usado[v]=1;custo+=p[(size_t)u*n+v];
 }
 custo+=p[(size_t)rota[n-1]*n];free(usado);return custo;
}
int tsp_insercao(const int*p,int n,int*rota){
 if(!p||!rota||n<=0)return -1;
 int*usado=calloc((size_t)n,sizeof(int));if(!usado)return -1;
 rota[0]=0;usado[0]=1;int tam=1;
 while(tam<n){
 int candidato=-1,distancia=INT_MAX;
 for(int v=1;v<n;v++)if(!usado[v])
 for(int k=0;k<tam;k++){
 int d=p[(size_t)rota[k]*n+v];
 if(d<distancia){distancia=d;candidato=v;}
 }
 if(candidato<0){free(usado);return -1;}
 int pos=0,delta=INT_MAX;
 for(int k=0;k<tam;k++){
 int u=rota[k],w=rota[(k+1)%tam];
 int inc=p[(size_t)u*n+candidato]+p[(size_t)candidato*n+w]-p[(size_t)u*n+w];
 if(inc<delta){delta=inc;pos=k+1;}
 }
 for(int k=tam;k>pos;k--)rota[k]=rota[k-1];
 rota[pos]=candidato;usado[candidato]=1;tam++;
 }
 int custo=0;for(int i=0;i<n;i++)custo+=p[(size_t)rota[i]*n+rota[(i+1)%n]];
 free(usado);return custo;
}
