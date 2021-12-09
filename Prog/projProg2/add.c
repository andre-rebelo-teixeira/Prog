#include "add.h"

// *************************************************************************************************************************************************************************
// Esta função cria mais uma estrutura do fitpo FIX_DATA
// Input - VAR_DATA *previous - Posição da estrutura do tipo VAR_DATA que se vai encontrar antes na lista
// input - FILE *pToFile - Apontador para o ficheiro e dados
// Input - VAR_DATA *start - Apontador para a a primeira cabeça de lista dos variaveis
// Input - char input[MAX] - valor que é lido em cada linha do documento externo
// Input - FIX_DATA *startFixed - Cabeça de lista dos do tipo FIX_DATA
// Input - int readingMode - modo de leitura do ficheiro, 1 => leitura global do ficheiro / 2 => leitura parcial do ficheiro com base no continente especificado
// Input - char continent[] - caso o modo de leitura seja o 2, será especificado aqui qual será o continente a ler, se modo de leitura = 1 => continent[] = '\0'
// Output - *newData - Apontador para o novo ultimo elemento da lista do tipo VAR_DATA
// *************************************************************************************************************************************************************************

FIX_DATA *addNodeFixed(FIX_DATA *previous, FILE *pToFile, VAR_DATA *start, char input[MAX], FIX_DATA *startFixed, int readingMode, char continent[])
{
    // Alocação dinamica do espaço que vai ser usado para colocar os dados lidos
    // A alocação dinamica realiza a inicialização de todos os valores a zero de modo a não haver lixo em memória
    // Fazendo com que o valgrind não apresente erros por saltos condicionais de variaveis não inicializadas
    FIX_DATA *newData = (FIX_DATA *)calloc(1, sizeof(FIX_DATA));

    // Confirma que o espaço foi alocado
    if (newData == NULL)
    {
        // Dá free de todo que já foi alocado até ao local
        Cleanup(startFixed);
        errno = ESRCH;
        // Indica que existiu um erro para o terminal
        perror("Failed to alocate the memory \n");
        // Sai do programa
        exit(EXIT_FAILURE);
    }
    // Declaração das variaveis que vão ser utilizadas
    FIX_DATA *aux = NULL;
    VAR_DATA *aux1 = NULL;
    int length;
    char copyInput[MAX];
    char *token;

    // Confirma que o input recebido tem o numero de colunas correto
    if (confirmInput(input) != 1)
    {
        printf("-1 erro de leitura...\n");
        Cleanup(startFixed);
        exit(1);
    }

    // Calcula o tamanho da string de input
    length = strlen(input);

    // Elimina o ultimo caracter quando este for um paragrafo da string input e coloca-o como sendo um caracter finalizado
    if (input[length] == '\n')
    {
        input[length - 1] = '\0';
    }
    else if (input[length - 2] == '\r' && input[length - 1] == '\n')
    {
        input[length - 2] = '\0';
        input[length - 1] = '\0';
    }

    // Copia do input lido no ficheiro para a string copyInput
    strcpy(copyInput, input);

    // Atravez do uso do strsep ignoramos as virgulas e colocamos os valores lidos dentro das variaveis de cada estrutura
    token = strsep(&input, ","); // Ignora a virgula

    // Confirma que o token recebido não tem caracteres ilicitos
    confirmToken(1, token, startFixed, pToFile, newData, NULL);

    strcpy(newData->countryName, token); // copia o nome do país lido para estrutura

    token = strsep(&input, ","); // Ignora a virgula

    // Confirma que o token recebido não tem caracteres ilicitos
    confirmToken(1, token, startFixed, pToFile, newData, NULL);

    strcpy(newData->countryCode, token); // copia o código do país lido para estrutura

    token = strsep(&input, ","); // Ignora a virgula

    // Confirma que o token recebido não tem caracteres ilicitos
    confirmToken(1, token, startFixed, pToFile, newData, NULL);

    strcpy(newData->continent, token); // copia o nome do continente lido para estrutura

    if (strcmp(token = strsep(&input, ","), "") == 0)
    {
        Cleanup(startFixed);
        exit(1);
    }
    else
    {
        // Confirma que o token recebido não tem caracteres ilicitos
        confirmToken(2, token, startFixed, pToFile, newData, NULL);
        sscanf(token, "%ld", &newData->population);
    }

    newData->population = atol(token); // converte para inteiro o valor da população que foi lido do ficheiro e coloca na estrutura

    // Confirma o modi de leitura geral
    switch (readingMode)
    {
    // Escolhe o modo de leitura 1 - leitura total do fiecheiro
    case 1:
        aux = confirmCountry(startFixed, newData);

        // Confirma se já existe algum pais com os mesmo dados (nome e código) já inseridos, se sim coloca os dados variaveis na lista do tipo VAR_DATA desse país
        if (aux != NULL)
        {
            // Coloca a 'cabeça' de lista do tipo VAR_DATA do país em questão no pais na variavel aux1
            aux1 = aux->data;

            // Anda até ao final da lista do tipo VAR_DATA do país em questão até ao final
            while (aux1->next != NULL)
            {
                aux1 = aux1->next;
            }

            // Adiciona um no do tipo variavel no final da lista do tipo VAR_DATA já existente
            aux1->next = addNodeVariable(aux1, copyInput, startFixed, pToFile, newData);

            // Dá o free do nó do tipo FIX_DATA que foi feito para colocar momentaneamente os dados do país que foram lidos
            free(newData);

            // Faz a linkagem das listas
            if (previous != NULL)
            {
                previous->next = NULL;
            }

            // Retorna NULL, indicado que nenhum país deve ser adicionado no final da lista do tipo FIX_DATA até ao momento
            return NULL;
        }
        //aux == NULL => Ainda nenhum país com aquelas condições
        else
        {
            // Chama a função que vai colocar o input variavel dentro das estruturas e ajusta o pointer
            newData->data = addNodeVariable(NULL, copyInput, startFixed, pToFile, newData);

            // Faz a linkagem das listas
            if (previous != NULL)
            {
                previous->next = newData;
            }
        }

        break;

    // Escolhe o modo de leitura parcial, com base no continente dado
    case 2:
        // Verifica se deve ler ou não a linha que acabou de receber com base nas restriçoes
        if (readerSelector(continent, newData) == NULL)
        {
            // Faz linkagem dos listas
            if (previous != NULL)
            {
                previous->next = NULL;
            }

            return NULL;
        }

        // Verifica se o pais está a aparecer pela primeira vez nos dados
        aux = confirmCountry(startFixed, newData);

        // Confirma se já existe algum pais com os mesmo dados (nome e código) já inseridos, se sim coloca os dados variaveis na lista do tipo VAR_DATA desse país
        if (aux != NULL)
        {
            // Coloca a 'cabeça' de lista do tipo VAR_DATA do país em questão no pais na variavel aux1
            aux1 = aux->data;

            // Anda até ao final da lista do tipo VAR_DATA do país em questão até ao final
            while (aux1->next != NULL)
            {
                aux1 = aux1->next;
            }
            //printf("%s \n%s \n", after->countryName, after->next->countryName);

            // Adiciona um no do tipo variavel no final da lista do tipo VAR_DATA já existente
            aux1->next = addNodeVariable(aux1, copyInput, startFixed, pToFile, newData);

            // Dá o free do nó do tipo FIX_DATA que foi feito para colocar momentaneamente os dados do país que foram lidos
            free(newData);

            // Faz a linkagem das listas
            if (previous != NULL)
            {
                previous->next = NULL;
            }

            // Retorna NULL, indicado que nenhum país deve ser adicionado no final da lista do tipo FIX_DATA até ao momento
            return NULL;
        }
        //aux == NULL => Ainda nenhum país com aquelas condições
        else
        {
            // Chama a função que vai colocar o input variavel dentro das estruturas e ajusta o pointer
            newData->data = addNodeVariable(NULL, copyInput, startFixed, pToFile, newData);

            // Faz a linkagem das listas
            if (previous != NULL)
            {
                previous->next = newData; //newestFixed -> next
            }
        }
        break;
    }

    // Return do pointer para o novo elemento da lista de estruturas
    return newData;
}

