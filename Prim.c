void Prim(struct Grafo *grafo, int origem, int *pai) {
	int i, j, dest, primeiro, nvert = grafo->numArestas;
	double menor;
	for (i=0; i<nvert; i++) {
		pai[i] = -1;
	}
	pai[origem] = origem;
	while(1) {
            int x, y;
		primeiro = 1;
		for (i=0; i<nvert; i++) {
			if (pai[i] != -1) {
				for (j=0; j<grafo->grau[i]; j++) {
					if (pai[j->i]== -1 && primeiro > j->i){
                        primeiro = j->i;
                        x = i;
                        y = primeiro->i;

					}
				}
			}
		}
		if (primeiro == 1) {
			break;
		}
		pai[dest] = origem;
	}
}
