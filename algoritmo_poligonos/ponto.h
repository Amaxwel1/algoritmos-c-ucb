#ifndef PONTO_H
#define PONTO_H

typedef struct {
    float x;
    float y;
} Ponto;

typedef struct {
    Ponto *vertices;
    int numVertices;
} Poligono;

Poligono criarPoligono();
void imprimirPoligono(Poligono poligono);
float calcularArea(Poligono poligono);
void liberarPoligono(Poligono poligono);

#endif