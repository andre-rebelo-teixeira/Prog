#ifndef TABULEIRO
#define TABULEIRO

#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<time.h>
#include"Ajuda.h"
#include"Conversor.h"
#include"Restricoes.h"
#include"pecas.h"
#include"modo_p1.h"


void modo_p1(int linhas, int colunas, int *tabuleiro, int *ocorrencias);
void modo_p2(int linhas, int colunas,int*tabuleiro,int *pecas_por_tipo);
void desenharTabuleiro(int linhas, int colunas);
int **copiar_matriz_3x3(int *peca);
void inicializa_a_zeros(int *arr, int linhas, int colunas);
void insere_uma_peca(int *tabuleiro, int *peca, int linhas3x3, int colunas3x3, int colunas);
void imprime_tabuleiro (int * tabuleiro,int linhas, int colunas);
void copia_uma_peca(int *peca_a_copiar, int *peca_nova);
int calcula_soma(int *arr, int linhas, int colunas);
void calcula_matriz_restricao(int *arr, int *restricao , int linhas, int colunas, int linhas3x3, int colunas3x3);
int Calcula_numero_quadriculas_ocupadas(int *tabuleiro, int linhas, int colunas);

#endif
