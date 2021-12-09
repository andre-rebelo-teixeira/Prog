#include "restrictions.h"

// *************************************************************************************************************************************************************************
// Esta função irá Percorrer toda a lista de FIX_DATA e irá remover os elementos que não cumpram a restrição de população
// Input - FIX_DATA startFixed - Apontador para cabeça de lista dos FIX_DATA
// Input - long populationRestriction - Limite mínimo ou máximo de população em milhares
// Input - int mode - 0 para filtrar segundo um mínimo de população e 1 para filtar segundo um máximo
// Output - retorna apontador para a nova caabeça de lista
// *************************************************************************************************************************************************************************

FIX_DATA *filterByPopulation(FIX_DATA *startFixed, long populationRestriction, int mode)
{
    FIX_DATA *iter = NULL;
    FIX_DATA *holdMe = NULL;

    // Multiplica por 1000 o numero recebido para estarmos em milhares
    populationRestriction *= 1000;

    // Compara qual o modo pedido
    switch (mode)
    {
    // Organiza segundo um minimo de população
    case 0:
        // Organiza todos os paises de forma decrescente de acordo com a população, para depois retirar os que não cumprem os minimo
        startFixed = populationOrganizator(startFixed, 1);

        // Percorre a lista dos paises já ordenados
        for (iter = startFixed; iter->next != NULL; iter = iter->next)
        {
            // Confirma se agum pais não cumpre o minimo de população
            if (iter->population >= populationRestriction)
            {
                holdMe = iter;
                continue;
            }
            break;
        }

        // Se algum o primeiro pais não cumprir minimo de população elimina os paises todos
        if (iter == startFixed)
        {
            Cleanup(startFixed);
            // Sai da função
            return NULL;
        }

        // Limpa todos os paises que não cumpram os minimos de população
        Cleanup(holdMe->next);

        // Acaba com a linkagem dos paises que já foram limpos
        holdMe->next = NULL;

        break;
    // Organiza segundo um maximo de população
    case 1:
        // Organiza todos os paises de forma crescente de acordo com a população, para depois retirar os que não cumprem o máximo
        startFixed = populationOrganizator(startFixed, 2);

        // Percorre a lista dos paises já ordenados
        for (iter = startFixed; iter->next != NULL; iter = iter->next)
        {
            // Confirma se algium pais não cumpre o máximo de população
            if (iter->population <= populationRestriction)
            {
                holdMe = iter;
                continue;
            }
            break;
        }

        // Se o primeiro pais não cumprir o máximo de população elimina todos os paises
        if (iter == startFixed)
        {
            Cleanup(startFixed);
            // Sai da função
            return NULL;
        }

        // Limpa todos os paises que não cumpram o máximo de população
        Cleanup(holdMe->next);

        // Acaba com a linkagem aos paises que já foram limpos
        holdMe->next = NULL;

        break;
    }

    // Retorna o novo cabeça de lista
    return startFixed;
}

// *************************************************************************************************************************************************************************
// Esta função irá Percorrer toda a lista de FIX_DATA e VAR_DATA e irá remover todos os elementos do tipo VAR_DATA que não cumpram os valores
// Input - FIX_DATA startFixed - Apontador para cabeça de lista dos FIX_DATA
// Input - int year1 - ano da primeira data de seleção colocada pelo utilizador
// Input - int year2 - ano da segunda data de selção colocada pelo utilizador
// Input - int week1 - semana da primeira data de seleção colocada pelo utilizador
// Input - int week2 - semana da segunda data de seleção colocada pelo utilizador
// Output - A função retorna um apontador para o início da lista (cabeça) agora filtrada
// *************************************************************************************************************************************************************************

