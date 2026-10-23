#include "bellman_ford.h"
#include <limits.h>
#include <stdio.h>
int main(void){
    GrafoListaPonderado *g=criar_grafo(5);
    if(!g)return 1;
    const int a[][3]={{0,1,6},{0,2,7},{1,3,5},{1,2,8},{1,4,-4},
                      {2,3,-3},{3,1,-2},{4,0,2},{4,3,7}};
    for(size_t i=0;i<sizeof(a)/sizeof(a[0]);i++)
        if(!adicionar_aresta(g,a[i][0],a[i][1],a[i][2])){liberar_grafo(g);return 1;}
    int dist[5],pred[5];
    if(bellman_ford(g,0,dist,pred))
        for(int i=0;i<5;i++)
            if(dist[i]==INT_MAX)printf("%d: inacessivel\n",i);
            else printf("0 -> %d: %d, predecessor %d\n",i,dist[i],pred[i]);
    else puts("Nao ha caminhos minimos definidos devido ao ciclo negativo.");
    liberar_grafo(g);return 0;
}
