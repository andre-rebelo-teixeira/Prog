#include "print.h"

// *************************************************************************************************************************************************************************
// Esta função imprime todos os argumentos da listas que foram lidos
// Input - FIX_DATA *start - apontador para o primeiro elemento das estruturas do tipo FIX_DATA
// Input - char *name - nome do ficheiro de output escolhido pelo utilizador
// Output - nada é retornado pela funçao (void)
// *************************************************************************************************************************************************************************

void PrintList(FIX_DATA *start, char *name)
{
    // Criaçõ do ficheiro de output com o nome especificado pelo utilizador
    FILE *pToFile = fopen(name, "w");

    fprintf(pToFile, "country,country_code,continent,population,indicator,weekly_count,year_week,rate_14_day,cumulative_count\n");

    // Confirma a lista já ligada tem algum valor
    if (start != NULL)
    {
        //Define 2 ponteiros para estruturas do tipo FIX_DATA e VAR_DATA
        FIX_DATA *currentFixData = NULL;
        VAR_DATA *currentVarData = NULL;

        //inicializa as cabeças de lista de cada tipo
        currentFixData = start;
        currentVarData = currentFixData->data;

        //Ciclo que garante que todas as listas do tipo FIX_DATA são impressas
        while (currentFixData != NULL)
        {
            // Atualizador do apontador CurrentVarDara visto estarmos num País novo
            currentVarData = currentFixData->data;
            //Ciclo que garante que todas as lisstas do tipo VAR_DATA que se encontram associadas a lista FIX_DATA atual são impressas
            while (currentVarData != NULL)
            {
                fprintf(pToFile, "%s,%s,%s,%ld,%s,%i, %04d-%02d,%lf,%i\n",
                        currentFixData->countryName,
                        currentFixData->countryCode,
                        currentFixData->continent,
                        currentFixData->population,
                        currentVarData->indicator,
                        currentVarData->weeklyCount,
                        currentVarData->year,
                        currentVarData->week,
                        currentVarData->rate2Weeks,
                        currentVarData->cumulativeCount);

                //movimento do ponteiro da lista VAR_DATA
                currentVarData = currentVarData->next;
            }

            //movimento do ponteiro do tipo FIX_DATA
            currentFixData = currentFixData->next;
        }
    }

    // Fecho do ficheiro
    fclose(pToFile);
}

// *************************************************************************************************************************************************************************
// Esta função imprime todos os argumentos da listas que foram lidos
// Input - FIX_DATA *start - apontador para o primeiro elemento das estruturas do tipo FIX_DATA
// Input - char *name - nome d ficheiro de output escolhido pelo utilizador
// Output - nada é retornado pela funçao (void)
// *************************************************************************************************************************************************************************

void PrintListInBynary(FIX_DATA *start, char *name)
{
    // Criação de um ficheiro com o nome escolhido pelo utilizador
    FILE *pToFile = fopen(name, "wb");

    //Definiao e inicialização das variavies usadas na função
    FIX_DATA *currentFixData = NULL;
    VAR_DATA *currentVarData = NULL;
    FIX_DATA *iter;
    VAR_DATA *iter2 = NULL;
    int countTotal = 0;
    int countCountry = 0;
    int counter = 0;

    //inicializa as cabeças de lista de cada tipo
    if (start != NULL)
    {
        currentFixData = start;
        currentVarData = currentFixData->data;

        // Calcule qual o numero de listas do tipo FIX_DATA que existem
        for (iter = start; iter != NULL; iter = iter->next)
        {
            countTotal++;
        }

        // Escreve no documento binário quantas listas do tipo FIX_DATA existem
        fwrite(&countTotal, sizeof(int), 1, pToFile);

        //Ciclo que garante que todas as listas do tipo FIX_DATA são impressas
        while (currentFixData != NULL)
        {

            // Escreve os dados do tipo FIX_DATA
            fwrite(currentFixData->countryName, sizeof(char), COUNTRYNAME, pToFile);
            fwrite(currentFixData->countryCode, sizeof(char), COUNTRYCODE, pToFile);
            fwrite(currentFixData->continent, sizeof(char), CONTINENT, pToFile);
            fwrite(&currentFixData->population, sizeof(int), 1, pToFile);

            // Precorre toda a lista do tipo VAR_DATA para o pais escolhido para saber quantas existem
            for (iter2 = currentFixData->data; iter2 != NULL; iter2 = iter2->next)
            {
                // Contgem de quantas listas existem
                countCountry++;
            }

            // Escrita no ficheiro .dat de quantas listas do tipo VAR_DATA existem para o país selecionado
            fwrite(&countCountry, sizeof(int), 1, pToFile);

            // Atualizador do apontador CurrentVarDara visto estarmos num País novo
            currentVarData = currentFixData->data;
            //Ciclo que garante que todas as lisstas do tipo VAR_DATA que se encontram associadas a lista FIX_DATA atual são impressas
            while (currentVarData != NULL)
            {
                // Escrita dos dados do tipo VAR_DATA
                fwrite(currentVarData->indicator, sizeof(char), INDICATOR, pToFile);
                fwrite(&currentVarData->weeklyCount, sizeof(int), 1, pToFile);
                fwrite(&currentVarData->year, sizeof(int), 1, pToFile);
                fwrite("-", sizeof(char), 1, pToFile);
                fwrite(&currentVarData->week, sizeof(int), 1, pToFile);
                fwrite(&currentVarData->rate2Weeks, sizeof(double), 1, pToFile);
                fwrite(&currentVarData->cumulativeCount, sizeof(int), 1, pToFile);

                //movimento do ponteiro da lista VAR_DATA
                currentVarData = currentVarData->next;
            }
            // Coloca contador dos dados variavies a zero
            countCountry = counter = 0;

            //movimento do ponteiro do tipo FIX_DATA
            currentFixData = currentFixData->next;
        }
    }
    // Fecho do ficheiro
    fclose(pToFile);
}
