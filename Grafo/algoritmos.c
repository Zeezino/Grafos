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
    ant[ini] = ini;

    for(I=0; I<NV; I++){
        vert = -1;

        for(int II=0; II<NV; II++){
            if(!visitados[II] && (vert == -1 || dist[II]<dist[vert]))
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

        
    printf("\nDistancias ao vertice inicial:\n");
    for(I=0; I<NV; I++){
        printf("%d ", dist[I]);
    }
    printf("\nVertices anteriores de cada vertice no menor caminho:\n");
    for(I=0; I<NV; I++){
        printf("%d ", ant[I]);
    }
    printf("\nVertices nao visitados:\n");
    int flag=0;
    for(I=0; I<NV; I++){
        if(!visitados[I]){
            printf("%d ", I);
            flag++;
        }
    }
    if(!flag)
        printf("Todos os vertices foram visitados");
    printf("\n");

    free(visitados);
    free(ant);
    free(dist);
}

void dijkstraFila(Grafo* gr, int ini){
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
    ant[ini] = ini;

    int* fila = (int*) malloc (NV*sizeof(int));
    int IF=0, FF=0;
    
    fila[FF] = ini;
    FF++;

    while (IF < FF) {
        // Encontra o vértice na fila com a menor distância
        int minDist = INT_MAX;
        int minIndex = -1;
        for (int i = IF; i < FF; i++) {
            if (dist[fila[i]] < minDist) {
                minDist = dist[fila[i]];
                minIndex = i;
            }
        }

        // Remove o vértice com a menor distância da fila
        vert = fila[minIndex];
        for (int i = minIndex; i < FF - 1; i++) {
            fila[i] = fila[i + 1];
        }
        FF--;

        visitados[vert] = 1;

        // Atualiza as distâncias dos vértices adjacentes
        for (I = 0; I < gr->grau[vert]; I++) {
            ind = gr->arestas[vert][I];
            int peso = gr->eh_ponderado ? gr->pesos[vert][I] : 1;
            if (dist[ind] > dist[vert] + peso) {
                dist[ind] = dist[vert] + peso;
                ant[ind] = vert;
                if (!visitados[ind]) {
                    fila[FF++] = ind;
                }
            }
        }
    }
        
    printf("\nDistancias ao vertice inicial:\n");
    for(I=0; I<NV; I++){
        printf("%d ", dist[I]);
    }
    printf("\nVertices anteriores de cada vertice no menor caminho:\n");
    for(I=0; I<NV; I++){
        printf("%d ", ant[I]);
    }
    printf("\nVertices nao visitados:\n");
    int flag=0;
    for(I=0; I<NV; I++){
        if(!visitados[I]){
            printf("%d ", I);
            flag++;
        }
    }
    if(!flag)
        printf("Todos os vertices foram visitados");
    printf("\n");

    free(visitados);
    free(ant);
    free(dist);
    free(fila);
}

void bellmanFord(Grafo* gr, int ini){
    int NV, vert, ind, peso, I, II;
    NV = gr->nro_vert;

    int* dist = (int*) malloc (NV*sizeof(int));
    int* ant = (int*) malloc (NV*sizeof(int));

    for(I=0; I<NV; I++){
        dist[I] = INT_MAX;
        ant[I] = -1;
    }
    dist[ini] = 0;
    ant[ini] = ini;

    int flag=0;
    for(I=0; I<NV-1; I++){
        if(!flag){
            flag=0;
            for(vert=0; vert<NV; vert++){
                if(ant[vert] != -1){
                    for(II=0; II<gr->grau[vert]; II++){
                        ind = gr->arestas[vert][II];
                        peso = gr->eh_ponderado ? gr->pesos[vert][II] : 1;
                        if(dist[ind] > dist[vert] + peso){
                            dist[ind] = dist[vert] + peso;
                            ant[ind] = vert;
                            flag++;
                        }
                    }
                }
            }
        }
        else
            break;
    }

    printf("\nDistancias ao vertice inicial:\n");
    for(I=0; I<NV; I++){
        printf("%d ", dist[I]);
    }
    printf("\nVertices anteriores de cada vertice no menor caminho:\n");
    for(I=0; I<NV; I++){
        printf("%d ", ant[I]);
    }
    printf("\n");

    free(dist);
    free(ant);
}

void floyd(Grafo* gr){
    int NV, vert, ind, peso, I, II, III;
    NV = gr->nro_vert;

    int **dist = (int**) malloc (NV*sizeof(int*));
    for(I=0; I<NV; I++){
        dist[I] = (int*) malloc (NV*sizeof(int));
        dist[I][I] = 0;
        for(II=0; II<NV; II++){
            if(II!=I)
                dist[I][II] = INT_MAX;
        }
    }

    for(I=0; I<NV; I++){
        for(II=0; II<gr->grau[I]; II++){
            ind = gr->arestas[I][II];
            peso = gr->eh_ponderado ? gr->pesos[I][ind] : 1;
            dist[I][ind] = peso;
        }
    }

    for(III=0; III<NV; III++){
        for(I=0; I<NV; I++){
            for(II=0; II<NV; II++){
                if(dist[I][III] != INT_MAX && dist[III][II] != INT_MAX && dist[I][II] > dist[I][III] + dist[III][II])
                    dist[I][II] = dist[I][III] + dist[III][II];
            }
        }
    }

    for(I=0; I<NV; I++){
        for(II=0; II<NV; II++){
            if(dist[I][II] == INT_MAX)
                printf("i ");
            else
                printf("%d ", dist[I][II]);
        }
        printf("\n");
    }

    for(I=0; I<NV; I++){
        free(dist[I]);
    }
    free(dist);
}

void prim(Grafo* gr, int ini){

}

void kruskal(Grafo* gr, int ini){

}