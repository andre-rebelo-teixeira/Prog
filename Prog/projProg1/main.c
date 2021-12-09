#include"headers.h"
#include"tabuleiro.h"
#include"modo_j1.h"
#include"modo_p2.h"

#define MAX_LINHAS 15
#define MAX_COLUNAS 24

int main(int argc,char *argv[])
{
    srand(time(0));

    int vector_user_input[] = {9,9,0,1,1,1,0,0,0,0,0,0,0}; //vetor que irá guardar os valores passados pelo terminal ao chamar o programa. 
    int linhas=12;
    int colunas=12;
    int modo_jogo;
    int modo_disparo;
    int modo_posicionamento;
    int numero_pecas[8]={0};
    int ocorrencias[8] = {0};
    int tabuleiro[MAX_LINHAS][MAX_COLUNAS];
    int tabuleiro_disparos[MAX_LINHAS][MAX_COLUNAS];

    UserInput(argc,argv, (int*)vector_user_input);

    //Passagem do valores do vetor que guarda o user input para as variáveis/ vetor a utilizar:
    linhas=vector_user_input[0];
    colunas=vector_user_input[1];
    modo_jogo=vector_user_input[2];
    modo_posicionamento=vector_user_input[3];
    modo_disparo=vector_user_input[4];
    numero_pecas[0]=vector_user_input[5];
    numero_pecas[1]=vector_user_input[6];
    numero_pecas[2]=vector_user_input[7];
    numero_pecas[3]=vector_user_input[8];
    numero_pecas[4]=vector_user_input[9];
    numero_pecas[5]=vector_user_input[10];
    numero_pecas[6]=vector_user_input[11];
    numero_pecas[7]=vector_user_input[12];
    

    inicializa_a_zeros((int*)tabuleiro, linhas, colunas);   
    
    //Seleção dos modos de jogo com base no input do utilizador 
    if (modo_jogo == 0)
    {
        if(modo_posicionamento == 1)
        {
            //cria um tabuleiro com o modo de posicionamento 1
            modo_p1(linhas, colunas, (int*)tabuleiro, (int*)ocorrencias);
            
            //imprime no ecrã a o tamanho e numero de peças do tabuleiro criado
            printf("%dx%d ", linhas, colunas);
            for(int i = 0; i <8; i++)
            {
                printf("%d ", ocorrencias[i]);
            }
            printf("\n");

            //imprime o tabuleiro que foi criado 
            imprime_tabuleiro((int*)tabuleiro, linhas, colunas);
        }
        else if (modo_posicionamento == 2)
        {
            //cria uma tabuleiro com o modo de posicionamento 2
            modo_posicionamento2(linhas, colunas,(int *)tabuleiro,(int *)numero_pecas);
            
            //imprime no ecrã o tamanho e numero de peças do tabulerio que foi criado
            printf("%dx%d ", linhas, colunas);
            for(int i = 0; i <8; i++)
            {
                printf("%d ", numero_pecas[i]);
            }
            printf("\n");
            
            //imprime no ecrâ o tabuleiro criado
            imprime_tabuleiro((int*)tabuleiro, linhas, colunas);


        }
        else
        {
            printf("definiçoes inválidas");
            exit(-1);
        }
    }
    else if(modo_jogo == 1)
    {

        if(modo_posicionamento == 1)
        {
            //cria um tabuleiro com o modo de posicionament 1
            modo_p1(linhas, colunas, (int*)tabuleiro, (int*)ocorrencias);

            //inicia o modo de jogo 1
            modo_j1(linhas, colunas, (int*)tabuleiro, (int*)vector_user_input,(int *)ocorrencias);
            
            //imprime no ecrâ o tabuleiro com que foi jogado
            imprime_tabuleiro((int*)tabuleiro, linhas, colunas);
        }
        else if (modo_posicionamento == 2)
        {
            //cria uma tabuleiro com o modo de posicionamento 2
            modo_posicionamento2(linhas, colunas,(int *)tabuleiro,(int *)numero_pecas);

            //inicia o modo de jogo 1
            modo_j1(linhas, colunas, (int*)tabuleiro, (int*)vector_user_input, (int*)numero_pecas);

            //imprime no ecrâ o tabuleiro com que foi jogado
            imprime_tabuleiro((int*)tabuleiro, linhas, colunas);
        }
        else
        {
            printf("definiçoes inválidas");
            exit(-1);
        }

    }
    else if (modo_jogo == 2)
    {
        //imprime no ecrã o tipo de jogo, o que espera, o tamanho e numero de peças do tabuleiro 
        printf("* ================================\n* Modo de Jogo 2 \n* Crie um tabuleiro com as características indicadas \n* Responda aos disparos do programa\n* ================================\n");
        printf("%dx%d ", linhas, colunas);
        for(int i = 5; i < 13; i++)
        {
            printf("%d ", vector_user_input[i]);
        }
        printf("\n");
        if (modo_disparo == 1)
        {
            //chama a função que inicia o modo de disparo 1
            modo_disparo1(linhas, colunas, (int*)numero_pecas, (int*)tabuleiro_disparos, (int*)tabuleiro);
        }
        else if(modo_disparo == 2)
        {
            //chama a função que inicia o modo de disparo 2
            modo_disparo2(linhas, colunas, (int*)numero_pecas,(int*)tabuleiro); 
        }
        else if(modo_disparo == 3)
        {
            //chama a função que inicia o modo de disparo 3
            modo_disparo3(linhas, colunas, (int*)numero_pecas, (int*)tabuleiro);
        }
        else 
        {
            printf("modo de disparo não se encontra dentro de gama");
            mensagemAjuda();
        }
    }
    else
    {
        printf("Modo de jogo não especificado \n");
        mensagemAjuda();
    }

    printf("\n");
    return 0;
}
