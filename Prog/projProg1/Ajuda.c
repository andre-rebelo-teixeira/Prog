#include"Ajuda.h"

//Função escrevo no ecrâ a mensagem de ajuda quando o utilizado fornecer parametros errados
void mensagemAjuda()
{
    printf("Diferentes opções sobre o que pode fazer:\n\
            -h Ajuda para o utilizador \n\
            -t Dimensões do tabuleiro (linhas x coluna) -  Se nao for dado nenhum valor será considerado linhas = 9 e colunas = 9 \n\
            -j Modo de jogo (0 a 2) - Se não foi dado valor, será considerado como 0 \n\
            -p Modo de posicionamento de peças pelo computador (1 a 2) - O valor predefinido será de 1 \n\
            -d Modo de Disparo de peça pelo computador (1 a 3) - O valor predefinido será de 1 \n\
            -1 Número de peças tipo 1 (minimo 1) \n\
            -2 Número de peças tipo 2 \n\
            -3 Número de peças tipo 3 \n\
            -4 Número de peças tipo 4 \n\
            -5 Número de peças tipo 5 \n\
            -6 Número de peças tipo 6 \n\
            -7 Número de peças tipo 7 \n\
            -8 Número de peças tipo 8 \n\n\
Tabelueiro:\n\
           -Tem de ser no minimo 9x9 e no maximo 15x24;\n\
           -Os valores das linhas e colunas têm de ser multiplos de 3\n\
Instruções para modo de disparo -d (1-3) apenas são validas se o modo de jogo -j for o 2\n\n\
Opções que indicam o numeor de peças -(1-8): \n\
            - Apenas são validas com os modos de jogo (-j) 1 e 2 se o modo de posicionamento for o modo 2;\n\
            - No moodo de jogo 2 esta instrução serve para o computador saber quando o jogo acaba.\n\n\
Opçoes de disparo (-d) apenas devem ser validas se o modo de jogo (-j) for o 2 \n\n\
Restrição 2 - O número máximo de peças por tabuleiro está limitado a: linhas * colunas / 9.\n\
No caso de o número de peças ser inferior ao limite, devem-se considerar, nos espaços restantes, matrizes de \n\
3x3 vazias\n\
Restrição 3 - Num jogo, segue-se a regra de nunca ter mais peças de um tipo de maior dimensão do que peças de um tipo de menor dimensão\n\
Restrição 4 - Mais, o número total de peças não deve exceder 50/100 do número de matrizes 3x3 num tabuleiro \n\
Restriçoes 3 e 4 apenas validas para o modo de posicionamento 2 \n");
}