#ifndef AGM_H
#define AGM_H
typedef struct {int *pai,*rank,n;} DSU;
typedef struct {int u,v,peso;} Aresta;
DSU *criar_dsu(int n);
int find(DSU*d,int x);
int unir(DSU*d,int x,int y);
void liberar_dsu(DSU*d);
int kruskal(int n,const Aresta*arestas,int m,Aresta*saida);
int prim(int n,const Aresta*arestas,int m,Aresta*saida);
#endif
