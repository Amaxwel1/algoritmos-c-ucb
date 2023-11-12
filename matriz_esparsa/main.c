#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lista.h"
#include "matriz.h"

int main(int argc, char *argv[])
{
	setbuf(stdout, NULL);

	MATRIZ_ESPARSA *a = leMatriz("matriz_A.txt");
	MATRIZ_ESPARSA *b = leMatriz("matriz_B.txt");

	MATRIZ_ESPARSA *result = NULL;

	printf("-- MATRIZES ESPARSAS --\n");
	printf("\nMatriz A");
	imprimeMatriz(a);

	printf("\nMatriz B");
	imprimeMatriz(b);

	printf("\n");

	printf("\nSoma: A + B");
	result = somaMatriz(a, b);
	imprimeMatriz(result);
	apagaMatriz(result);

	printf("\nProduto: A * B");
	result = multiplicaMatriz(a, b);
	imprimeMatriz(result);
	apagaMatriz(result);

	apagaMatriz(a);
	apagaMatriz(b);

	printf("\n\nFIM DO PROGRAMA.");

	return EXIT_SUCCESS;
}