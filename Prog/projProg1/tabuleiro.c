#include"tabuleiro.h"

/*----------------------------------------------------------------------------------------------------------------------------------------

                Inicio da declaração das funções que vão ser usadas para criar o tabuleiro

----------------------------------------------------------------------------------------------------------------------------------------*/


void inicializa_a_zeros(int *arr, int linhas, int colunas)
{ // esta função serve para começar o tabuleiro todo a zeros para não haver erros na colocação de peças
    for (int i=0; i < linhas; i++)
    {
        for (int j=0; j < colunas; j++)
        {
            *((arr+i*colunas)+j) = 0;
        }
    }
}

void copia_uma_peca(int *peca_a_copiar, int *peca_nova) 
{ // passa uma pessa das variaveis definidas por nós do vetor peças para uma nova matriz (peca_a_copiar) de modo a que depois possa ser inserida no tabuleiro
    for (int i=0; i < 3; i++)
    { 
        for (int j=0; j < 3; j++)
        {
            *((peca_nova+i*3)+j) = *((peca_a_copiar+i*3)+j);
        }
    }
}

void insere_uma_peca(int *tabuleiro, int *peca, int linhas3x3, int colunas3x3, int colunas) 
{ // esta função ser para inserir uma peça no tabuleiro de modo a não ficar sempre a zero 
    for (int i=0; i < 3; i++)
    {
        for (int j=0; j < 3; j++)
        {   
            int pos_x = i+ linhas3x3*3;
            int pos_y = j+ colunas3x3*3;
            *((tabuleiro+pos_x*colunas)+pos_y) = *((peca+i*3)+j);
        }
    }
}

void imprime_tabuleiro (int * tabuleiro,int linhas, int colunas)
{ //esta função imprime o tabuleiro de jogo no terminal pra o utilizador conseguir ver o jogo e as peça
    for (int l = 0;l < linhas; l++) 
    {   
        if (linhas - l < 10) {printf(" ");};
        
        printf("%d   ",linhas-l); // Print dos numeros correspondentes às linhas

        for (int c = 0; c < colunas; c++)
        {
            if (*((tabuleiro + l*colunas) + c) == 0) 
            {
                printf("-  ");
            }
            else 
            printf("%d  ", *((tabuleiro + l*colunas) + c));
        }
        printf("\n");
    }
    printf("     ");

    for(char i = 65; i < 65 + colunas; i++)  //Print das letras correspondentes às colunas
    {
        printf("%c  ", i);
    }
}

void calcula_matriz_restricao(int *arr, int *restricao , int linhas, int colunas, int linhas3x3, int colunas3x3) 
{ //esta funcção calcula a matriz de restriçao de cada quadricula da matriz, sendo que se a soma dos quadrados 8 quadrados 'vizinhos' do mesmo for maior do que 1, 
  //colocaa a matris restrição a 1, esta matriz será usada para ser possivel calcular a restrição 1 das peças (vizinhança)
    
    for (int k = 0; k <= 2; k++) // GERAR A MATRIZ DE RESTRIÇÃO - É INDEPENDENTE DA PEÇA QUE VAMOS COLOCAR - PERCORRE AS TRÉS POSIÇÕES DA MATRIZ 3x3
    {
        for (int l = 0; l <= 2; l++)
        {   
            int soma = 0;
            for (int x = -1; x <= 1; x++) // PERCORRER A VIZINHANÇA DE CADA ELEMENTO DA MATRIZ 3x3 EM QUE NOS ENCONTRAMOS E VERIFICA SE JÁ FORAM COLOCADAS PEÇAS NA VIZINHANÇA
            {
                for (int y = -1; y <= 1; y++)
                {
                    int pos_x = linhas3x3 * 3 + k + x;
                    int pos_y = colunas3x3 * 3 + l + y;
                    if(pos_x >= 0 && pos_x < linhas && pos_y >= 0 && pos_y < colunas)
                    {
                        soma += *((arr + pos_x*colunas)+pos_y);
                    }
                }
            }
            if (soma > 0)
            {
                *((restricao+k*3)+l) = 1;
            }
            else 
            {
                *((restricao+k*3)+l) = 0;
            }
        }
    }
}

int Calcula_numero_quadriculas_ocupadas(int *tabuleiro, int linhas, int colunas)
{ //calcula a quantidade de quadricas que não estejam em branco no tabuleiro para ser possivel ao computador descobrir quando destruiu todos os barcos
    int numero_quadrados_ocupados = 0;

    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            if (*((tabuleiro + i*colunas)+ j) != 0)
            {
                numero_quadrados_ocupados++;
            }

        }
    }
    return numero_quadrados_ocupados;
}

