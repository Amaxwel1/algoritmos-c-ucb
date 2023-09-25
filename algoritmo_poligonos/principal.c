#include "ponto.h"
#include <stdio.h>

int main() {
    Poligono poligono = criarPoligono();

    imprimirPoligono(poligono);

    float area = calcularArea(poligono);

    printf("Area do poligono: %.2lf\n", area);

    liberarPoligono(poligono);

    return 0;
}
