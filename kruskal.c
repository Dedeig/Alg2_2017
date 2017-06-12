#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kruskal.h"


int find(struct subconjunto subconjuntos[], int i)
{
	if (subconjuntos[i].pai != i)
		subconjuntos[i].pai = find(subconjuntos, subconjuntos[i].pai);

	return subconjuntos[i].pai;
}

void Union(struct subconjunto subconjuntos[], int x, int y)
{
	int raiz_x = find(subconjuntos, x);
	int raiz_y = find(subconjuntos, y);

	if (subconjuntos[raiz_x].class < subconjuntos[raiz_y].class)
		subconjuntos[raiz_x].pai = raiz_y;
	else if (subconjuntos[raiz_x].class > subconjuntos[raiz_y].class)
		subconjuntos[raiz_y].pai = raiz_x;

	else
	{
		subconjuntos[raiz_y].pai = raiz_x;
		subconjuntos[raiz_x].class++;
	}
}

int compara(const void* k, const void* w)
{
	struct Aresta* k1 = (struct Aresta*)k;
	struct Aresta* w1 = (struct Aresta*)w;
	return k1->peso > w1->peso;
}


void Kruskal(struct Grafo* grafo)
{
	int V = grafo->V;
	struct Aresta vetor[V];
	int a = 0;
	int i = 0;

	qsort(grafo->aresta, grafo->A, sizeof(grafo->aresta[0]), compara);

	struct subconjunto *subconjuntos =
		(struct subconjunto*) malloc( V * sizeof(struct subconjunto) );

	for (int v = 0; v < V; v++)
	{
		subconjuntos[v].pai = v;
		subconjuntos[v].class = 1;
	}

	while (a < V - 1)
	{

		struct Aresta prox_aresta = grafo->aresta[i++];

		int x = find(subconjuntos, prox_aresta.origem);
		int y = find(subconjuntos, prox_aresta.destino);

		if (x != y)
		{
			vetor[a++] = prox_aresta;
			Union(subconjuntos, x, y);
		}
	}

	//	printf("Following are the arestas in the constructed Kruskal\n");
	//	for (i = 0; i < a; ++i)
	  // printf("%d -- %d == %.2f, class: %d\n", vetor[i].origem, vetor[i].destino, vetor[i].peso, subconjuntos[i].class);

	FILE *p = fopen("kruskalResults.txt", "w");

	for (i = 0; i < a; i++)
	  fprintf(p, "%d\n", subconjuntos[i].class);	  
	  
	return;
}

struct Grafo* criaGrafo(int V, int A)
{
	struct Grafo* grafo = (struct Grafo*) malloc( sizeof(struct Grafo) );
	grafo->V = V;
	grafo->A = A;

	grafo->aresta = (struct Aresta*) malloc( grafo->A * sizeof( struct Aresta ) );

	return grafo;
}
