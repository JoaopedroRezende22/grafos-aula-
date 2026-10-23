#include "dijkstra.h"
#include <limits.h>
#include <stdio.h>
int main(void){
 GrafoListaPonderado*g=criar_grafo(6);if(!g)return 1;
 int a[][3]={{0,1,7},{0,2,9},{0,5,14},{1,2,10},{1,3,15},{2,3,11},{2,5,2},{3,4,6},{5,4,9}};
 for(size_t i=0;i<sizeof(a)/sizeof(a[0]);i++)
 if(!adicionar_aresta(g,a[i][0],a[i][1],a[i][2])){liberar_grafo(g);return 1;}
 int dist[6],pred[6];dijkstra(g,0,dist,pred);
 for(int v=0;v<6;v++){if(dist[v]==INT_MAX)printf("0 -> %d: inacessivel\n",v);
 else {printf("0 -> %d: custo %d, rota ",v,dist[v]);reconstruir_caminho(0,v,pred);}}
 liberar_grafo(g);return 0;
}
