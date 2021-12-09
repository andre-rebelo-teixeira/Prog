#include "disparo.h"

//função que controla  o modo de disparo 1:
void modo_disparo1(int linhas, int colunas, int * vector_numero_pecas, int * tabuleiro_disparados, int * tabuleiro_pecas)
{
    // começa a contagem do tempo
    time_t tempo_de_inicio = time(NULL);

    //declaração das variaveis utilizadas:
    int numero_quadrados_ocupados = 0;
    int tiros_totais = 0;
    int tiros_acertados = 0;
    int aux1, aux2;
    char user_input;

    //inicializa o tabuleiro de verificação de disparos a zero
    inicializa_a_zeros((int *) tabuleiro_disparados, linhas, colunas);

    //inicializa a zeros o tabuleiro das peças já acertadas
    inicializa_a_zeros((int *)tabuleiro_pecas, linhas, colunas);

    //calcula quanto quadrados ocupados se encontram no tabuleiro
    numero_quadrados_ocupados = numero_de_quadrados_ocupados_no_tabuleiro((int *)vector_numero_pecas);

    //dispara numa posição enquanto não tiver acertado em todos os quadrados ocupadas
    while (tiros_acertados < numero_quadrados_ocupados)
    {
        //gera uma coordenada de disparo random
        aux1 = (rand() % linhas);
        aux2 = (rand() % colunas);

        //verifica se já foi disparado no local
        if (*(tabuleiro_disparados + aux1 *colunas +aux2) == 0)
        {

            // afirma local como atingido, e aumenta numero de tiros totais
            *(tabuleiro_disparados + aux1 *colunas +aux2) = 1;
            tiros_totais++;

            //imprime as coordenadas de disparo
            printf("%c%d \n", 'A'+aux2, linhas-aux1);

            //aguarda pela confirmação do utilizador
            if (scanf("%c", &user_input) != 1)
            {
                //caso scanf não retorne um diz que o utilizador não indicou nada e abandona o programa
                printf("não consegui ler");
                exit(-1);
            }

            while (getchar()!= '\n');

            //analise da informação dada pelo utilizador:
            switch(user_input)
            {
                case '-': //disparou na agua
                    break;

                case '1': case '2': case '3': case '4': case '5': case '6' :case'7': case '8': //disparou numa posição ocupada por peça
                    tiros_acertados++;
                    *(tabuleiro_pecas+aux1*colunas+aux2) = user_input - '0'; //coloca o tabuleiro das peças já disparadas com o valor da peça acertada
                    break;
            }
        }
    }
    //imprime o tabuleiro que foi criado com base no input do utilizador
    imprime_tabuleiro((int*)tabuleiro_pecas, linhas, colunas);

    time_t fim_de_jogo = time(NULL);

    printf("Fim de Jogo: %d jogadas em %u segundos\n", tiros_totais, (unsigned)(fim_de_jogo - tempo_de_inicio));
}

