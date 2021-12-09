#include "userInput.h"

//analisa o input que o utilizador coloca na linha de comandos ao iniciar o programa
void treatUserInput(int argc, char *argv[], int *array, char *nameInput, char *nameOutput, char *continent)
{
    int size;
    //ciclo que faz analisar todos os argumentos colocados excepto o primeiro (pois é './wargame')
    for (int i = 1; i < argc; i++)
    {
        //analisa se o primeiro caracter de cada string é '-'
        if (argv[i][0] == '-')
        {
            switch (argv[i][1]) // Analisa o segundo caracter de cada input
            {

            case 'L':                                // Modo de leitura
                if (strcmp(argv[i + 1], "all") == 0) // Modo de leitura total escolhido
                {
                    *(array) = 1; // Coloca o valor 0 do array do user input a 1 (valor 0 vê o modo de leitura)
                }
                else // Modo de leitura parcial escolhido
                {
                    *(array) = 2;                   // Coloca o valor 0 do array do user input a 2 (valor 0 vê o modo de leitura)
                    strcpy(continent, argv[i + 1]); // Copia para continent o nome do continent que vai ser lido
                }
                break;

            case 'S':                                 // Modo de ordenação dos dados
                if (strcmp(argv[i + 1], "alfa") == 0) // Ordenação alfabética
                {
                    *(array + 1) = 1; // Coloca o valor 1 do array do user input a 1 (valor 1 vê o modo de ordenação)
                }
                else if (strcmp(argv[i + 1], "pop") == 0) // Ordenação dos dados por ordem decrescente da população
                {
                    *(array + 1) = 2; // Coloca o valor 1 do array do user input a 2 (valor 1 vê o modo de ordenação)
                }
                else if (strcmp(argv[i + 1], "inf") == 0) // Modo de ordenação crescente do numero mortos numa semana
                {
                    *(array + 1) = 3;                                           // Coloca o valor 1 do array do user input a 3 (valor 1 vê o modo de ordenação)
                    sscanf(argv[i + 2], "%d-%d", &*(array + 6), &*(array + 7)); // Coloca nos valores 6 e 7 a semana e o ano selecionado
                }
                else if (strcmp(argv[i + 1], "dea") == 0) // Modo de ordenação crescente do numero de mortos numa semana
                {
                    *(array + 1) = 4;                                           // Coloca o valor 1 do array do user input a 1 (valor 1 vê o modo de ordenação)
                    sscanf(argv[i + 2], "%d-%d", &*(array + 6), &*(array + 7)); // Coloca nos valores 6 e 7 a semana e o ano selecionado
                }
                else
                {
                    // O comando que foi colocado não existe
                    errno = ESRCH;
                    perror("The argument you input for the -S restricion is not valid, try 'alfa' or 'pop' or 'inf' or 'dea', Since input is not valid we will exit the program \n");
                    exit(EXIT_FAILURE);
                }
                break;

            case 'D':                                // Modo de seleção de dados
                if (strcmp(argv[i + 1], "inf") == 0) // Apenas semana com mais infetados para cada pais
                {
                    *(array + 2) = 1; // Coloca o valor 2 do array do user input a 1 (valor 2 vê modo de seleção)
                }
                else if (strcmp(argv[i + 1], "dea") == 0) // Apenas semana com mais mortos para cada país
                {
                    *(array + 2) = 2; // Coloca o valor 2 do array do user input a 2 (valor 2 vê o modo de seleção)
                }
                else if (strcmp(argv[i + 1], "racioinf") == 0) // Apenas semana com maior maior racio de infetados para cada país
                {
                    *(array + 2) = 3; // Coloca o valor 2 do array do user input a 3 (valor 2 vê o modo de seleção)
                }
                else if (strcmp(argv[i + 1], "raciodea") == 0) // Apenas semana com maior numero de racio de mortos para cada pais
                {
                    *(array + 2) = 4; // Coloca o valor 2 do array do user input a 4 (valor 2 vê o modo de seleção)
                }
                else
                {
                    // O comando que foi colocado não existe
                    errno = ESRCH;
                    perror("The argument you input for the -D restricion is not valid, try 'inf' or 'dea' or 'racioinf' or 'raciodea', Since input is not valid we will exit the program \n");
                    exit(EXIT_FAILURE);
                }
                break;

            case 'P':                                // Modo de Restrição de dados
                if (strcmp(argv[i + 1], "min") == 0) // Apenas paises com mais de n mil habitante
                {
                    *(array + 3) = 1;                         // Coloca o valor 3 do vetor user input a 1 (valor 3 vê modo de restrição)
                    sscanf(argv[i + 2], "%d", &*(array + 8)); // Recebe o valor de n milhares
                }
                else if (strcmp(argv[i + 1], "max") == 0) // Apenas paises com menos de n mil habitante
                {
                    *(array + 3) = 2;                         // Coloca o valor 3 do vetor user input a 1 (valor 3 vê modo de restrição)
                    sscanf(argv[i + 2], "%d", &*(array + 8)); // Rebele o valor de n milhares
                }
                else if (strcmp(argv[i + 1], "date") == 0) // Apenas dados para uma semana especifica
                {
                    *(array + 3) = 3;                                            // Coloca o valor 3 do vetor user input a 1 (valor 3 vê modo de restrição)
                    sscanf(argv[i + 2], "%d-%d", &*(array + 9), &*(array + 10)); // Recebe a data da semana indicada
                }
                else if (strcmp(argv[i + 1], "dates") == 0) // Apenas dados para um conjunto de semanas
                {
                    *(array + 3) = 4;                                             // Coloca o valor 3 do vetor user input a 1 (valor 3 vê modo de restrição)
                    sscanf(argv[i + 2], "%d-%d", &*(array + 9), &*(array + 10));  // Recebe a data da primeira semana indicada
                    sscanf(argv[i + 3], "%d-%d", &*(array + 11), &*(array + 12)); // Recebe a data da segunda semana indicada
                }
                else
                {
                    // Comando não existe
                    errno = ESRCH;
                    perror("The argument you input for the -P restricion is not valid, try 'min' or 'max' or 'date' or 'dea', Since input is not valid we will exit the program \n");
                    exit(EXIT_FAILURE);
                }
                break;

            case 'i':
                size = strlen(argv[i + 1]); // Calcula o tamanho total do nome do ficheiro de input

                if (argv[i + 1][size - 4] == 46 && argv[i + 1][size - 3] == 100 && argv[i + 1][size - 2] == 97 && argv[i + 1][size - 1] == 116) // Ficheiro de entrada é um .dat
                {
                    *(array + 4) = 2;               // Coloca valor 4 do vetor user input a 2 para indicar que vai ler de um binário
                    strcpy(nameInput, argv[i + 1]); // Copia o nome do ficheiro de input
                }
                else if (argv[i + 1][size - 4] == 46 && argv[i + 1][size - 3] == 99 && argv[i + 1][size - 2] == 115 && argv[i + 1][size - 1] == 118) // Ficheiro de entrada é um .csv
                {
                    *(array + 4) = 1;               // Coloca o valor 4 do vetor user input a 1 para indicar que vai ler de um comma separated value
                    strcpy(nameInput, argv[i + 1]); // Copia o nome do ficheiro de input
                }
                else
                {
                    // Extenção de ficheiro não é reconhecida
                    errno = ESRCH;
                    perror("The extension you tried to put is not suported, try .dat or .csv, Since input is not valid we will exit the program \n");
                    exit(EXIT_FAILURE);
                }
                break;

            case 'o':
                size = strlen(argv[i + 1]);

                if (argv[i + 1][size - 4] == 46 && argv[i + 1][size - 3] == 100 && argv[i + 1][size - 2] == 97 && argv[i + 1][size - 1] == 116) // Ficheiro de saida é um .dat
                {
                    *(array + 5) = 2;                // Coloca o valor 5 do vetor user input a 1 para indicar que vai escrever para um binário
                    strcpy(nameOutput, argv[i + 1]); // Copia o nome do ficheiro de output
                }
                else if (argv[i + 1][size - 4] == 46 && argv[i + 1][size - 3] == 99 && argv[i + 1][size - 2] == 115 && argv[i + 1][size - 1] == 118) // Ficheiro de saida é um .csv
                {

                    *(array + 5) = 1;                // Coloca o valor 5 do vetor user input a 1 para indicar que vai escrever para um comma separated value
                    strcpy(nameOutput, argv[i + 1]); // Copia o nome do ficheiro de outpur
                }
                else
                {
                    // Extenção de ficheiro não é reconhecida
                    errno = ESRCH;
                    perror("The extension you tried to put is not suported, try .dat or .csv, Since input is not valid we will exit the program \n");
                    exit(EXIT_FAILURE);
                }
                break;
            }
        }
    }
}
