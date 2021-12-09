#include "sort.h"

// *************************************************************************************************************************************************************************
// Esta função confirma a se as listas estão ordenadas de forma alfabetica ou não, e caso não esteja organiza as listas
// Input - FIX_DATA *start - apontador para o inicio das listas do tipo FIX_DATA
// Output - start - novo apontador para o inicio da lista do tipo FIX_DATA
// *************************************************************************************************************************************************************************

FIX_DATA *alphabeticalOrganizator(FIX_DATA *start)
{
    // Declaração das variaveis que vão ser necessárias ao longo da função
    FIX_DATA *startCopy = NULL;
    FIX_DATA *previous = NULL;
    FIX_DATA *after = NULL;
    FIX_DATA aux;

    // Inicialização das variaveis
    int flag = 1;
    startCopy = &aux;
    startCopy->next = start;

    // Confirmação de que a lista tem pelo menos 2 elementos para tentar realizar a organização da mesma
    if (startCopy != NULL && startCopy->next != NULL)
    {
        // Ciclo que mantem o ciclo a ser precorrido enquanto não existir uma passagem pela lista do tipo FIX_DATA que altere nenhuma list
        while (flag)
        {
            flag = 0; // Coloca a variavel que controla o ciclo a 0
            previous = startCopy;
            after = startCopy->next;

            // Apenas entra neste ciclo se existirem mais de duas listas por organizar
            while (after->next != NULL)
            {
                // Confirma a condição de os países estarem organizados por ordem alfabética
                if (strcmp(after->countryName, after->next->countryName) > 0)
                {
                    // Reorganiza os pointer com o uso da função troca
                    previous->next = troca(after, after->next);

                    // Como foi realizada uma alteração no codigo coloca a variavel que controla o ciclo while principal a 1
                    flag = 1;
                }
                // Faz o avanço para ler as proximas 2 listas
                previous = after;

                // Confirma se pode atualizar o pointer after para um valor que não seja NULL
                if (after->next != NULL)
                {
                    after = after->next;
                }
            }
        }
    }
    // Avança o apontador after para a proxima posição de modo a retornar o valor certo
    after = startCopy->next;

    // Encerra a função com o retorno de after
    return after;
}

// *************************************************************************************************************************************************************************
// Esta função troca os apontadores de modo a conseguirmos organizar as listas do tipo FIX_DATA
// Input - FIX_DATA *previous - apontador que guarda o valor da lista que estava um posição à frente na lista quando a função foi chamada
// Input - FIX_DATA *after - apontador que guarda o valor da lista que estava duas à frente na lista quando a função foi chamada
// Output - after - apontador para a estrutura que vai estar imeatamente à frente (depois da organização) da estrutura
//                  que nos encontravamos na lista quando a função foi chamada
// *************************************************************************************************************************************************************************

FIX_DATA *troca(FIX_DATA *previous, FIX_DATA *after)
{
    previous->next = after->next;
    after->next = previous;

    return after;
}

// *************************************************************************************************************************************************************************
// Esta função confirma a se as listas estão ordenada de forma populacional ou não, e caso não esteja organiza as listas
// Input - FIX_DATA *start - apontador para o inicio das listas do tipo FIX_DATA
// Input - int mode - escolhe o tipo de organização das listas crescente (2) ou decrescente (1)
// Output - start - novo apontador para o inicio da lista do tipo FIX_DATA
// *************************************************************************************************************************************************************************

FIX_DATA *populationOrganizator(FIX_DATA *start, int mode)
{
    // Declaração das variaveis que vão ser necessárias ao longo da função
    FIX_DATA *startCopy = NULL;
    FIX_DATA *previous = NULL;
    FIX_DATA *after = NULL;
    FIX_DATA aux;

    // Inicialização das variaveis
    int flag = 1;
    startCopy = &aux;
    startCopy->next = start;

    // Confirmação de que a lista tem pelo menos 2 elementos para tentar realizar a organização da mesma
    if (startCopy != NULL && startCopy->next != NULL)
    {
        switch (mode)
        {
        case 1:
            // Ciclo que mantem o ciclo a ser precorrido enquanto não existir uma passagem pela lista do tipo FIX_DATA que altere nenhuma list
            while (flag)
            {
                flag = 0; // Coloca a variavel que controla o ciclo a 0
                previous = startCopy;
                after = startCopy->next;

                // Apenas entra neste ciclo se existirem mais de duas listas por organizar
                while (after->next != NULL)
                {
                    // Confirma a condição de os países estarem organizados por ordem alfabética
                    if (after->population < after->next->population)
                    {
                        // Reorganiza os pointer com o uso da função troca
                        previous->next = troca(after, after->next);

                        // Como foi realizada uma alteração no codigo coloca a variavel que controla o ciclo while principal a 1
                        flag = 1;
                    }
                    // Faz o avanço para ler as proximas 2 listas
                    previous = after;

                    // Confirma se pode atualizar o pointer after para um valor que não seja NULL
                    if (after->next != NULL)
                    {
                        after = after->next;
                    }
                }
            }

            break;

        case 2:
            // Ciclo que mantem o ciclo a ser precorrido enquanto não existir uma passagem pela lista do tipo FIX_DATA que altere nenhuma list
            while (flag)
            {
                flag = 0; // Coloca a variavel que controla o ciclo a 0
                previous = startCopy;
                after = startCopy->next;

                // Apenas entra neste ciclo se existirem mais de duas listas por organizar
                while (after->next != NULL)
                {
                    // Confirma a condição de os países estarem organizados por ordem alfabética
                    if (after->population > after->next->population)
                    {
                        // Reorganiza os pointer com o uso da função troca
                        previous->next = troca(after, after->next);

                        // Como foi realizada uma alteração no codigo coloca a variavel que controla o ciclo while principal a 1
                        flag = 1;
                    }
                    // Faz o avanço para ler as proximas 2 listas
                    previous = after;

                    // Confirma se pode atualizar o pointer after para um valor que não seja NULL
                    if (after->next != NULL)
                    {
                        after = after->next;
                    }
                }
            }
            break;
        }
    }
    // Avança o apontador after para a proxima posição de modo a retornar o valor certo
    after = startCopy->next;

    // Encerra a função com o retorno de after
    return after;
}

