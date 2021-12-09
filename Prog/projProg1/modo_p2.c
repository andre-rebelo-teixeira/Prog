#include<stdio.h>
#include<stdlib.h>
#include"modo_p2.h"
#include"tabuleiro.h"
#include"headers.h"

void modo_posicionamento2(int linhas, int colunas,int *tabuleiro,int *pecas_por_tipo)
{
    //inicialização de variaveis 
    int linhas3x3;
    int colunas3x3;
    int ordem_colocacao[9];
    int pecas_por_colocar[8] = {0} ;
    int variante_aleatoria;
    int peca_a_colocar[3][3];
    int matriz_restricao[3][3];
    int permissao1;
    int flag;
    int numero_pecas_limite;
    int numero_pecas_a_colocar = 0;
    int pecas_a_colocar[8];
    

    //calculo do numero de matrizes 3x3 nas linhas e nas colunas
    linhas3x3 = linhas / 3;
    colunas3x3 = colunas / 3;

    numero_pecas_limite = (linhas * colunas / 18);

    for (int i=0; i<8;i++)
    {
        numero_pecas_a_colocar += *(pecas_por_tipo+i);

        pecas_a_colocar[i] = *(pecas_por_tipo+i);
    }
    //verificação das restriçoes
    if (restricao3(pecas_a_colocar) == 0)
    {
        printf("Modo no possivel, Restriçao \n");
        mensagemAjuda();
        exit(-1);
    }
    if (numero_pecas_a_colocar > numero_pecas_limite)
    {
        printf("Peças a mais \n");
        exit(-1);
    }

    //Faz os 1000 ciclos de tentativas caso não consiga inserir as pecas
    for (int ciclo = 1; ciclo < 1001; ciclo++)
    {
        //volta a tentar colocar as peças
        inicializa_a_zeros ((int*)tabuleiro, linhas, colunas);
        
        //Recomeça a colocação de peças no tabuleiro
        for (int i = 0; i < 8; i++)
        {
            pecas_por_colocar[i] = *(pecas_por_tipo + i);
        }

        //percorre o tabuleiro em grupos de 3 linhas
        for (int i = 0; i < linhas3x3; i++)
        {
            //percorre o tabuleiro em grupos de 3 colunas
            for(int j = 0; j < colunas3x3; j++)
            {
                //gera ordem aleatória para colocação de pecas
                gera_vetor_aleatorio((int*)ordem_colocacao);

                //percorre o vetor de peças que vai tentar colocar
                for (int k = 0; k < 9; k++)
                {
                    //caso coloque uma peça vazia atualiza a coordenada de posicionamento 
                    if (ordem_colocacao[k] == 0)
                    {
                        break;
                    }
                    else 
                    {   
                        //verifica se ainda existem peças deste tipo por colocar
                        if (pecas_por_colocar[ordem_colocacao[k]-1] >0)
                        {   
                            //calcula variante aleatória
                            variante_aleatoria = RetornaVarianteAleatoria(ordem_colocacao[k]);
                            
                            //copia a peça escolhida para a matriz 3x3 que vai ser inserida no tabuleiro
                            copia_uma_peca((int*)pecas[variante_aleatoria], (int*)peca_a_colocar);
                            
                            //calcula a matriz de restrição
                            calcula_matriz_restricao((int*)tabuleiro, (int*)matriz_restricao, linhas, colunas, i, j);

                            //verifica se consegue cumprir a restrição 1 colocando aquela peça
                            permissao1 = restricao1(matriz_restricao, peca_a_colocar);
                            
                            if (permissao1 == 1)
                            {
                                //insere a peca no tabuleiro 
                                insere_uma_peca((int*)tabuleiro, (int*)peca_a_colocar, i, j, colunas);

                                //diminui o numero de pecas a colocar deste tipo e passa para atualiza as coordenadas de posicionamento 
                                pecas_por_colocar[ordem_colocacao[k]-1]--;
                                break;
                            }
                            else
                            {
                                //caso não consiga inserir a peça tenta todas as variante da mesma
                                for (int l = 1; l< 13; l++)
                                {
                                    //calcula a variante global associada 
                                    variante_aleatoria = Conversor(ordem_colocacao[k], l);
                                    
                                    //verifica se a variante ainda é valida caso não seja passa para a proxima peça
                                    if (variante_aleatoria == -1 )
                                    {
                                        break;
                                    }

                                    //copia a peça escolhida para uma matriz que será inseriada no tabuleiro
                                    copia_uma_peca((int*)pecas[variante_aleatoria], (int*)peca_a_colocar);

                                    ////calcula a matriz de restrição
                                    calcula_matriz_restricao((int*)tabuleiro, (int*)matriz_restricao, linhas, colunas, i, j);

                                    //verifica se consegue cumprir a restrição 1 colocando aquela peça
                                    permissao1 = restricao1(matriz_restricao, peca_a_colocar);
                                    
                                    if (permissao1 == 1)
                                    {
                                        //insere a peca no tabuleiro 
                                        insere_uma_peca((int*)tabuleiro, (int*)peca_a_colocar, i, j, colunas);
                                        
                                        //diminui o numero de pecas a colocar deste tipo e passa para atualiza as coordenadas de posicionamento 
                                        pecas_por_colocar[ordem_colocacao[k]-1]--;
                                        
                                        //não testa mais variantes nem mais para a 
                                        k = l = 1000; 
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } 

        //verifica se colocou todas as pecas
        flag = 0;
        for (int i = 0; i < 8 ; i++)
        {   
            if(pecas_por_colocar[i] != 0)
            {
                flag = 1;
            }
        } 
        //caso tenha colocado todas as peças acaba o posicionamento 
        if (flag == 0)
        {
            break;
        } 
    }
}

void gera_vetor_aleatorio(int *array)
{
    //inicializa o vetor com o valor corresppondente ao indice da posição 
    for (int i = 0; i < 9; i++) 
    {     
        *(array + i) = (i);
    }

    //torna o vetor aleatório
    //para cada posição troca o valor com o valor de uma posição aleatorio 
    for (int i = 0; i < 9 ; i++)
    {    
        int temp = *(array + i);
        int randomIndex = rand() % 9;

        *(array + i) = *(array + randomIndex);
        *(array + randomIndex) = temp;
    }

}