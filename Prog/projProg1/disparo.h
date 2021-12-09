#ifndef DISPARO
#define DISPARO

#include "tabuleiro.h"
#include <time.h>
#include <stdio.h>
#include "modo_p1.h"

void modo_disparo1(int linhas, int colunas, int * vector_numero_pecas, int * tabuleiro_disparados, int * tabuleiro_pecas);
void modo_disparo2(int linhas, int colunas, int *vetor_numero_pecas, int * tabuleiro_pecas);
void modo_disparo3(int linhas, int colunas, int * vetor_numero_pecas, int *tabuleiro);
int converte_numero_linha_para_linha_matriz(int numero_linha, int linhas);
int confirma_tiro(int *tabuleiro, int linha_disparo, int coluna_disparo, int linhas,int colunas);
int numero_de_quadrados_ocupados_no_tabuleiro(int *vector_numero_pecas);

#endif 