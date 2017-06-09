#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "kruskal.h"

#define numPontos 788
#define numArestas 310078

float calculaDistanciaEuclidiana(float coordX, float coordX2, float coordY, float coordY2){
	float distancia;

	distancia = sqrt((pow((coordX - coordX2),2)) - (pow((coordY - coordY2), 2)));

	return(distancia);
}

int main(int argc, char *argv[])
{
	char *fileName;
	float coordX[numPontos], coordY[numPontos];
	float distanciaPontos[numPontos][numPontos];
	int countI, countJ;

	//fileName = argv[1];
	FILE *p;
	p = fopen("data.txt", "r");
    printf("oi");

	while(!feof(p)){
		for(countI = 0; countI < numPontos; countI++){
			fscanf(p, "%f  %f", &coordX[countI], &coordY[countI]);
            printf("%.2f %.2f\n", coordX[countI], coordY[countI]);
		}
	}
	/*
    printf("oi");
    fclose(p);

    countI = 0;
    countJ = 0;

    for(countI = 0; countI < 1; countI++){
        for(countJ = 0; countJ < 1; countJ++){
            printf("oi\n");
            distanciaPontos[countI][countJ] = calculaDistanciaEuclidiana(coordX[countI],coordX[countJ], coordY[countI], coordY[countJ]);
        }
    }

    printf("%.2f\n", distanciaPontos[0][1]);

/*
	int V = numPontos;
	int A = numArestas;
	struct Grafo* grafo = criaGrafo(V, A);

	grafo->aresta[0].origem = 0;
	grafo->aresta[0].destino = 1;
	grafo->aresta[0].peso = 10;

	grafo->aresta[1].origem = 0;
	grafo->aresta[1].destino = 2;
	grafo->aresta[1].peso = 6;

	grafo->aresta[2].origem = 0;
	grafo->aresta[2].destino = 3;
	grafo->aresta[2].peso = 5;

	grafo->aresta[3].origem = 1;
	grafo->aresta[3].destino = 3;
	grafo->aresta[3].peso = 15;

	grafo->aresta[4].origem = 2;
	grafo->aresta[4].destino = 3;
	grafo->aresta[4].peso = 4;

	grafo->aresta[5].origem = 3;
	grafo->aresta[5].destino = 4;
	grafo->aresta[5].peso = 7;

    Kruskal(grafo);
*/

	return 0;
}
