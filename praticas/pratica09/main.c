#pragma GCC diagnostic ignored "-Wmisleading-indentation"
#include "cobertura.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
static double segundos(clock_t a,clock_t b){return (double)(b-a)/CLOCKS_PER_SEC;}
int main(void){
 const int tamanhos[]={5,8,10,12,15};
 puts("n | exata | tempo exata(s) | gulosa | tempo gulosa(s) | validas");
 for(size_t k=0;k<sizeof(tamanhos)/sizeof(tamanhos[0]);k++){
 int n=tamanhos[k];Grafo*g=criar_grafo(n);
 int *exata=calloc((size_t)n,sizeof(int)),*gulosa=calloc((size_t)n,sizeof(int));
 if(!g||!exata||!gulosa){liberar_grafo(g);free(exata);free(gulosa);return 1;}
 /* Grafo deterministico, incluindo um caminho que conecta todos os vertices. */
 for(int u=0;u<n;u++)for(int v=u+1;v<n;v++)
 if(v==u+1||((u*17+v*11+n)%7==0))adicionar_aresta(g,u,v);
 clock_t a=clock();int opt=cobertura_minima_bt(g,exata);clock_t b=clock();
 int heu=cobertura_gulosa(g,gulosa);clock_t c=clock();
 printf("%2d | %5d | %.8f | %6d | %.8f | %s\n",
 n,opt,segundos(a,b),heu,segundos(b,c),
 eh_cobertura(g,exata)&&eh_cobertura(g,gulosa)?"sim":"nao");
 liberar_grafo(g);free(exata);free(gulosa);
 }
 return 0;
}
