#include "readFiles.h"

// *************************************************************************************************************************************************************************
// Esta função ser para ler todos os ficheiros em binário que sejam necessário de ler
// Input - *char name - Array de caracteres que contem o nome do ficheiro que vai ser aberto pelo utilizador
// Output - FIX_DATA *startFixed - Apontador para a primeira estrutura do tipo FIX_DATA, ou seja par a head geral
// *************************************************************************************************************************************************************************

FIX_DATA *ReadInBynary(char *name)
{
    // Declaração e inicialização de todas as variaveis utilizadas ao longo da função
    FIX_DATA *startFixed = NULL;
    FIX_DATA *newestFixed = NULL;
    FIX_DATA *helper2 = NULL;
    VAR_DATA *start = NULL;
    int casos_totais = 0;
    int cases = 0;
    int year = 0;
    int week = 0;
    int populacao = 0;
    int numberOfFixedData = 0;
    int control = 0;
    int numberOfVarData = 0;
    int control_1 = 0;
    char country[COUNTRYNAME] = "";
    char countrycode[COUNTRYCODE] = "";
    char continent[CONTINENT] = "";
    char input[MAX] = "";
    char copyInput[MAX] = "";
    char helper[MAX] = "";
    char indicator[INDICATOR] = "";
    char dummy[1] = "";
    double ratio = 0.0;

    // Abertura do ficheiro que foi especificado
    FILE *pToFile = fopen(name, "rd");

    // Confirmação de se o ficheiro foi aberto ou se houve agum erro
    if (pToFile == NULL)
    {
        printf("Erro a abrir o ficheiro \n");
        exit(1);
    }

    // Leitura do numero de estruturas do tipo FIX_DATA
    fread(&numberOfFixedData, sizeof(int), 1, pToFile);

    // Ciclo que garante que os dados do tipo FIX_DATA são todos lidos
    while (control < numberOfFixedData)
    {
        // Limpa a string input
        input[0] = '\0';

        // Leitura do nome do país
        fread(country, sizeof(char), COUNTRYNAME, pToFile);
        strcat(input, country);

        // Leiura do codigo do pais
        fread(countrycode, sizeof(char), COUNTRYCODE, pToFile);
        strcat(input, ",");
        strcat(input, countrycode);

        // Leitura do continente
        fread(continent, sizeof(char), CONTINENT, pToFile);
        strcat(input, ",");
        strcat(input, continent);

        // Leitura da população correspondente ao país
        fread(&populacao, sizeof(int), 1, pToFile);
        sprintf(helper, "%d", populacao);
        strcat(input, ",");
        strcat(input, helper);

        // Leitura do semanas que o país tem
        fread(&numberOfVarData, sizeof(int), 1, pToFile);

        control_1 = 0;
        // Ciclo que garante que os dados do tipo VAR_DARA são todos lidos
        while (control_1 < numberOfVarData)
        {
            // CLimpa a string copy input
            copyInput[0] = '\0';
            strcpy(copyInput, input);

            // Leitura do indicador da semana
            fread(indicator, sizeof(char), INDICATOR, pToFile);
            strcat(copyInput, ",");
            strcat(copyInput, indicator);

            // leitura do numero de casos da semana
            fread(&cases, sizeof(int), 1, pToFile);
            sprintf(helper, "%d", cases);
            strcat(copyInput, ",");
            strcat(copyInput, helper);

            // letura do ano
            fread(&year, sizeof(int), 1, pToFile);
            sprintf(helper, "%d", year);
            strcat(copyInput, ",");
            strcat(copyInput, helper);

            // leitura do caracter '-' que está no meio da data
            fread(dummy, sizeof(char), 1, pToFile); // -

            // Leitura da semana
            fread(&week, sizeof(int), 1, pToFile);
            sprintf(helper, "%d", week);
            strcat(copyInput, "-");
            strcat(copyInput, helper);

            // leitura do racio das ultimas 2 semanas
            fread(&ratio, sizeof(double), 1, pToFile);
            sprintf(helper, "%lf", ratio);
            strcat(copyInput, ",");
            strcat(copyInput, helper);

            // Leitura dos casos totais do país
            fread(&casos_totais, sizeof(int), 1, pToFile);
            sprintf(helper, "%d", casos_totais);
            strcat(copyInput, ",");
            strcat(copyInput, helper);

            // Confirma se já existe algum país na lista
            if (startFixed == NULL)
            {
                // Adiciona uma estrutura à lista que vai ser lida
                startFixed = addNodeFixed(NULL, pToFile, start, copyInput, startFixed, 1, "");
                newestFixed = startFixed;
            }
            //Adiciona uma estrutura que não seja a primeira da lista
            else
            {
                helper2 = addNodeFixed(newestFixed, pToFile, start, copyInput, startFixed, 1, "");

                // Confirma se o pointer recebido é NULL ou não
                if (helper2 != NULL)
                {
                    // Adiciona liga a estrutura que foi adicionada às estruturas que já tinham sido inicializadas
                    newestFixed = helper2;
                }
            }
            control_1++;
        }
        control++;
    }
    // Fecho do ficheiro de leitura
    fclose(pToFile);

    // Retorno do pointeiro para a primeira posição da lista
    return startFixed;
}

