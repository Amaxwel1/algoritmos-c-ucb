#include "ponto.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Poligono criarPoligono() {
    FILE *arquivo = fopen("vertices.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    Poligono poligono;
    fscanf(arquivo, "%d", &poligono.numVertices);

    if (poligono.numVertices < 3) {
        printf("O poligono deve ter pelo menos 3 vertices.\n");
        fclose(arquivo);
        exit(1);
    }

    poligono.vertices = (Ponto *)malloc(sizeof(Ponto) * poligono.numVertices);

    for (int i = 0; i < poligono.numVertices; i++) {
        fscanf(arquivo, "%f %f", &poligono.vertices[i].x, &poligono.vertices[i].y);
    }

    fclose(arquivo);
    return poligono;
}

void imprimirPoligono(Poligono poligono) {
    printf("\n");
    printf("Numero de vertices: %d\n", poligono.numVertices);
    printf("Coordenadas dos vertices:\n");

    for (int i = 0; i < poligono.numVertices; i++) {
        printf("Vertice %d: (%.2lf, %.2lf)\n", i + 1, poligono.vertices[i].x, poligono.vertices[i].y);
    }
    printf("\n");
}

float calcularArea(Poligono poligono) {
    float area = 0.0;

    for (int i = 1; i < poligono.numVertices - 1; i++) {
        float x1 = poligono.vertices[0].x;
        float y1 = poligono.vertices[0].y;
        float x2 = poligono.vertices[i].x;
        float y2 = poligono.vertices[i].y;
        float x3 = poligono.vertices[i + 1].x;
        float y3 = poligono.vertices[i + 1].y;

        area += 0.5 * fabs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1));
    }

    return area;
}

void liberarPoligono(Poligono poligono) {
    free(poligono.vertices);
}
