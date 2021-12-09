#include "auxiliar.h"

// *************************************************************************************************************************************************************************
// Input - int selector - irá selecionar o tipo de string que vai ser comparada, pode tomar 3 valores, 1 -strings / 2 - inteiros / 3 - decimais
// Input - char token[] - a string que vai ser analisada
// Inpu - FIX_DATA *startFixed - apontador para o primerio elemento da lista do fitpo FIX_DATA
// Input - FILE *pToFile - apontador para o ficheiro com os dados
// Input - FIX_DATA *newst - apontador para a estrutura do tipo FIX_DATA que esta a ser preenchida agora mesmo
// Input - VAR_DATA *newstetVAR - quando diferente de NULL é um apontador para a estrutura do tipo VAR_DATA que está a ser preenchida agora mesmo,
//                              - quando igual a NULL => estamos a preencher uma estrutura do tipo var data
// Output - nenhum, função é do tipo void
// *************************************************************************************************************************************************************************

void confirmToken(int selector, char token[], FIX_DATA *startFixed, FILE *pToFile, FIX_DATA *newest, VAR_DATA *newestVar)
{
    int numberOfDecimalPoints = 0;
    switch (selector)
    {
    // Confimrma se a string enviada pode ser convertida para uma palavra (char[]) - ou seja - se apenas tem caracteres maisculos, minusculos, espaços e carecteres nulos
    case 1:
        // Percorre toda a string enviada
        for (int i = 0; i <= strlen(token); i++)
        {
            //  Confirma se existe algum caracter que seja ilicito na string
            if ((token[i] >= 65 && token[i] <= 90) || (token[i] >= 97 && token[i] <= 122) || token[i] == 32 || token[i] == 0)
            {
                // Vai comfirmar o próximo caracter
                continue;
            }

            // Havia um caracter ilicito, logo termina o programa e avisa o utilizador
            printf("-1 erro de leitura...\n");

            // Liberta toda a memória que foi alocada e fecha todos os ficheiros
            Cleanup(startFixed);
            fclose(pToFile);
            free(newest);

            if (newestVar != NULL)
            {
                free(newestVar);
            }

            exit(1);
        }
        break;

    // Confirma se a string enviada pode ser convertida para um numero inteiro (sem casas decimais) - ou seja - apenas tem numeros como caracteres
    case 2:
        // Precorre a string enviada
        for (int i = 0; i <= strlen(token); i++)
        {
            //  Confirma se existe algum caracter que seja ilicito na string
            if ((token[i] >= 48 && token[i] <= 57) || token[i] == 0 || token[i] == 45)
            {
                // Vai comfirmar o próximo caracter
                continue;
            }

            // Havia um caracter ilicito, logo termina o programa e avisa o utilizador
            printf("-1 erro de leitura...\n");

            // Liberta toda a memoria que foi alocada e fecha todos os ficheiros
            Cleanup(startFixed);
            fclose(pToFile);
            free(newest);
            if (newestVar != NULL)
            {
                free(newestVar);
            }
            exit(1);
        }
        break;

    // Confirma se a string enviada pode ser convertida para um numero com casas decimais (float ou double) - ou seja - apenas tem numeros ou
    case 3:
        // Precorre a string enviada
        for (int i = 0; i <= strlen(token); i++)
        {
            //  Confirma se existe algum caracter que seja ilicito na string
            if ((token[i] >= 48 && token[i] <= 57) || token[i] == 0 || (token[i] == 46 && numberOfDecimalPoints < 1))
            {
                // confirma quantos pontos existem no numero
                if (token[i] == 46)
                {
                    numberOfDecimalPoints++;
                }

                // Vai comfirmar o próximo caracter
                continue;
            }

            // Havia um caracter ilicito, logo termina o programa
            printf("-1 erro de leitura...\n");

            // Liberta toda a memória que foi alocada e fecha todos os ficheiros
            Cleanup(startFixed);
            fclose(pToFile);
            free(newest);
            if (newestVar != NULL)
            {
                free(newestVar);
            }
            exit(1);
        }
        break;
    }
}

// *************************************************************************************************************************************************************************
// Esta função irá Percorrer toda a lista de FIX_DATA e irá confirma se o país que está a tentar ser colocado na lista já existe ou se é um país novo, se existir retorna
// um apontador para o mesmo
// Input - FIX_DATA *start - Apontador para cabeça de lista dos FIX_DATA
// Input - FIX_DATA *objective - Apontador para a estrutura que foi gerada temporáriamente para guardar os dados do  páis
// Output - Existem e possibilidades de output:
//        - NULL - Ou seja nenhum país dos que já se encontravam na lista tem o mesmo código de país que o que está a ser introduzido
//        - after - Apontador para a estrutura FIX_DATA que tem os dados do país escolhido, ocorre quando na lista já existia um estrutura do tipo FIX_DATA com
//                        os valores esperados
// *************************************************************************************************************************************************************************

FIX_DATA *confirmCountry(FIX_DATA *start, FIX_DATA *objective)
{
    FIX_DATA *after = NULL;
    after = start;

    // Ciclo que irá Percorrer a listas do tipo FIX_DATA criadas até ao momento
    while (after != NULL)
    {
        // Verifica se alguma estrutura da lista já tem os valores que foram introduzidos agora
        if (strcmp(after->countryCode, objective->countryCode) == 0 && strcmp(after->countryName, objective->countryName) == 0)
        {
            // Retorna o ponteiro para o a estrutura
            return after;
        }

        // Atualiza o ponteiro after para continuar a procura
        after = after->next;
    }

    // Retorna NULL indicando que não existe outra estrutura igual
    return NULL;
}

