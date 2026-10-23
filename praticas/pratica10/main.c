#include "hamiltoniano.h"
#include "tps.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
static double tempo(clock_t a,clock_t b){return (double)(b-a)/CLOCKS_PER_SEC;}
int main(void){
 const int tamanhos[]={5,8,10,12};
 puts("n | TSP exato / tempo(s) | Vizinho / tempo(s) | Insercao / tempo(s)");
 for(size_t t=0;t<sizeof(tamanhos)/sizeof(tamanhos[0]);t++){
 int n=tamanhos[t];Grafo*g=criar_grafo(n);
 if(!g)return 1;
 /* Ciclo simples garante um ciclo Hamiltoniano; inclui cordas deterministicas. */
 for(int i=0;i<n;i++)adicionar_aresta(g,i,(i+1)%n);
 for(int i=0;i<n;i++)for(int j=i+2;j<n;j++)
 if((i*5+j*3+n)%5==0)adicionar_aresta(g,i,j);
 int*caminho=malloc((size_t)n*sizeof(int));
 int*rota=malloc((size_t)n*sizeof(int)),*p=grafo_para_tsp(g);
 if(!caminho||!rota||!p){free(caminho);free(rota);free(p);liberar_grafo(g);return 1;}
 int existe=encontrar_caminho_hamiltoniano_bt(g,caminho,0);
 int ciclo=encontrar_caminho_hamiltoniano_bt(g,caminho,1);
 printf("Hamiltoniano n=%d: caminho=%s, ciclo=%s\n",n,existe?"sim":"nao",ciclo?"sim":"nao");
 clock_t a=clock();int exato=tsp_forca_bruta(p,n,rota);clock_t b=clock();
 int viz=tsp_vizinho_mais_proximo(p,n,rota);clock_t c=clock();
 int ins=tsp_insercao(p,n,rota);clock_t d=clock();
 printf("%2d | %d / %.6f | %d / %.6f | %d / %.6f\n",
 n,exato,tempo(a,b),viz,tempo(b,c),ins,tempo(c,d));
 free(caminho);free(rota);free(p);liberar_grafo(g);
 }
 return 0;
}
