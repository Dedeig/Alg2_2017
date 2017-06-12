#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "kruskal.h"

#define numPontos 788
#define numArestas 310078 //o numero de arestas é defindo por n(n-1)/2 para um grafo completo, onde n = numer de vertices (nesse caso numPontos)

//Função recebe quatro valores float (coordenadas X e Y de dois pontos) e calcula a distância Euclidiana entre os dois pontos.
float calculaDistanciaEuclidiana(float coordX, float coordX2, float coordY, float coordY2){
	float distancia;

	distancia = sqrt(((coordX - coordX2)*(coordX - coordX2)) + ((coordY - coordY2)*(coordY - coordY2)));

	return(distancia);
}

int main(int argc, char *argv[])
{
	float coordX[numPontos], coordY[numPontos]; //vetores de float para guardar os pontos lidos
	float distanciaPontos[numPontos][numPontos]; //matriz com 
	int i, j, k;

	//fileName = argv[1];
	FILE *p;
	p = fopen("data.txt", "r");

	while(!feof(p)){
		for(i = 0; i < numPontos; i++){
			fscanf(p, "%f  %f", &coordX[i], &coordY[i]);
		}
	}
	
    i=0;
    j=0;

    for(i = 0; i < numPontos; i++){
        for(j = 0; j < numPontos; j++){
            distanciaPontos[i][j] = calculaDistanciaEuclidiana(coordX[i], coordX[j], coordY[i], coordY[j]);
       }
    }

    //Inicializa o grafo
	int V = numPontos;
	int A = numArestas;
	struct Grafo* grafo = criaGrafo(V, A);

	i=0;
	j=0;
	k=0;

	//Insere as arestas no grafo
	//Não temos uma struct para o vértice (o que importa é a aresta)
	for(i = 0; i < numPontos; i++){
		for(j = 0; j < numPontos; j++){
			if((j<i) || (j==i)){
			  //printf("Aresta já existe, não será inserida\n");
				continue;
			}
			
			grafo->aresta[k].origem = i;
			grafo->aresta[k].destino = j;
			grafo->aresta[k].peso = distanciaPontos[i][j];
			//printf("%d origem: %d, destino: %d, peso: %.2f\n", k, grafo->aresta[k].origem, grafo->aresta[k].destino,grafo->aresta[k].peso);
			k++;
		}
	}

	//Executa Kruskal com Union-Find no grafo dado
    Kruskal(grafo);

    fclose(p);

	return 0;
}
