#include"modo_p1.h"

void modo_p1(int linhas, int colunas, int *tabuleiro, int *ocurrencias) // Posicionamento p1 feito
{
    int  restricao[3][3]= {{0}};
    
    int num_colunas3x3 = colunas / 3, num_linhas3x3 = linhas / 3, num_pecas_colocadas = 0;
    int Permissao1, Permissao2;
    
    inicializa_a_zeros((int *)tabuleiro, linhas, colunas);//Inicializaço do tabuleiro com todos os elementos a zero


    //percorre o tabuleiro em grupos de 3 linhas
    for (int i = 0; i < num_linhas3x3; i++) 
    {   
        //precorre o tabuleiro em grupos de 3 colunas
        for(int j = 0; j < num_colunas3x3; j++)
        {   
            //calcula a matriz de restrições para a matriz 3x3 atual
            int num_tentativas = 0;
            calcula_matriz_restricao((int *)tabuleiro, (int *)restricao ,linhas, colunas,i,j);

            //fica em ciclo infinito ae gerar uma peça
            while(1)
            {            

                //gera uma peça para tentar ser inserida no tabuleiro
                int peca_gerada[3][3];
                int peca_final=rand() % 43;
                int identificador_da_peca = Conversor2(peca_final);
                
                //depois de gerar uma peça copia para o matriz que será inserida 
                copia_uma_peca((int *)pecas[peca_final], (int *)peca_gerada);

                //verifica as permissões 
                Permissao1 = restricao1(restricao,peca_gerada);
                Permissao2 = restricao2(linhas,colunas,num_pecas_colocadas+1);

                //se for possivel insere a peça no tabuleiro 
                if (Permissao1 == 1 && Permissao2 == 1)
                {
                    //função insere a peça no tabuleiro
                    insere_uma_peca((int *)tabuleiro, (int *)peca_gerada, i, j,colunas); // insere uma peça no tabuleiro de jogo

                    //verifica se peça inserida é a peça nula
                    if (peca_final != 0)
                    {
                        //incrementa o numero de peças 
                        num_pecas_colocadas++;
                        *(ocurrencias+identificador_da_peca - 1) += 1;
                    }
                    break; 
                }
                //para garantir que não se fica num ciclo infinito
                if (num_tentativas == 1000)
                {
                    break;
                }
                num_tentativas++;
            }
        }
    }
}