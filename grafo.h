#include <stdlib.h>

#ifndef GRAFO_H
#define GRAFO_H

struct Aresta
{
  int origem, destino;
  float peso;
};

struct Grafo
{
  int V, A;
  int *grau;

  struct Aresta* aresta;
};

struct subconjunto
{
  int pai;
  int class;
};

struct Grafo* criaGrafo(int V, int A);
int find(struct subconjunto subconjuntos[], int i);
void Union(struct subconjunto subconjuntos[], int x, int y, int maxSubSets);
int compara(const void* k, const void* w);
void Kruskal(struct Grafo* grafo, int maxSubSets);
void Prim(struct Grafo *grafo, int origem, int *pai);

#endif
