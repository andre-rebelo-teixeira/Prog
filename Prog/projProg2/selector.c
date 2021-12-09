#include "selector.h"

// *************************************************************************************************************************************************************************
// Função faz a seleção dos dados com base no input do utilizador
// Input - VAR_DATA *start - ponteiro para a estrutura do tipo VAR_DAR inicial
// Input - FIX_DATA *helper2 - Apontador para a estrutura do tipo FIX_DATA cujas as semanas são correspondentes
// Input - char *indicator - indicador do que é vai ser organizado ("cases" ou "deaths")
// Input - int selectorModo - escolho o tipo de organização 1 - casos/mortes semanais  2 - Racio (mortes ou caos)
// Output - Apontador para a semana com um valor maior com base no input escolhido
// *************************************************************************************************************************************************************************

VAR_DATA *moreCases(VAR_DATA *ListHead, FIX_DATA *helper2, char *indicator, int selectorMode)
{
    // Declaração e inicialização das variaveis que vão ser usadas ao longo da função
    VAR_DATA *left = NULL;
    VAR_DATA *right = NULL;
    VAR_DATA *head = NULL;
    VAR_DATA aux;
    int flag = 1;
    head = &aux;
    head->next = ListHead;

    // Confirma se a lista tem pelo menos 2 elementos, pois menos do que isso não compensa ser organizada
    if ((ListHead != NULL) && (ListHead->next != NULL))
    {
        // Mantem  função a realizar pelo menos uma troca por iteração
        while (flag)
        {
            flag = 0;
            left = head;
            right = head->next;

            // Seleciona o modo de organização, ou seja, se vai confirmar racios, ou se vai confirmar contagens semanais
            switch (selectorMode)
            {
            // Entra na organização de contagens semanais
            case 1:
                while (right->next != NULL)
                {
                    // Confirma se a estrutura a esquera que está ser comparada não o indicador corretor e se a estrutura à direita o tem indicador semanal correto, se sim realiza a troca
                    if (strcmp(right->indicator, indicator) != 0 && strcmp(right->next->indicator, indicator) == 0)
                    {
                        // Chama a função que troca a ordem das listas
                        left->next = trocaVAR(right, right->next);
                        // Coloca o flag a 1 para realizar mais uma vez o ciclo
                        flag = 1;
                    }
                    // Confirma se ambas as estruturas a ser organizadas tem o indicador correto, e a estrutura mais avançada tem mais casos semanais
                    else if (right->weeklyCount < right->next->weeklyCount && strcmp(right->indicator, indicator) == 0 && strcmp(right->next->indicator, indicator) == 0)
                    {
                        // Chama a função que troca a ordem das listas
                        left->next = trocaVAR(right, right->next);
                        // Coloca o flag a 1 para realizar mais uma vez o ciclo
                        flag = 1;
                    }
                    // Confirma se ambas as estruturas a ser organizadas tem o indicador correto, e se ambaas tem os mesmo casos semanais
                    else if (right->weeklyCount == right->next->weeklyCount && strcmp(right->indicator, indicator) == 0 && strcmp(right->next->indicator, indicator) == 0)
                    {
                        // Como ambas tem os mesmo casos semanais vai organizar de modo a que se escolha a semana mais recente
                        if (moreRecentData(right, right->next) == -1)
                        {
                            // Chama a função que troca a ordem das listas
                            left->next = trocaVAR(right, right->next);
                            // Coloca o flag a 1 para realizar mais uma vez o ciclo
                            flag = 1;
                        }
                    }

                    // avança o pointer left
                    left = right;

                    // Confirma se pode avançar o pointer right
                    if (right->next != NULL)
                    {
                        // Avança o pointer right
                        right = right->next;
                    }
                }
                break;

            case 2:
                // Entra na organização de contagens semanais
                while (right->next != NULL)
                {
                    // Confirma se a estrutura a esquera que está ser comparada não o indicador corretor e se a estrutura à direita o tem indicador semanal correto, se sim realiza a troca
                    if (strcmp(right->indicator, indicator) != 0 && strcmp(right->next->indicator, indicator) == 0)
                    {
                        // Chama a função que troca a ordem das listas
                        left->next = trocaVAR(right, right->next);
                        // Coloca o flag a 1 para realizar mais uma vez o ciclo
                        flag = 1;
                    }
                    // Confirma se ambas as estruturas a ser organizadas tem o indicador correto, e a estrutura mais avançada tem mais casos semanais
                    else if (right->rate2Weeks < right->next->rate2Weeks && strcmp(right->indicator, indicator) == 0 && strcmp(right->next->indicator, indicator) == 0)
                    {
                        // Chama a função que troca a ordem das listas
                        left->next = trocaVAR(right, right->next);
                        // Coloca o flag a 1 para realizar mais uma vez o ciclo
                        flag = 1;
                    }
                    // Confirma se ambas as estruturas a ser organizadas tem o indicador correto, e se ambaas tem os mesmo casos semanais
                    else if (right->rate2Weeks == right->next->rate2Weeks && strcmp(right->indicator, indicator) == 0 && strcmp(right->next->indicator, indicator) == 0)
                    {
                        // Como ambas tem os mesmo casos semanais vai organizar de modo a que se escolha a semana mais recente
                        if (moreRecentData(right, right->next) == -1)
                        {
                            // Chama a função que troca a ordem das listas
                            left->next = trocaVAR(right, right->next);
                            // Coloca o flag a 1 para realizar mais uma vez o ciclo
                            flag = 1;
                        }
                    }

                    // avança o pointer left
                    left = right;

                    // Confirma se pode avançar o pointer right
                    if (right->next != NULL)
                    {
                        // Avança o pointer right
                        right = right->next;
                    }
                }
                break;
            }
        }
    }

    // Coloca pointer right a apontar para a segunda estrutura
    right = head->next;

    // Atualiza o primeiro pointer do pais para as listas do tipo VAR_DATA
    helper2->data = right;

    // Compara se existe algum semana para o apis
    if (strcmp(helper2->data->indicator, indicator) == 0)
    {
        // Confirma se existe mais alguma semana na lista
        if (right->next != NULL)
        {
            // Chama a função que apaga o resto da lista
            removeVarDataList(helper2->data->next);

            // Atualiza o next do primeiro valor do tipo VAR_DATA para estar a NUÇÇ
            right->next = NULL;
        }
    }
    else
    {
        // Confirma se existe alguma semana na lista
        if (right != NULL)
        {
            // Apaga todas as semanas
            removeVarDataList(helper2->data);
        }
    }

    // Retorna apontador para a primeira posição do tipo VAR_DATA daquela país
    return right;
}

