#include"modo_j1.h"

void modo_j1(int linhas, int colunas, int *tabuleiro, int *vetor_user_input, int *ocorrencias)
{
    // começa a contagem do tempo
    time_t tempo_de_inicio = time(NULL);

    //declaração das variaveis que são necessárias 
    int numero_quadrados_ocupados = 0;
    int numero_quadrados_acertados = 0;
    int linha_disparo, coluna_disparo;
    char str[3], str_linha[10];
    int str_length;
    int i;
    int numero_de_tiros = 0;
    
    //calcula o numero de posições ocupadas no tabuleiro
    numero_quadrados_ocupados = Calcula_numero_quadriculas_ocupadas((int*)tabuleiro, linhas, colunas);

    //prints pedidos pelo professor 
    printf("* ================================\n* Modo de Jogo 1\n* Insira as Coordenadas de Disparo\n* ================================\n");
    printf("%dx%d ", linhas, colunas);
    for (int i = 0; i < 8; i++)
    {
        printf("%d ", ocorrencias[i]);
    }
    printf("\n");   

    //confirma se já acertou em todas as posições
    while(numero_quadrados_acertados < numero_quadrados_ocupados)
    {
        //reconhece a posição em que o utilizador quer disparar
        if ((scanf("%s", str)) != 1)
        {
            //caso não consiga reconhecer o input termina o programa
            printf("não consegui reconhecer o input");
            exit(1);
        }

        //incrementa o numero de tiros totais
        numero_de_tiros++;

        //reconheco o user input para conseguir obter as coordenadas de disparo pretendidas
        str_length = strlen(str);
        i=1;
        while(i<=str_length)
        {
            str_linha[i-1]=str[i];
            i++;
        }
        linha_disparo = linhas - atoi(str_linha);
        coluna_disparo = str[0]-'A';
        
        //escreve na consola o que existe na posição pretendida do tabuleiro 
        if(*((tabuleiro + linha_disparo * colunas) + coluna_disparo) == 0)
        {
            printf("- \n");
        }
        else 
        {
        printf("%d \n", *((tabuleiro + linha_disparo * colunas) + coluna_disparo));
        numero_quadrados_acertados++;
        }
    }
    //termina o jogo indicando o numero de tiros e o tempo de jogo
    time_t fim_de_jogo = time(NULL);

    printf("Fim de Jogo: %d jogadas em %u segundos\n", numero_de_tiros, (unsigned)(fim_de_jogo - tempo_de_inicio));
} 
   