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

void dijkstra(Grafo* gr, int ini){
    int I, NV, ind, vert;
    NV = gr->nro_vert;

    int* visitados = (int*) malloc (NV * sizeof(int));
    int* ant = (int*) malloc (NV * sizeof(int));
    int* dist = (int*) malloc (NV * sizeof(int));

    for(I=0; I<NV; I++){
        visitados[I] = 0;
        ant[I] = -1;
        dist[I] = INT_MAX;
    }
    dist[ini] = 0;

    for(I=0; I<NV; I++){
        vert = -1;
        for(int II=0; II<NV; II++){
            if(!visitados[II] && (vert == -1 || dist[II] < dist[vert]))
                vert = II;
        }

        if(vert == -1 || dist[vert] == INT_MAX)
            break;

        visitados[vert] = 1;

        for(int II=0; II<gr->grau[vert]; II++){
            ind = gr->arestas[vert][II];
            if(dist[ind] > dist[vert] + (gr->eh_ponderado ? gr->pesos[vert][II] : 1)){
                dist[ind] = dist[vert] + (gr->eh_ponderado ? gr->pesos[vert][II] : 1);
                ant[ind] = vert;
            }
        }
    }
        
    printf("\n");
    for(I=0; I<NV; I++){
        printf("%d ", dist[I]);
    }
    printf("\n");

    free(visitados);
    free(ant);
    free(dist);
}

void bellmanFord(Grafo* gr, int ini){
    int I, II, NV, ind, vert;
    NV = gr->nro_vert;

    int* ant = (int*) malloc (NV * sizeof(int));
    int* dist = (int*) malloc (NV * sizeof(int));

    for(I=0; I<NV; I++){
        ant[I] = -1;
        dist[I] = INT_MAX;
    }
    dist[ini] = 0;

    for(I=0; I<NV-1; I++){
        for(vert=0; vert<NV; vert++){
            for(II=0; II<gr->grau[vert]; II++){
                ind = gr->arestas[vert][II];
                if(dist[ind] > dist[vert] + (gr->eh_ponderado ? gr->pesos[vert][II] : 1)){
                    dist[ind] = dist[vert] + (gr->eh_ponderado ? gr->pesos[vert][II] : 1);
                    ant[ind] = vert;
                }
            }
        }
    }

    for(vert=0; vert<NV; vert++){
        for(II=0; II<gr->grau[vert]; II++){
            ind = gr->arestas[vert][II];
            if(dist[ind] > dist[vert] + (gr->eh_ponderado ? gr->pesos[vert][II] : 1)){
                printf("\nGrafo possui ciclo negativo\n\n");
                return;
            }
        }
    }

    printf("\n");
    for(I=0; I<NV; I++){
        printf("%d ", dist[I]);
    }
    printf("\n");

    free(ant);
    free(dist);
}

void floyd(Grafo* gr){
    int I, II, III, NV;
    NV = gr->nro_vert;

    int** dist = (int**) malloc (NV * sizeof(int*));
    for(I=0; I<NV; I++){
        dist[I] = (int*) malloc (NV * sizeof(int));
        for(II=0; II<NV; II++){
            dist[I][II] = INT_MAX;
        }
    }

    for(I=0; I<NV; I++){
        dist[I][I] = 0;
        for(II=0; II<gr->grau[I]; II++){
            dist[I][gr->arestas[I][II]] = gr->eh_ponderado ? gr->pesos[I][II] : 1;
        }
    }

    for(III=0; III<NV; III++){
        for(I=0; I<NV; I++){
            for(II=0; II<NV; II++){
                if(dist[I][II] > dist[I][III] + dist[III][II]){
                    dist[I][II] = dist[I][III] + dist[III][II];
                }
            }
        }
    }

    for(I=0; I<NV; I++){
        for(II=0; II<NV; II++){
            printf("%d ", dist[I][II]);
        }
        printf("\n");
    }

    for(I=0; I<NV; I++){
        free(dist[I]);
    }
    free(dist);
}

void printarGrafo(Grafo* gr){
    int I, II;
    printf("\n");
    for(I=0; I<gr->nro_vert; I++){
        printf("Vertice %d: ", I+1);
        for(II=0; II<gr->grau[I]; II++){
            printf("%d ", gr->arestas[I][II]+1);
        }
        printf("\n");
    }
    printf("\n");
}