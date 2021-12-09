#include "headers.h"

// *************************************************************************************************************************************************************************
// Declaração a função principal do código (Main)
// Input - int argc - inteiro que irá guardar o numero que argumentos que foram utilizados ao chamar o programa na linha de comandos
// Input - char *argv[] - array que irá guardar os argumentos que foram utilizados para chamar o programa na linha de comandos
// Output - return 0 - Função  retorna 0 indicando que o programa foi corrigo com sucesso, se o valor retornado não for zero ocorreu um erro algures na execução
// *************************************************************************************************************************************************************************

#define VECTOR 13

int main(int argc, char *argv[])
{
    // Declaração e inicialização das variavies que vão ser usadas ao longo da função
    FIX_DATA *startFixed = NULL;
    FIX_DATA *helper = NULL;                                               // Cabeça de lista geral do programa
    int vectorUserInput[VECTOR] = {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // Valores Padrão para a leitura de ficheiros;
    char nameInput[MAX] = "";
    char nameOutput[MAX] = "";
    char continent[CONTINENT];

    // Trata do user input colocado em terminal
    treatUserInput(argc, argv, vectorUserInput, nameInput, nameOutput, continent);

    // Confirma se vai ser feita uma leitura integral do programa ou se vai ser feita uma leitura parcial do ficheiro
    if (vectorUserInput[0] == 1)
    {
        // Confirma se a leitura vai ser feita de um ficheiro .csv
        if (vectorUserInput[4] == 1)
        {
            // Chama função que faz leitura total de um ficheiro .csv
            startFixed = ReadInCSV(nameInput, "", vectorUserInput[0]);
        }
        // Confirma se a leitura vai ser feita de um ficheiro .dat
        else if (vectorUserInput[4] == 2)
        {
            // Chama função que faz a leitura total de um ficheiro .dat
            startFixed = ReadInBynary(nameInput);

            // Vê qual o tipo de escrita que vai ser feita no programa .dat ou .csv
            // Desconcidera as opções -L/-S/-D/-P
            if (vectorUserInput[5] == 1)
            {
                // Faz print em .csv daquilo que foi lido do binário
                PrintList(startFixed, nameOutput);
                // Faz o free de todas as listas
                Cleanup(startFixed);
                // Termina o programa
                return 0;
            }
            else if (vectorUserInput[5] == 2)
            {
                // Faz print em .csv de tudo o que foi lido do binário
                PrintListInBynary(startFixed, nameOutput);
                // Faz free de todas as listas
                Cleanup(startFixed);
                // Termino do programa
                return 0;
            }
        }
    }
    // Entra no modo de leitura parcial do ficheiro
    else if (vectorUserInput[0] == 2)
    {
        // Faz leitura parcial de um ficheiro .csv com base no input do utilizador
        if (vectorUserInput[4] == 1)
        {
            startFixed = ReadInCSV(nameInput, continent, vectorUserInput[0]);
        }
        // Faz leitura total de um ficheiro .dat - Ocorre pois no eneunciado é dito para desconciderar qualquer opções de tratamento de dados
        else if (vectorUserInput[4] == 2)
        {
            // Chama a função que lê os .dat
            startFixed = ReadInBynary(nameInput);
            // Vê qual o tipo de escrita que vai ser feita no programa .dat ou .csv
            if (vectorUserInput[5] == 1)
            {
                // Fazprint em .csv de tudo o que foi lido do binário
                PrintList(startFixed, nameOutput);
                // Faz free de todas as listas
                Cleanup(startFixed);
                // Termino do programa
                return 0;
            }
            else if (vectorUserInput[5] == 2)
            {
                // Faz print em .dat de tudo aquilo que foi lido do binário
                PrintListInBynary(startFixed, nameOutput);
                // Faz free de todas as listas
                Cleanup(startFixed);
                // Termino do programa
                return 0;
            }
        }
    }
    // Verifica qual será o modo de seleção de dados

    switch (vectorUserInput[2])
    {
    // Caso 1 - semana com mais infetados para cada país
    case 1:
        // inicializa um apontador com o valor igual a startfixed (Para poedr ser alterado )
        helper = startFixed;
        // Anda por todos os paises da lista a escolher a semana com mais infetados
        while (helper != NULL)
        {
            // Chama a função que vai escolher o maior numero de casos para um país
            helper->data = moreCases(helper->data, helper, "cases", 1);
            // Avanço dos pointers
            helper = helper->next;
        }
        break;
    // Caso 2 - semana com mais mortos para cada país
    case 2:
        // inicializa um apontador com o valor igual a startfixed (Para poedr ser alterado )
        helper = startFixed;
        // Anda por todos os paises da lista a escolher a semana com mais infetados
        while (helper != NULL)
        {
            // Chama a função que vai escolher o maior numero de casos para um país
            helper->data = moreCases(helper->data, helper, "deaths", 1);
            // Avanço dos pointers
            helper = helper->next;
        }
        break;
    // Caso 3 - maior racio de infetados das ultimas 2 semanas para cada pais
    case 3:
        // inicializa um apontador com o valor igual a startfixed (Para poedr ser alterado )
        helper = startFixed;
        // Anda por todos os paises da lista a escolher a semana com mais infetados
        while (helper != NULL)
        {
            // Chama a função que vai escolher o maior numero de casos para um país
            helper->data = moreCases(helper->data, helper, "cases", 2);
            // Avanço dos pointers
            helper = helper->next;
        }
        break;
    // Caso 4 - maior racio de mortos das ultimas 2 semanas para cada país
    case 4:
        // inicializa um apontador com o valor igual a startfixed (Para poedr ser alterado )
        helper = startFixed;
        // Anda por todos os paises da lista a escolher a semana com mais infetados
        while (helper != NULL)
        {
            // Chama a função que vai escolher o maior numero de casos para um país
            helper->data = moreCases(helper->data, helper, "deaths", 2);
            // Avanço dos pointers
            helper = helper->next;
        }
        break;
    default:
        break;
    }

    // Verifica qual o modo de restrição
    switch (vectorUserInput[3])
    {
    // Caso 1 - população minima
    case 1:
        startFixed = filterByPopulation(startFixed, vectorUserInput[8], 0);
        break;
    // Caso 2 - população máxima
    case 2:
        startFixed = filterByPopulation(startFixed, vectorUserInput[8], 1);
        break;
    // Apenas dados relativos a 1 semana
    case 3:
        startFixed = filterByDates(startFixed, vectorUserInput[9], vectorUserInput[9], vectorUserInput[10], vectorUserInput[10]);
        break;
    // Apenas dados relativos a 1 intervalo de semanas
    case 4:
        startFixed = filterByDates(startFixed, vectorUserInput[9], vectorUserInput[11], vectorUserInput[10], vectorUserInput[12]);
        break;
    default:
        break;
    }

    // Verifica qual é o modo de ordenação dos dados
    switch (vectorUserInput[1])
    {
    // Ordem alfabética
    case 1:
        startFixed = alphabeticalOrganizator(startFixed);
        break;
    // Ordem decrescente de população
    case 2:
        startFixed = populationOrganizator(startFixed, 1);
        break;
    // Maior numero de casos numa determinada semana
    case 3:

        startFixed = casesOrganizator(startFixed, vectorUserInput[6], vectorUserInput[7], "cases");
        break;
    // Maior numero de mortos numa determinada semana
    case 4:
        startFixed = casesOrganizator(startFixed, vectorUserInput[6], vectorUserInput[7], "deaths");
        break;
    default:
        break;
    }
    // Quando leitura foi feita num .csv o print é  ultima coisa a ser feita
    if (vectorUserInput[5] == 1)
    {
        // Print em .csv dos dados que foram lidos e organizados
        PrintList(startFixed, nameOutput);
    }
    else if (vectorUserInput[5] == 2)
    {
        // Print em .dat dos dados que foram lidos e organizados
        PrintListInBynary(startFixed, nameOutput);
    }

    // Free de todas as listas que foram alocadas
    Cleanup(startFixed);

    // Termino do programa
    return 0;
}
