#include "agm.h"
#include <stdio.h>
static void mostrar(const char*nome,Aresta*a,int k){
 int total=0;printf("%s: %d arestas\n",nome,k);
 for(int i=0;i<k;i++){printf("%d -- %d (peso %d)\n",a[i].u,a[i].v,a[i].peso);total+=a[i].peso;}
 printf("Custo total: %d\n",total);
}
int main(void){
 Aresta edges[]={{0,1,4},{0,2,4},{1,2,2},{1,3,5},{2,3,5},{2,4,11},{3,4,2}};
 Aresta r1[4],r2[4];
 int m=(int)(sizeof(edges)/sizeof(edges[0]));
 int a=kruskal(5,edges,m,r1),b=prim(5,edges,m,r2);
 if(a!=4||b!=4){puts("Grafo desconectado ou falha.");return 1;}
 mostrar("Kruskal",r1,a);mostrar("Prim",r2,b);return 0;
}