// *************************************************************************************************************************************************************************
// Esta função troca a posição de 2 variaveis numa lista
// Input - VAR_DATA *previous - Apontador para a estrutura que se encontra inicialmente antes na lista
// Input - VAR_DATA *after - Apontador para a estrutura que se encontra mais à frente na lista
// Output - iter2 - Apontador para a posição mais inicialmente na lista
// *************************************************************************************************************************************************************************

VAR_DATA *trocaVAR(VAR_DATA *previous, VAR_DATA *after)
{
    // Declaração e inicialização das variaveis que vão ser usadas nesta função
    VAR_DATA *iter = NULL;
    VAR_DATA *iter2 = NULL;
    iter = previous;
    iter2 = after;

    // troca dos pointer de posição
    iter->next = iter2->next;
    iter2->next = iter;
    return iter2;
}

// *************************************************************************************************************************************************************************
// Função calcula qual é a data mais recente ou mais antiga de modo a que quando houver um maior numero de casos a organização
// Input - VAR_DATA *first - Apontador para o primeiro elemento que quer ser utilizado para comparar datas
// Input - VAR_DATA *second - Apontador para o segundo elemento que quer ser utilizado para comparar datas
// Output - Função pode retornar 3 valores (1, 0, -1)
//              -1 - Segundo elemento é mais recente que o primeiro
//              0 - Elementos têm exatamente as mesmas datas e casos
//              1 - Primeiro elemento é mais recente que o segundo
// *************************************************************************************************************************************************************************

int moreRecentData(VAR_DATA *first, VAR_DATA *second)
{
    // Primeiro elemento enviado é mais recente que o segundo elemento
    if (first->year > second->year)
    {
        return 1;
    }
    // Anos dos 2 elementeos são iguais, semanas vão desempatar as qual o mais recente
    else if (first->year == second->year)
    {
        if (first->week > second->week)
        {
            // Primeiro elemento enviado é mais recente que o segundo elemento
            return 1;
        }
        else if (first->week == second->week)
        {
            // Elementos tem a mesma data, o programa não sabe o que fazer
            printf("datas são iguais, o programa não sabe como decidir, vaideixar como está");
            return 0;
        }
        else
        {
            // Segundo elemento enviado é mais recente que o primeiro
            return -1;
        }
    }

    // Segundo elementeo enviado é mais recente do que o primeiro elemento enviado
    return -1;
}