//função que controla o modo de disparo 2
void modo_disparo2(int linhas, int colunas, int *vetor_numero_pecas, int * tabuleiro_pecas)
{
    //Começa a contagem do tempo
    time_t tempo_de_inicio = time(NULL);

    //inicialização das variaveis
    int linhas3x3=linhas / 3;
    int colunas3x3 = colunas / 3;
    int i, j, k;
    int linha_disparo = 0;
    int coluna_disparo = 0;
    int vector_colunas[9]={1,1,1,0,2,0,2,2,0};
    int vector_linhas[9]={1,0,2,1,1,0,2,0,2};
    int numero_quadrados_ocupados = 0;
    int numero_quadrados_atingidos_geral=0;
    int numero_quadrados_atingidos_matrix3x3=0;
    int numero_quadrados_ocupados_matriz3x3=0;
    char user_input;
    int tiros_totais = 0;

    //inicializa a zeros o tabuleiro em que vai ser guardado o input do utilizador
    inicializa_a_zeros((int*)tabuleiro_pecas, linhas, colunas);

    //calcula o numero de posições ocupadas no mapa
    for(int i = 0; i<8;i++)
    {
        numero_quadrados_ocupados +=  *(vetor_numero_pecas+i) * (i+1);
    }


    //ciclo que precorre as linhas do tabuleiro andando de 3 em 3
    for (i=0; i < linhas3x3 ;i++)
    {
        //ciclo que precorre as linhas do tabuleiro andando de 3 em 3
        for(j = 0; j<colunas3x3 ;j++)
        {
             //reset do numero de quadrados a atingir e coloca o numero de quadrados a atingir a 9, para percorrer o vector de 9 posições de disparo
            numero_quadrados_ocupados_matriz3x3 = 9;
            numero_quadrados_atingidos_matrix3x3 = 0;

            //cicilo que trata dos 9 disparos a fazer na matriz 3x3
            for(k=0; k<9; k++)
            {
                //cria a linha e coluna de disparo reais do tabuleiro 
                linha_disparo = vector_linhas[k]+i*3;
                coluna_disparo = vector_colunas[k] + j*3;
                printf("%c%d \n", 'A'+coluna_disparo, linhas-linha_disparo);

                //deteta o user input para saer no que acertou
                if ((scanf("%c", &user_input)) != 1)
                {
                    printf("não consegui ler");
                    exit(-1);
                }
                tiros_totais++;

                while (getchar()!= '\n');
                
                switch(user_input)
                {
                    case '-': //disparou na agua
                        break;

                    case '1': case '2': case '3': case '4': case '5': case '6' :case'7': case '8': //disparou numa posiçãp ocupada
                        numero_quadrados_atingidos_matrix3x3++; // aumenta o numero de quadrados acertados dentro da matriz 3x3 em que estamos
                        numero_quadrados_atingidos_geral++; // aumenta o numero de quadrados acertados no tabuleiro completo 
                        numero_quadrados_ocupados_matriz3x3 = user_input -'0';
                       //( *(tabuleiro_pecas+linha_disparo*MAX_COLUNAS))=0;
                        *(tabuleiro_pecas + linha_disparo*colunas + coluna_disparo) = user_input - '0';
                        break;
                }
                
                //Compara se já desparou em todos as posiçĩes ocupadas dentro 
                if (numero_quadrados_atingidos_matrix3x3 == numero_quadrados_ocupados_matriz3x3) 
                {
                    break;
                }

            }
            //Compara  se já disparou em todas as posições que o tabuleiro tem ocupadas
            if (numero_quadrados_ocupados == numero_quadrados_atingidos_geral)
            {
                //acaba todos os ciclos pois o jogo acabou 
                i = j = 1000;
                break;
            }
        }
    }

    time_t fim_de_jogo = time(NULL);

    //imprime a mensagem de final do jogo com o numero de tiros totais e com o tempo que demorou a correr o programa
    printf("Fim de Jogo: %d jogadas em %u segundos\n", tiros_totais, (unsigned)(fim_de_jogo - tempo_de_inicio));

    //imprime o tabuleiro com base no user input
    imprime_tabuleiro((int*)tabuleiro_pecas, linhas, colunas);
}