// *************************************************************************************************************************************************************************
// Esta função irá realizar a organização das listas pelo máximo de casos ou mortes numa determinada semana
// Input - FIX_DATA *start - ponteiro para a estrutura do tipo FIX_DATA
// Input - int year - ano escolhido pelo utilizador
// Input - int week - semana escolhido pelo utilizador
// char *indicator - apontador para o sitio em memória em que está guardado o indicador escolhido pelo utilizador
// Output - after - apontador para a nova cabeça de lista
// *************************************************************************************************************************************************************************

FIX_DATA *casesOrganizator(FIX_DATA *start, int year, int week, char *indicator)
{
    // Declaração e inicialização das variaveis que vão ser necessárias ao longo da função
    FIX_DATA *startCopy = NULL;
    FIX_DATA *previous = NULL;
    FIX_DATA *after = NULL;
    FIX_DATA aux;
    VAR_DATA *auxiliar1 = NULL;
    VAR_DATA *auxiliar2 = NULL;
    int flag = 1;
    startCopy = &aux;
    startCopy->next = start;

    // Confirmação de que a lista tem pelo menos 2 elementos para tentar realizar a organização da mesma
    if (startCopy != NULL && startCopy->next != NULL)
    {
        // Ciclo que mantem o ciclo a ser precorrido enquanto não existir uma passagem pela lista do tipo FIX_DATA que altere nenhuma list
        while (flag)
        {
            flag = 0; // Coloca a variavel que controla o ciclo a 0
            previous = startCopy;
            after = startCopy->next;

            // Apenas entra neste ciclo se existirem mais de duas listas por organizar
            while (after->next != NULL)
            {
                // Confirma se existem valores pedidos para as semanas escolhidas para os proximos 2 paises
                auxiliar1 = confirmaDatas(year, week, indicator, after->data);
                auxiliar2 = confirmaDatas(year, week, indicator, after->next->data);

                // Confirma se ambos os paises não tem a asemana escolhida e faz a comparação alfabética
                if (auxiliar1 == NULL && auxiliar2 == NULL && strcmp(after->countryName, after->next->countryName) > 0)
                {
                    previous->next = troca(after, after->next);
                    flag = 1;
                }
                // Cofirma se o primeiro pais não tem valor, se o segundo tem e se o mesmo é diferente de zero
                else if (auxiliar1 == NULL && auxiliar2 != NULL && auxiliar2->weeklyCount != 0)
                {
                    previous->next = troca(after, after->next);
                    flag = 1;
                }
                // Confirma se o primeiro ão tem valor, se o so segundo tem e se o mesmo é igual a zero
                else if (auxiliar1 == NULL && auxiliar2 != NULL && auxiliar2->weeklyCount == 0)
                {
                    if (strcmp(after->countryName, after->next->countryName) > 0)
                    {
                        previous->next = troca(after, after->next);
                        flag = 1;
                    }
                }
                // Confirma se ambos os paises tem a semana indicada, e se o segundo pais tem menos numero de casos que o primeiro
                else if (auxiliar1 != NULL && auxiliar2 != NULL && auxiliar1->weeklyCount < auxiliar2->weeklyCount)
                {
                    previous->next = troca(after, after->next);
                    flag = 1;
                }
                // Confirma se ambos os paises tem a semana indicada, e se tem o memso numero de casos, fazendo assim a organização alfabética
                else if (auxiliar1 != NULL && auxiliar2 != NULL && auxiliar1->weeklyCount == auxiliar2->weeklyCount && strcmp(after->countryName, after->next->countryName) > 0)
                {
                    previous->next = troca(after, after->next);
                    flag = 1;
                }

                // Faz o avanço para ler as proximas 2 listas
                previous = after;

                // Confirma se pode atualizar o pointer after para um valor que não seja NULL
                if (after->next != NULL)
                {
                    after = after->next;
                }
            }
        }
    }

    // Avança o apontador after para a proxima posição de modo a retornar o valor certo
    after = startCopy->next;

    // Encerra a função com o retorno de after
    return after;
}

// *************************************************************************************************************************************************************************
// Esta função vai confirmar se para cada pais existe cados relativos à semana que foi escolhida com o indicador escolhido
// Input - int year - ano que foi especificado pelo utilizador
// Input - week - semana que foi especificada pelo utilizador
// char indicator - indicador escolhido pelo utilizador
// VAR_DATA *start - 'cabeça' de lista dos dados varaveis para um país
// Output - iter - o apontador para o valor em que estão guardados os dados da semana que foi indicada
//        - NULL - o país escolhido não tem valores para a semana que foi indicada
// *************************************************************************************************************************************************************************

VAR_DATA *confirmaDatas(int year, int week, char *indicator, VAR_DATA *start)
{
    VAR_DATA *iter;

    // Precorre toda a lista variavel para encontrar se tem a semana escolhida ou não
    for (iter = start; iter != NULL; iter = iter->next)
    {
        if (iter->week == week && iter->year == year && strcmp(indicator, iter->indicator) == 0)
        {
            return iter;
        }
    }
    return NULL;
}
