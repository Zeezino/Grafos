typedef struct grafo Grafo;

Grafo* criaGrafo(int nro_vert, int Amax, int eh_ponderado);
void destruirGrafo(Grafo* gr);

int inserirAresta(Grafo* gr, int orig, int dest, int digrafo, float peso);
int removerAresta(Grafo* gr, int orig, int dest, int digrafo);

void iniciaBuscaProfundidade(Grafo* gr, int ini);
void buscaProfundidade(Grafo* gr, int ini, int* visitados, int cont);
void buscaLargura(Grafo* gr, int ini);

void dijkstra(Grafo* gr, int ini);
void dijkstraFila(Grafo* gr, int ini);
void bellmanFord(Grafo* gr, int ini);
void floyd(Grafo* gr);

void prim(Grafo* gr, int ini);
void kruskal(Grafo* gr, int ini);

void printarGrafo(Grafo* gr);