//função que controla o modo de disparo 3
void modo_disparo3(int linhas, int colunas, int * vetor_numero_pecas, int *tabuleiro)
{
    // começa a contagem do tempo
    time_t tempo_de_inicio = time(NULL);

    //inicialização de variaveis:
    int linhas3x3=linhas / 3;
    int colunas3x3 = colunas / 3;
    int i, j, k;
    int linha_disparo = 0;
    int coluna_disparo = 0;
    int vector_colunas[9]={1,1,1,0,2,0,2,2,0};
    int vector_linhas[9]={1,0,2,1,1,0,2,0,2};
    int numero_quadrados_ocupados = 0;
    int numero_quadrados_atingidos_geral=0;
    int numero_quadrados_atingidos_matrix3x3=0;
    int numero_quadrados_ocupados_matriz3x3=0;
    char user_input;
    int peca_atual[3][3];
    int matrix_restricao[3][3];
    int tiros_totais = 0;

    //inicializaço do tabuleiro calculado pelo utilizador a zeros
    inicializa_a_zeros((int *) tabuleiro, linhas, colunas);

    //caclculo do numero de posições do tabuleiro ocupadas por barcos
    for(int i = 0; i<8;i++)
    {
        numero_quadrados_ocupados +=  *(vetor_numero_pecas+i) * (i+1);

    }


    //ciclo que percorre as linhas do tabuleiro andando de 3 em 3 linhas
    for (i=0; i < linhas3x3 ;i++)
    {
        //ciclo que percorre as colunas do tabuleiro andando de 3 em 3 colunas
        for(j = 0; j<colunas3x3 ;j++)
        {
            //reset do numero de quadrados a atingir e coloca o numero de quadrados a atingir a 9, para percorrer o vector de 9 posições de disparo
            numero_quadrados_ocupados_matriz3x3 = 9;
            numero_quadrados_atingidos_matrix3x3 = 0;

            //inicializa a peça atual de disparo a zeros
            inicializa_a_zeros((int *)peca_atual, 3, 3);

            //inicializa a matriz de restrição para cada peça e de seguida calcula-a com base no tabuleiro
            inicializa_a_zeros((int *)matrix_restricao, 3, 3);
            calcula_matriz_restricao((int *)tabuleiro, (int *)matrix_restricao ,linhas, colunas,i,j);


            for(k=0; k<9; k++)
            {
                //conversão da coordenada de disparo local (dentro da matriz 3x3) para a coordenada de disparo global (definida de acordo com o mapa do utilizador)
                linha_disparo = vector_linhas[k]+i*3;
                coluna_disparo = vector_colunas[k] + j*3;
                if(matrix_restricao[vector_linhas[k]][vector_colunas[k]] == 1)//não pode haver peça neste local devido a restrição 1
                {
                    continue; // comando que faz com que execute o proximo passo do ciclo
                }



                //impressao da coordenada de disparo
                printf("%c%d\n",'A'+coluna_disparo, linhas-linha_disparo);

                //leitura do caracter introduzido pelo utilizador : agua ou navio
                    if ((scanf("%c", &user_input)) != 1)
                    {
                        printf("não consegui ler");
                        exit(-1);
                    }

                    tiros_totais++;

                    while (getchar()!= '\n');
                    switch(user_input)
                    {
                        case '-': //disparou na agua
                            break;

                        case '1': case '2': case '3': case '4': case '5': case '6' :case'7': case '8':
                            numero_quadrados_atingidos_matrix3x3++;
                            numero_quadrados_atingidos_geral++;
                            numero_quadrados_ocupados_matriz3x3 = user_input -'0';
                            peca_atual[vector_linhas[k]][vector_colunas[k]] = user_input-'0';
                            break;
                    }
                //verificacao do numero de quadrados atingidos na matriz 3x3. caso tenha afundado uma peça, passa a matriz 3x3 seguinte
                if (numero_quadrados_atingidos_matrix3x3 == numero_quadrados_ocupados_matriz3x3)
                {
                    insere_uma_peca((int*)tabuleiro, (int*)peca_atual,i,j,colunas);
                    break;
                }
                //proxima_coordenada_disparo:
                //aux = 1;
            }

            //ve se já acertou em todos as posições que se encontravam ocupads no tabuleiro
            if (numero_quadrados_ocupados == numero_quadrados_atingidos_geral)
            {
                //sai de todos os ciclos que controlam o disparo pois o jogo acabaou 
                i = j = 1000;
                break;
            }
        }
    }

    time_t fim_de_jogo = time(NULL);

    //imprime a mensagem de final do jogo com o numero de tiros totais e com o tempo que demorou a correr o programa
    printf("Fim de Jogo: %d jogadas em %u segundos\n", tiros_totais, (unsigned)(fim_de_jogo - tempo_de_inicio));
    imprime_tabuleiro((int*)tabuleiro, linhas, colunas);

}

//funcão calcula o numero de posições ocupadas no tabuleiro para o computador saber quando terminar o jogo
int numero_de_quadrados_ocupados_no_tabuleiro(int *vector_numero_pecas)
{
    int numero_quadrados_ocupados = 0;
    for(int i = 0; i<8;i++)
    {
        numero_quadrados_ocupados +=  *(vector_numero_pecas+i) * (i+1);

    }
    return numero_quadrados_ocupados;
}
    