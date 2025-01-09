#include <stdio.h>
#include "grafo.h"

int main(){
    int eh_digrafo = 1;
    Grafo* gr = criaGrafo(5, 5, 0);

    inserirAresta(gr, 0, 1, eh_digrafo, 0);
    inserirAresta(gr, 1, 3, eh_digrafo, 0);
    inserirAresta(gr, 1, 2, eh_digrafo, 0);
    inserirAresta(gr, 2, 4, eh_digrafo, 0);
    inserirAresta(gr, 3, 0, eh_digrafo, 0);
    inserirAresta(gr, 3, 4, eh_digrafo, 0);
    inserirAresta(gr, 4, 1, eh_digrafo, 0);

    // algoritmo de busca
    floyd(gr);
    // algoritmo de spanning tree

    printarGrafo(gr);

    destruirGrafo(gr);
    return 0;
}