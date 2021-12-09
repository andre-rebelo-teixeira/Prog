#include"Conversor.h"

//Retorna uma variante de peça aleatoria sabendo o tipo da peça
int RetornaVarianteAleatoria(int identificador_peca)
{
    int variante_peca = 0;
    switch (identificador_peca)
    {
    case  1:
        variante_peca = rand() % 9;
        break;

    case  2:
        variante_peca = rand() % 12;
        break;

    case  3:
        variante_peca = rand() % 6;
        break;

    case  4:
        variante_peca = rand() % 4;
        break;

    case  5:
        variante_peca = rand() % 4;
        break;

    case  6:
        variante_peca = rand() % 4;
        break;

    case  7:
        variante_peca = rand() % 2;
        break;

    case  8:
        variante_peca = 0;
        break;
    }

    return Conversor(identificador_peca, variante_peca + 1);
}

//Converte o identificador de peça e de variante para o identificador global da mesma
int Conversor(int identificador_peca, int identificador_variante)
{
    int identificador_global = 0;
    switch (identificador_peca)
    {
        case 1:
            if (identificador_variante == 1) {identificador_global = 1;}
            else if (identificador_variante == 2) {identificador_global = 2;}
            else if (identificador_variante == 3) {identificador_global = 3;}
            else if (identificador_variante == 4) {identificador_global = 4;}
            else if (identificador_variante == 5) {identificador_global = 5;}
            else if (identificador_variante == 6) {identificador_global = 6;}
            else if (identificador_variante == 7) {identificador_global = 7;}
            else if (identificador_variante == 8) {identificador_global = 8;}
            else if (identificador_variante == 9) {identificador_global = 9;}
            else{return -1;};
            break;

        case 2:
            if(identificador_variante == 1) {identificador_global = 10;}
            else if(identificador_variante == 2) {identificador_global = 11;}
            else if(identificador_variante == 3) {identificador_global = 12;}
            else if(identificador_variante == 4) {identificador_global = 13;}
            else if(identificador_variante == 5) {identificador_global = 14;}
            else if(identificador_variante == 6) {identificador_global = 15;}
            else if(identificador_variante == 7) {identificador_global = 16;}
            else if(identificador_variante == 8) {identificador_global = 17;}
            else if(identificador_variante == 9) {identificador_global = 18;}
            else if(identificador_variante == 10) {identificador_global = 19;}
            else if(identificador_variante == 11) {identificador_global = 20;}
            else if(identificador_variante == 12) {identificador_global = 21;}
            else{return -1;};
            break;

        case 3:
            if(identificador_variante==1){identificador_global=22;}
            else if(identificador_variante == 2) {identificador_global = 23;}
            else if(identificador_variante == 3) {identificador_global = 24;}
            else if(identificador_variante == 4) {identificador_global = 25;}
            else if(identificador_variante == 5) {identificador_global = 26;}
            else if(identificador_variante == 6) {identificador_global = 27;}
            else{return -1;};
            break;

        case 4:
            if(identificador_variante == 1) {identificador_global = 28;}
            else if(identificador_variante == 2) {identificador_global = 29;}
            else if(identificador_variante == 3) {identificador_global = 30;}
            else if(identificador_variante == 4) {identificador_global = 31;}
            else{return -1;};
            break;

        case 5:
            if(identificador_variante == 1) {identificador_global = 32;}
            else if(identificador_variante == 2) {identificador_global = 33;}
            else if(identificador_variante == 3) {identificador_global = 34;}
            else if(identificador_variante == 4) {identificador_global = 35;}
            else{return -1;};
            break;

        case 6:
            if(identificador_variante == 1) {identificador_global = 36;}
            else if(identificador_variante == 2) {identificador_global = 37;}
            else if(identificador_variante == 3) {identificador_global = 38;}
            else if(identificador_variante == 4) {identificador_global = 39;}
            else{return -1;};
            break;

        case 7:
            if(identificador_variante == 1) {identificador_global = 40;}
            else if(identificador_variante == 2) {identificador_global = 41;}
            else{return -1;};
            break;

        case 8:
            if(identificador_variante == 1){identificador_global = 42;}
            else{return -1;};
            break;
    }
    return identificador_global;
}

//Converte o identificador global no identificador do tipo de peça
int Conversor2(int identificador_global)
{
    int identificador_de_peca = 0;

    if (identificador_global > 0 && identificador_global < 10)
    {
        identificador_de_peca = 1;
    }
    else if (identificador_global > 9 && identificador_global < 22)
    {
        identificador_de_peca = 2;
    }
    else if (identificador_global > 21 && identificador_global < 28)
    {
        identificador_de_peca = 3;
    }
    else if (identificador_global > 27 && identificador_global < 32)
    {
        identificador_de_peca = 4;
    }
    else if (identificador_global > 31 && identificador_global < 36)
    {
        identificador_de_peca = 5;
    }
    else if (identificador_global > 35 && identificador_global < 40)
    {
        identificador_de_peca = 6;
    }
    else if (identificador_global > 40 && identificador_global < 42)
    {
        identificador_de_peca = 7;
    }
    else if (identificador_global == 42)
    {
        identificador_de_peca = 8;
    };
    return identificador_de_peca;
}
    