// *************************************************************************************************************************************************************************
// Esta função faz a leitura de um ficheiro binário
// Input - char *name - nome do ficheiro de leitura de dados
// Input - char *continent - nome do continente que vai ser é para ser lido caso seja uma leitura parcial do ficheiro
// Input - int mode - modo de leitura do ficheiro 1 - total / 2 - parcial
// Output - startFixed - retorna apontador para a primeira posição da lista
// *************************************************************************************************************************************************************************

FIX_DATA *ReadInCSV(char *name, char *continent, int mode)
{
    // Declaração e inicialização das variaveis utilizadadas neste ficheiro
    FIX_DATA *startFixed = NULL; //cabeça de lista
    FIX_DATA *newestFixed = NULL;
    FIX_DATA *helper = NULL;
    int numberOfLines = 0;

    // Define 1 pointeiros para estruturas do tipo VAR_DATA
    VAR_DATA *start = NULL;
    // Declara a string input que vai receber os dados do ficheiro
    char input[MAX];

    //Cria um ponteiro para o ficheiro que vai ser aberto
    FILE *pToFile = fopen(name, "r+");

    //Confirma se o ponteiro foi bem criado
    if (pToFile != NULL)
    {
        //Garante que o ponteiro está a apontar para a primeira posição do ficheiro de texto
        rewind(pToFile);

        // Leitura de uma linha do ficheiro externo
        while (fgets(input, MAX, pToFile) != NULL)
        {
            if (numberOfLines >= 1)
            {
                //Adiciona uma estrutura no inicio da lista
                if (startFixed == NULL)
                {
                    startFixed = addNodeFixed(NULL, pToFile, start, input, startFixed, mode, continent);
                    newestFixed = startFixed;
                }
                //Adiciona uma estrutura que não seja a primeira da lista
                else
                {
                    helper = addNodeFixed(newestFixed, pToFile, start, input, startFixed, mode, continent);
                    // Confirma se o pointer recebido é NULL ou não
                    if (helper != NULL)
                    {
                        // Adiciona liga a estrutura que foi adicionada às estruturas que já tinham sido inicializadas
                        newestFixed = helper;
                    }
                }
            }
            numberOfLines++;
        }
        //Fecha o ficheiro que está a ser usado
        fclose(pToFile);
    }
    else
    // Não consegui gerar o ficheiro
    {
        printf("Error finding the project");
        Cleanup(startFixed);
        exit(-1);
    }

    // Retorna apontador para a primeira posição da lista
    return startFixed;
}
