#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "grafo.h"

struct grafo{
    int nro_vert;
    int Amax;
    int eh_ponderado;
    int **arestas;
    int **pesos;
    int *grau;
};

Grafo* criaGrafo(int nro_vert, int Amax, int eh_ponderado){
    Grafo* gr;
    gr = (Grafo*) malloc (sizeof(Grafo));

    if(gr){
        gr->nro_vert = nro_vert;
        gr->Amax = Amax;
        gr->eh_ponderado = eh_ponderado;

        gr->grau = (int*) malloc (nro_vert*sizeof(int));
        for(int I=0; I<nro_vert; I++)
            gr->grau[I] = 0;

        gr->arestas = (int**) malloc (nro_vert*sizeof(int*));
        for(int I=0; I<gr->nro_vert; I++){
            gr->arestas[I] = (int*) malloc (Amax*sizeof(int));
        }

        if(gr->eh_ponderado){
            gr->pesos = (int**) malloc (nro_vert*sizeof(int*));
            for(int I=0; I<gr->nro_vert; I++){
                gr->pesos[I] = (int*) malloc (Amax*sizeof(int));
            }
        }

        return gr;
    }
    exit(1);
}

void destruirGrafo(Grafo* gr){
    if(gr){
        int I;
        for(I=0; I<gr->nro_vert; I++){
            free(gr->arestas[I]);
        }
        free(gr->arestas);

        if(gr->eh_ponderado){
            for(I=0; I<gr->nro_vert; I++){
                free(gr->pesos[I]);
            }
            free(gr->pesos);
        }

        free(gr->grau);
        free(gr);
    }
}

int inserirAresta(Grafo* gr, int orig, int dest, int digrafo, float peso){
    if(!gr){
        printf("\nErro de alocacao do grafo\n\n");
        return 0;
    }

    if(orig<0 || orig>=gr->nro_vert || dest<0 || dest>=gr->nro_vert){
        printf("\nIndices de origem ou destino invalidos!\n\n");
        return 0;
    }

    gr->arestas[orig][gr->grau[orig]] = dest;
    if(gr->eh_ponderado){
        gr->pesos[orig][gr->grau[orig]] = peso;
    }
    gr->grau[orig]++;

    if(!digrafo)
        inserirAresta(gr, dest, orig, 1, peso);

    return 1;
}

int removerAresta(Grafo* gr, int orig, int dest, int digrafo){
    if(!gr){
        printf("\nErro de alocacao do grafo\n\n");
        return 0;
    }

    if(orig<0 || orig>=gr->nro_vert || dest<0 || dest>=gr->nro_vert){
        printf("\nIndices de origem ou destino invalidos!\n\n");
        return 0;
    }

    int I;
    for(I=0; I<gr->grau[orig]; I++){
        if(gr->arestas[orig][I] == dest)
            break;
    }

    if(I==gr->grau[orig]){
        printf("\nA aresta entre os indices indicados nao existe\n\n");
        return 0;
    }

    gr->grau[orig]--;
    gr->arestas[orig][I] = gr->arestas[orig][gr->grau[orig]];

    if(gr->eh_ponderado)
        gr->pesos[orig][I] = gr->pesos[orig][gr->grau[orig]];

    if(!digrafo)
        removerAresta(gr, dest, orig, 1);

    return 1;
}

void iniciaBuscaProfundidade(Grafo* gr, int ini){
    int* visitados = (int*) malloc (gr->nro_vert * sizeof(int));
    int I, cont=1;

    for(I=0; I<gr->nro_vert; I++)
        visitados[I] = 0;

    buscaProfundidade(gr, ini, visitados, cont);

    printf("\n");
    for(I=0; I<gr->nro_vert; I++){
        printf("%d ", visitados[I]);
    }
    printf("\n");

    free(visitados);
}

void buscaProfundidade(Grafo* gr, int ini, int* visitados, int cont){
    int I;
    visitados[ini] = cont;

    for(I=0; I<gr->grau[ini]; I++){
        if(!visitados[gr->arestas[ini][I]]){
            buscaProfundidade(gr, gr->arestas[ini][I], visitados, cont+1);
        }
    }
}

void buscaLargura(Grafo* gr, int ini){
    int* visitados = (int*) malloc (gr->nro_vert * sizeof(int));
    int vert, cont=1, IF=0, FF=0, I;
    int* fila = (int*) malloc (gr->nro_vert * sizeof(int));

    for(I=0; I<gr->nro_vert; I++)
        visitados[I] = 0;

    FF++;
    fila[FF] = ini;
    visitados[ini] = cont;

    while(IF!=FF){
        IF = (IF+1) % gr->nro_vert;
        vert = fila[IF];
        cont++;

        for(I=0; I<gr->grau[vert]; I++){
            if(!visitados[gr->arestas[vert][I]]){
                FF = (FF+1) % gr->nro_vert;
                fila[FF] = gr->arestas[vert][I];
                visitados[gr->arestas[vert][I]] = cont;
            }
        }
    }

    printf("\n");
    for(int I=0; I<gr->nro_vert; I++){
        printf("%d ", visitados[I]);
    }
    printf("\n");

    free(fila);
    free(visitados);
}

void printarGrafo(Grafo* gr){
    int I, II;
    printf("\nImpressao dos vertices e seus vizinhos:\n");
    for(I=0; I<gr->nro_vert; I++){
        printf("Vertice %d: ", I+1);
        for(II=0; II<gr->grau[I]; II++){
            printf("%d ", gr->arestas[I][II]+1);
        }
        printf("\n");
    }
    printf("\n");
}