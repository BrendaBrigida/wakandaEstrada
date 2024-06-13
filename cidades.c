#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cidades.h"

#ifndef CIDADES_H
#define CIDADES_H

typedef struct{

char Nome[256];    // Nome do cidade
int Posicao;       // Posição da cidade

}Cidade;

typedef struct{

int N;           // Número de cidades
int T;           // Comprimento da estrada
Cidade *C;       // Vetor de cidades

}Estrada;

Estrada *getEstrada(const char *nomeArquivo);                      // Inicializa cidades no TAD indicado acima.
double calcularMenorVizinhanca(const char *nomeArquivo);           // Retorna a menor vizinhança.
char *cidadeMenorVizinhanca(const char *nomeArquivo);              // Retorna a cidade que tem menor vizinhança.

#endif



// Função para inicializar a estrutura Estrada a partir do arquivo de entrada

Estrada *getEstrada(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        return NULL;
    }

    int T, N;
    fscanf(arquivo, "%d", &T);
    fscanf(arquivo, "%d", &N);

    if (T < 3 || T > 1000000 || N < 2 || N > 10000) {
        fclose(arquivo);
        return NULL;
    }

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    estrada->N = N;
    estrada->T = T;
    estrada->C = (Cidade *)malloc(N * sizeof(Cidade));

    for (int i = 0; i < N; i++) {
        int posicao;
        char nome[256];
        fscanf(arquivo, "%d %s", &posicao, nome);
        if (posicao <= 0 || posicao >= T) {
            free(estrada->C);
            free(estrada);
            fclose(arquivo);
            return NULL;
        }
        estrada->C[i].Posicao = posicao;
        strcpy(estrada->C[i].Nome, nome);
    }

    fclose(arquivo);
    return estrada;
}

     //Funcao para calcular a menor vizinhanca entre todas as cidades

double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) {
        return -1.0; // Erro ao ler a estrada
    }

    double menorVizinhanca = estrada->T; // Inicializa com um valor maximo possivel

    for (int i = 0; i < estrada->N - 1; i++) {
        double vizinhanca = (estrada->C[i + 1].Posicao - estrada->C[i].Posicao) / 2.0;
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
        }
    }

    free(estrada->C);
    free(estrada);
    return menorVizinhanca;
}

    //Funcao para retornar o nome da cidade com a menor vizinhanca

char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) {
        return NULL; // Erro ao ler a estrada
    }

    double menorVizinhanca = estrada->T; // Inicializa com um valor maximo possivel
    int cidadeIndex = -1;

    for (int i = 0; i < estrada->N - 1; i++) {
        double vizinhanca = (estrada->C[i + 1].Posicao - estrada->C[i].Posicao) / 2.0;
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
            cidadeIndex = i;
        }
    }

    char *cidade = (char *)malloc(256 * sizeof(char));
    strcpy(cidade, estrada->C[cidadeIndex].Nome);

    free(estrada->C);
    free(estrada);
    return cidade;
}


int main(){

    const char *nomeArquivo = "teste01.txt";
    
    Estrada *estrada = getEstrada(nomeArquivo);
    if(estrada) {
        printf("Estrada carregada com sucesso!\n");
        free(estrada->C);
        free(estrada);
    } else {
        printf("Falha ao carregar a estrada.\n");
    }
    
    double menorVizinhanca = calcularMenorVizinhanca(nomeArquivo);
    printf("Menor vizinhanca: %.2f\n", menorVizinhanca);

    char *cidade = cidadeMenorVizinhanca(nomeArquivo);
    if (cidade) {
        printf("Cidade com menor vizinhanca: %s\n", cidade);
        free(cidade);
    } else {
        printf("Falha ao determinar a cidade com menor vizinhanca.\n");
    }

    return 0;
}