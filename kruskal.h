#ifndef KRUSKAL_H
#define KRUSKAL_H

struct Aresta
{
	int origem, destino, peso;
};

struct Grafo
{
	int V, A;

	struct Aresta* aresta;
};

struct Grafo* criaGrafo(int V, int A)
{
	struct Grafo* grafo = (struct Grafo*) malloc( sizeof(struct Grafo) );
	grafo->V = V;
	grafo->A = A;

	grafo->aresta = (struct Aresta*) malloc( grafo->A * sizeof( struct Aresta ) );

	return grafo;
}

struct subconjunto
{
	int pai;
	int class;
};

int find(struct subconjunto subconjuntos[], int i);
void Union(struct subconjunto subconjuntos[], int x, int y);
int compara(const void* k, const void* w);
void Kruskal(struct Grafo* grafo);

#endif
