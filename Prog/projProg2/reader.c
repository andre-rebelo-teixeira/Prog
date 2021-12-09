#include "reader.h"

// *************************************************************************************************************************************************************************
// Esta função realiza quando necessário a seleção dos dados que estão a ser lidos
// Input - char continent[] - string com que recebe o valor do continente que vai ser lido
// Input - FIX_DATA *newData - apontador para a estrutura que vai ser testada na seleção de dados no momento
// Output - newData - Caso seja o continente seja o selecionado devolve o valor do apontador que recebeu (ou seja != NULL)
//        - NULL - Caso seja um país com o continente que não seja o o que foi selecionado retorna NULL
// *************************************************************************************************************************************************************************

FIX_DATA *readerSelector(char continent[], FIX_DATA *newData)
{
    // Confirma que o ponteiro recebido é diferente de NULL
    if (newData != NULL)
    {
        // Faz a comparação do continente do país com o continente selecionado e dá errado
        if (strcmp(continent, newData->continent) != 0)
        {
            // Liberta o valor libertado para colocar o newData pois não necessita de alocar espaço para o país
            free(newData);
            return NULL;
        }
    }
    // Retorna algo diferente de NULL
    return newData;
}
