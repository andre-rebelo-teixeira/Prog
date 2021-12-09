#include"Restricoes.h"

/*
restrição 0) -  As peças só podem ser colocadas em quadrículas de 3x3.
                Uma peça não pode ocupar mais do que uma quadrícula de 3x3 definida no tabuleiro. As quadrículas
                de 3x3 do tabuleiro definem-se avançando no eixo vertical e no eixo horizontal de 3 em 3. Dado que
                o tabuleiro tem sempre dimensão múltipla de 3 em ambos os eixos, pode ser sempre construído com
                base num número inteiro de quadrículas de 3x3 em ambas as direções.  

Restrição 1) -  As peças nunca podem ter arestas ou vértices de contacto com outras peças.

Restrição 2) -  O número máximo de peças por tabuleiro está limitado a: linhas * colunas / 9. No caso de o número de peças ser inferior ao limite,
                devem-se considerar, nos espaços restantes, matrizes de 3x3 vazias.

Restrição 3) -  Num jogo, segue-se a regra de nunca ter mais peças de um tipo de maior dimensão do que peças de um tipo de menor dimensão. 

Restrição 4) -  Mais, o número total de peças não deve exceder 50% do número de matrizes 3x3 num tabuleiro. 
*/

//verifica a restrição 
int restricao1(int MatrizRestricao[3][3], int MatrizPeca[3][3])
{
    int Permissao = 1;
        for (int i = 0; i <= 2; i++)
        {
            for (int j = 0; j <= 2; j++)
            {
                //verifica se em algum momento a matriz restrição e peça a tentar inserida são ambas diferentes de zero
                if (MatrizPeca[i][j] !=0 && MatrizRestricao[i][j] != 0)
                {
                    //retorna 0 se não for possivel inserir a peça
                    Permissao =  0;
                }
            }
        }
        //retorna 1 caso seja possivel inserir uma peça
        return Permissao;
}

//verifica a restrição 2
int restricao2(int NumeroLinhas, int NumeroColunas, int NumeroPecas) // return 1 caso a restrição seja comprida
{  
    int PecasLimite = NumeroLinhas * NumeroColunas / 9;

    if (NumeroPecas <= PecasLimite)
    {
        return 1;    
    }
    else 
    {
        return 0;
    }
}

//verifica a restrição 3
int restricao3(int numero_pecas_por_tipo[8])
{
    for (int i = 0; i<= 7; i++)
    {
        for(int j = i+1; j<=7; j++)
        {
         if(numero_pecas_por_tipo[j]>numero_pecas_por_tipo[i])
            {
                return 0;
            }
        }
    }
    return 1;
}

//verifica a restrição 4
int restricao4(int maximo, int numeroPecas)   //esta função recebe o valor de pg e da peça atual gerada, caso o limte maximo seja ultrapassado esta irá retornar 0 caso contrário irá retornar 1 dado.
{
    maximo /= 2; 

    if (numeroPecas > maximo)
    {
        return 0;
    } else
    {
        return 1;
    }

}



