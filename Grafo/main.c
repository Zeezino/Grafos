#include <stdio.h>
#include "grafo.h"

int main(){
    int eh_digrafo = 0;
    Grafo* gr = criaGrafo(6, 4, 1);

    inserirAresta(gr, 0, 1, eh_digrafo, 7);
    inserirAresta(gr, 0, 2, eh_digrafo, 9);
    inserirAresta(gr, 0, 5, eh_digrafo, 14);
    inserirAresta(gr, 1, 2, eh_digrafo, 10);
    inserirAresta(gr, 1, 3, eh_digrafo, 15);
    inserirAresta(gr, 2, 3, eh_digrafo, 11);
    inserirAresta(gr, 2, 5, eh_digrafo, 2);
    inserirAresta(gr, 3, 4, eh_digrafo, 6);
    inserirAresta(gr, 4, 5, eh_digrafo, 9);

    // algoritmo de busca
    prim(gr, 0);
    // floyd(gr);
    // algoritmo de spanning tree
    // prim(gr, 0);

    printarGrafo(gr);

    destruirGrafo(gr);
    return 0;
}