#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

typedef struct No {
    double dado;
    struct No *proximo;
} No;

typedef struct {
    No *topo;
} Pilha;

void inicializar(Pilha *pilha) {
    pilha->topo = NULL;
}

void empilhar(Pilha *pilha, double valor) {
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro: Falha na alocação de memória\n");
        exit(EXIT_FAILURE);
    }
    novoNo->dado = valor;
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
}

double desempilhar(Pilha *pilha) {
    if (pilha->topo != NULL) {
        No *temp = pilha->topo;
        double valor = temp->dado;
        pilha->topo = temp->proximo;
        free(temp);
        return valor;
    } else {
        printf("Erro: Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
}

double avaliarExpressaoPosfixada(const char *expressao) {
    Pilha pilha;
    inicializar(&pilha);

    for (int i = 0; expressao[i] != '\0'; ++i) {
        if (isdigit(expressao[i]) || (expressao[i] == '.' && isdigit(expressao[i + 1]))) {
            // Interpretar números (incluindo números decimais)
            char *endptr;
            double numero = strtod(&expressao[i], &endptr);
            i = endptr - expressao - 1;  // Atualizar o índice para o próximo caractere
            empilhar(&pilha, numero);
        } else if (expressao[i] == ' ' || expressao[i] == '\t') {
            continue;
        } else {
            double operando2, operando1;

            if (isalpha(expressao[i])) {
                char operador[4] = {0};
                int j = 0;
                while (isalpha(expressao[i]) && j < 3) {
                    operador[j++] = expressao[i++];
                }
                --i; // Voltar um caractere para compensar o avanço adicional no loop

                if (strcmp(operador, "sin") == 0) {
                    operando1 = desempilhar(&pilha);
                    empilhar(&pilha, sin(operando1));
                } else if (strcmp(operador, "cos") == 0) {
                    operando1 = desempilhar(&pilha);
                    empilhar(&pilha, cos(operando1));
                } else if (strcmp(operador, "tan") == 0) {
                    operando1 = desempilhar(&pilha);
                    empilhar(&pilha, tan(operando1));
                } else if (strcmp(operador, "log") == 0) {
                    operando1 = desempilhar(&pilha);
                    empilhar(&pilha, log10(operando1));
                } else {
                    printf("Erro: Operador inválido\n");
                    exit(EXIT_FAILURE);
                }
            } else {
                switch (expressao[i]) {
                    case '+':
                        operando2 = desempilhar(&pilha);
                        operando1 = desempilhar(&pilha);
                        empilhar(&pilha, operando1 + operando2);
                        break;
                    case '-':
                        operando2 = desempilhar(&pilha);
                        operando1 = desempilhar(&pilha);
                        empilhar(&pilha, operando1 - operando2);
                        break;
                    case '*':
                        operando2 = desempilhar(&pilha);
                        operando1 = desempilhar(&pilha);
                        empilhar(&pilha, operando1 * operando2);
                        break;
                    case '/':
                        operando2 = desempilhar(&pilha);
                        operando1 = desempilhar(&pilha);
                        if (operando2 != 0.0) {
                            empilhar(&pilha, operando1 / operando2);
                        } else {
                            printf("Erro: Divisão por zero\n");
                            exit(EXIT_FAILURE);
                        }
                        break;
                    case '^': // potência
                        operando2 = desempilhar(&pilha);
                        operando1 = desempilhar(&pilha);
                        empilhar(&pilha, pow(operando1, operando2));
                        break;
                    default:
                        printf("Erro: Operador inválido\n");
                        exit(EXIT_FAILURE);
                }
            }
        }

        // Imprimir valores intermediários da pilha para depuração
        printf("Pilha: ");
        for (No *temp = pilha.topo; temp != NULL; temp = temp->proximo) {
            printf("%f ", temp->dado);
        }
        printf("\n");
    }

    if (pilha.topo != NULL) {
        return pilha.topo->dado;
    } else {
        printf("Erro: Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    const char *expressao = "0.5 45 sen 2 ^ +";
    double resultado = avaliarExpressaoPosfixada(expressao);
    printf("Resultado: %f\n", resultado);
    return 0;
}
