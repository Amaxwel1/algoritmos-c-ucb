#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void troca(char **A, char **B){
    char *temp = *A;
    *A = *B;
    *B = temp;
}

int particao(char *vet[], int inicio, int final, int *trocas, int *comparacoes ){

    char *pivot = vet[final];
    int i = inicio - 1;

    for(int j = inicio; j <= final - 1; j++){
        (*comparacoes)++;
        if(strcmp(vet[j], pivot) < 0){
            i++;
            troca(&vet[i], &vet[j]);
        }
    }
    troca(&vet[i + 1], &vet[final]);
    (*trocas)++;
    return i + 1;

}

void quicksort(char *vet[], int inicio, int fim, int *trocas, int *comparacoes){
    if (inicio < fim){
        int pos = particao(vet, inicio, fim, trocas, comparacoes);
        quicksort(vet, inicio, pos - 1, trocas, comparacoes);
        quicksort(vet, pos + 1, fim, trocas, comparacoes);
    }
    
}

void gerarArquivo(char *vet[], int n, int trocas, int comparacoes, char *mediana ) {
    FILE *arquivo = fopen("saida.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de saída.");
        return;
    }

    fprintf(arquivo, "Numero de trocas: %d\n", trocas);
    fprintf(arquivo, "Numero de comparações: %d\n", comparacoes);
    fprintf(arquivo, "Mediana: %s\n", mediana);

    fprintf(arquivo, "\n");

    fprintf(arquivo, "Vetor ordenado:\n");
    for (int i = 0; i < n; i++) {
        fprintf(arquivo, "(%d) %s\n", i + 1, vet[i]);
    }

    fclose(arquivo);
}


int main() {

    char *arr[] = {
        "maca", "banana", "pera", "uva", "laranja", "abacaxi", "limao", 
        "manga", "abacate", "kiwi", "cereja", "morango", "pessego", "goiaba", 
        "melancia", "framboesa", "amora", "caqui", "figo", "papaya"
    };
    int n = sizeof(arr) / sizeof(arr[0]);
    int trocas = 0, comparacoes = 0;

    quicksort(arr, 0, n - 1, &trocas, &comparacoes);

    printf("Strings ordenadas:\n");
    for (int i = 0; i < n; i++) {
        printf("(%d) %s\n", i + 1, arr[i]);
    }

    printf("Numero de trocas: %d\n", trocas);
    printf("Numero de comparacoes: %d\n", comparacoes);

    char *mediana;
    if (n % 2 == 0) {

    int meio1 = (n - 1) / 2;
    int meio2 = meio1 + 1;
    printf("Mediana: %s\n", arr[meio2]);
    mediana = arr[meio2];

    } else {
        int meio = (n - 1) / 2;
        printf("Mediana: %s\n", arr[meio]);
        mediana = arr[meio];
    }

    gerarArquivo(arr, n, trocas, comparacoes, mediana);


return 0;
}