// *************************************************************************************************************************************************************************
// Esta função dá o free de todos as listas cuja memória foi alocada dinamicamente
// Input - FIX_DATA *startFixed - apontador para o primeiro elemento das estruturas do tipo FIX_DATA
// Output - nada é retornado pela funçao (void)
// *************************************************************************************************************************************************************************

void Cleanup(FIX_DATA *startFixed)
{
    if (startFixed != NULL)
    { //Criação de 2 apontadores para estruturas do tipo FIX_DATA
        FIX_DATA *freeMeLatter = startFixed;
        FIX_DATA *holdMeLater = startFixed->next;
        if (startFixed->data != NULL)
        {
            //Criação de 2 apontadores para estruturas do tipo VAR_DATA
            VAR_DATA *freeMe = startFixed->data;
            VAR_DATA *holdMe = startFixed->data->next;

            //Ciclo que garante que nenhuma estrutura do tipo FIX_DATA fica por libertar
            while (freeMeLatter != NULL)
            {
                // Atualização do apontador freeMe visto estarmos num País novo
                freeMe = freeMeLatter->data;

                //Ciclo que garante que nenhuma estrutura do tipo VAR_DATA fica por libertar
                while (freeMe != NULL)
                {
                    //Salvaguarda do apontador para a proxima lista do tipo VAR_DATA
                    holdMe = freeMe->next;

                    //Free da lista do tipo VAR_DATA atual
                    free(freeMe);

                    //Atualização do apontador para a proxima posição da lista
                    freeMe = holdMe;
                }
                //Salvaguarda do apontador para a proxima lista do tipo FIX_DATA
                holdMeLater = freeMeLatter->next;

                //Free da lista do tipo FIX_DATA atual
                free(freeMeLatter);

                //Atualizaão do apontador para a proxima posição da lista
                freeMeLatter = holdMeLater;
            }
        }
    }
}

// *************************************************************************************************************************************************************************
// Esta função limpa um nó de uma lista de dados variável
// Input - VAR_DATA *start - apontador para a cabeça da lista desejada VAR_DATA
// Input - VAR_DATA *freeMe - apontador para o elemento das estruturas do tipo VAR_DATA a remover
// Output - A função retorna um apontador para o início da lista (cabeça)
// *************************************************************************************************************************************************************************

VAR_DATA *removeVarNode(VAR_DATA *varHead, VAR_DATA *freeMe)
{
    VAR_DATA *auxPtr;

    // Caso o elemento a remover seja a cabeça da lista
    if (varHead == freeMe)
    {
        varHead = varHead->next;
        free(freeMe);
    }
    // Caso em que não existe nada na lista
    else if (varHead == NULL)
    {
        return varHead;
    }
    else
    {
        //Este loop vai meter o auxPtr no nó imediatamente antes do ao nó a remover
        for (auxPtr = varHead; auxPtr->next != freeMe; auxPtr = auxPtr->next)
            ;

        // posicionar o aopontador para o próximo elemento do elemento anterior ao nó a remover, no próximo membro da lista
        auxPtr->next = freeMe->next;
        free(freeMe);
    }
    return varHead;
}

// *************************************************************************************************************************************************************************
// Esta função limpa uma lista toda do tipo VAR_DATA
// Input - VAR_DATA *head - primeiro elemento do tipo VAR_DATA da lista que vai ser removida
// Output - nenhum, função é do tipo void
// *************************************************************************************************************************************************************************

void removeVarDataList(VAR_DATA *head)
{
    // Declaração e inicialização das variaveis usadas na função
    VAR_DATA *freeMe, *holdMe;
    freeMe = head;
    holdMe = freeMe->next;

    // Ciclo que garante que se precorre a lista do tipo VAR_DATA toda
    while (freeMe != NULL)
    {
        //Salvaguarda do apontador para a proxima lista do tipo VAR_DATA
        holdMe = freeMe->next;

        //Free da lista do tipo VAR_DATA atual
        free(freeMe);

        //Atualização do apontador para a proxima posição da lista
        freeMe = holdMe;
    }
}

// *************************************************************************************************************************************************************************
// Esta função confirma que o input recebido pelo ficheiro é correto, ou seja, que não lhe faltam colunas
// Input - char *input - vector que vai guardar o input recebido do ficheiro
// Output - 1 - input está correto, ou seja, tem 8 colunas / 0 - input recebido tem mais do que 9 colunas
// *************************************************************************************************************************************************************************

int confirmInput(char *input)
{
    // Declaração e inicialização das variavies a utilizar nesta função
    int numberOfCommas = 0;

    // Ciclo que percorre o input completo
    for (int i = 0; i <= strlen(input); i++)
    {
        // Confirma se a letra atual é uma virgula e se for aumenta a contagem
        if (input[i] == 44)
        {
            numberOfCommas++;
        }
    }
    // Confirma se o numero de virgual é diferente do correto (8), se o for retorna 0
    if (numberOfCommas != 8)
    {
        return 0;
    }
    else
    {
        // Numero de virgulas foi o correto, logo retorna 1
        return 1;
    }
}