FIX_DATA *filterByDates(FIX_DATA *startFixed, int year1, int year2, int week1, int week2)
{
    // declaração e inicialização de todas as variaveis usadas
    int aux;
    FIX_DATA *currentFixData;
    VAR_DATA *currentVarData;
    FIX_DATA *auxiliar2 = NULL;
    VAR_DATA *auxiliar = NULL;
    currentFixData = startFixed;
    currentVarData = currentFixData->data;

    // Confirma que as semanas estão dentro dos valores permitidos para um ano (1-53)
    if ((week1 > 53 || week1 < 0) || (week2 > 53 || week2 < 0))
    {
        errno = ESRCH;
        perror("One of your weeks is out of bounds");
        Cleanup(startFixed);
        exit(1);
    }

    // Organização da informação de maneira a que as var year/week 1 fiquem com a data mais antiga
    if (year2 < year1)
    {
        aux = year1;
        year1 = year2;
        year2 = aux;

        aux = week1;
        week1 = week2;
        week2 = aux;
    }
    else if (year2 == year1 && week2 < week1)
    {
        aux = week1;
        week1 = week2;
        week2 = aux;
    }

    //Ciclo que garante que todas as listas do tipo FIX_DATA são percorridas
    while (currentFixData != NULL)
    {
        auxiliar2 = currentFixData->next;
        // Atualizador do apontador CurrentVarDara visto estarmos num País novo
        currentVarData = currentFixData->data;
        //Ciclo que garante que todas as listas do tipo VAR_DATA que se encontram associadas a lista FIX_DATA atual são percorridas
        while (currentVarData != NULL)
        {
            auxiliar = currentVarData->next;

            // Confirma se a semana do pais está dentro das datas selecionadas
            if (confirmFirstData(currentVarData->year, currentVarData->week, year1, week1) == 0 || confirmFirstData(year2, week2, currentVarData->year, currentVarData->week) == 0)
            {
                // Caso semana não esteja dentro do valor correto elimina a semana
                currentFixData->data = removeVarNode(currentFixData->data, currentVarData);
            }
            //movimento do ponteiro da lista VAR_DATA
            currentVarData = auxiliar;
        }
        // Confirma se o país em questão tem alguma semana dentro dos parametros pedidos se não apaga o país
        if (currentFixData->data == NULL)
        {
            // Apaga o país que não tem semana
            startFixed = removeOneFixData(startFixed, currentFixData->countryName);
        }

        //movimento do ponteiro do tipo FIX_DATA
        currentFixData = auxiliar2;
    }

    // Colocação dos pointers no sitio esperado
    currentFixData = startFixed;
    currentVarData = currentFixData->data;

    // Retorno de um apontador para o primeiro elemento da lista
    return startFixed;
}

// *************************************************************************************************************************************************************************
// Remove uma estrutura do tipo FIX_DATA da lista
// Input - FIX_DATA *head - apontador para a primeira estrutura do tipo FIX_DATA
// Input - char *countryName - nome do pais que vai ser removido
// Output - head - Apontador para o primeira estrutura do tipo FIX_DATA
// *************************************************************************************************************************************************************************

FIX_DATA *removeOneFixData(FIX_DATA *head, char *countryName)
{
    // Declaração e inicialização de todas as variavies
    FIX_DATA *AuxH, *AuxT;
    AuxH = head;
    AuxT = head->next;

    // Compara se a primeira estrutura é para ser removida
    if (strcmp(AuxH->countryName, countryName) == 0)
    {
        head = head->next;
    }
    else
    {
        // Vai precorrendo a lista até encontrar a estrutura a remover
        while (strcmp(AuxT->countryName, countryName) != 0)
        {
            // Avanço dos apontadores
            AuxH = AuxT;
            AuxT = AuxT->next;
        }
        // Free dos pointer
        AuxH->next = AuxT->next;
        free(AuxT);
    }
    //
    return head;
}

// *************************************************************************************************************************************************************************
// Comprara duas datas indicando qual é a maior das duas e retorna um valor com base nisso
// Input - int year1 - Ano 1 da comparação
// Input - int week1 - semana 1 da comparação
// Input - int year2 - Ano 2 da comparação
// Input - int week2 - Ano 1 da comparação
// Output - int - 1 - segunda data é menor ou igual que a primeira / 0 - segunda data é maior que a primeira
// *************************************************************************************************************************************************************************

int confirmFirstData(int year1, int week1, int year2, int week2)
{
    // Confirma se o segundo ano é maior que o segundo
    if (year2 < year1)
    {
        return 1;
    }
    // Confirma se os 2 anos forem iguais se a segunda semana é menor
    else if (year2 == year1 && week2 < week1)
    {
        return 1;
    }
    // Confirma se a segunda data é igual à primeira
    else if (year2 == year1 && week2 == week1)
    {
        return 1;
    }
    return 0;
}