// *************************************************************************************************************************************************************************
// Esta função cria mais uma estrutura do fitpo VAR_DATA
// Input - VAR_DATA *previous - Posição da estrutura do tipo VAR_DATA que se vai encontrar antes na lista
// Input - char input[MAX] - Valor lidos pelo programa que estavam no documento externo
// Input - FIX_DATA *startFixed - Apontador para o primeiro elemento da lista do tipo FIX_DATA
// Input - FILE *pToFile - apontador para o ficherio de dados
// Input . FIX_DATA *newest - apontador para a estrutura do tipo FIX_DATA em que o nó do tipo VAR_DATA que está a ser preenchido vai ser colocado
// Output - *newData - Apontador para o novo ultimo elemento da lista do tipo VAR_DATA
// *************************************************************************************************************************************************************************

VAR_DATA *addNodeVariable(VAR_DATA *previous, char input[MAX], FIX_DATA *startFixed, FILE *pToFile, FIX_DATA *newest)
{
    // Alocação dinamica do espaço que vai ser usado para colocar os dados lidos
    // A alocação dinamica realiza a inicialização de todos os valores a zero de modo a não haver lixo em memória
    // Fazendo com que o valgrind não apresente erros por saltos condicionais de variaveis não inicializadas
    VAR_DATA *newData = (VAR_DATA *)calloc(1, sizeof(VAR_DATA));

    // Confirma que o espaço foi alocado
    if (newData == NULL)
    {
        // Dá free de todo que já foi alocado até ao local
        Cleanup(startFixed);
        errno = ESRCH;
        // Indica que existiu um erro para o terminal
        perror("Failed to alocate the memory \n");
        exit(EXIT_FAILURE);
    }

    //declaração das variaveis necessárias a esta função
    char *token;
    int size = strlen(input);

    // Elimina o ultimo caracter quando este for um paragrafo da string input e coloca-o como sendo um caracter finalizado
    if (input[size] == '\n')
    {
        input[size - 1] = '\0';
    }
    else if (input[size - 2] == '\r' && input[size - 1] == '\n')
    {
        input[size - 2] = '\0';
        input[size - 1] = '\0';
    }

    // Ignora os primeiros 4 dados, visto estes já estarm colocados numa estrutura FIX_DATA
    token = strsep(&input, ",");
    token = strsep(&input, ",");
    token = strsep(&input, ",");
    token = strsep(&input, ",");

    token = strsep(&input, ",");       // Ignora a virgula
    strcpy(newData->indicator, token); // Copia o indicador para o a estrutura

    // Confirma se existe valor para o weekly count
    if (strcmp(token = strsep(&input, ","), "") == 0)
    {
        Cleanup(startFixed);
        exit(1);
    }
    else
    {
        confirmToken(2, token, startFixed, pToFile, newest, newData); // Confirma presença de caracteres ilicitos no token
        sscanf(token, "%d", &newData->weeklyCount);                   // Copia valor lido para o weekly count
    }

    // Lê a data(ano e semana), e coloca os valorres na estrutura
    token = strsep(&input, ",");
    sscanf(token, "%d-%d", &newData->year, &newData->week);

    // Lê o racio das ultimas 2 semanas , e coloca o valor na estrutura, confirmando se está definico no documento ou não
    if (strcmp(token = strsep(&input, ","), "") == 0)
    {
        newData->rate2Weeks = 0;
    }
    else
    {
        // Confirma que o token não tem caracteres ilicitos
        confirmToken(3, token, startFixed, pToFile, newest, newData);
        sscanf(token, "%lf", &newData->rate2Weeks);
    }

    // Lê a conta total, e coloca o valor na estrutura, confirmando se está definico no documento ou não
    if (strcmp(token = strsep(&input, ","), "") == 0)
    {
        Cleanup(startFixed);
        exit(1);
    }
    else
    {
        // Confirma que o token não tem caracteres ilicitos
        confirmToken(2, token, startFixed, pToFile, newest, newData);
        sscanf(token, "%d", &newData->cumulativeCount);
    }

    // Coloca o pointer da nova estrutura gerada a apontar para o vazio
    newData->next = NULL;

    // Return do pointer para o novo elemento da lista de estruturas
    return newData;
}
