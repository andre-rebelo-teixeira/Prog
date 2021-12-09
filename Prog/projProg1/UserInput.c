#include"UserInput.h"

//analisa o input que o utilizador coloca na linha de comandos ao iniciar o programa
void UserInput(int argc, char *argv[], int * array )
{
    //declaração das variaveis que vão ser usadas ao longo do programa
    int numero_da_peca;

    //ciclo que faz analisar todos os argumentos colocados excepto o primeiro (pois é './wargame')
    for(int i = 1; i < argc; i++)
    {
        //analisa se o primeiro caracter de cada string é '-'
        if (argv[i][0] == '-')
        {
            //caso seja analisa  o próximo caracter da string 
            switch (argv[i][1])
            { 
            case 'h': //Indica que quer iniciar mensagem de ajuda
                mensagemAjuda();
                exit(0);
                break;

            case 't': // Quer configurar o tamanho do tabuleiro 
                sscanf(argv[i+1], "%dx%d", &*(array), &*(array+1)); //análize das dimeções do tabuleiro dadas pelo utilizador 
                if (((*(array) % 3)!=0 || (*(array+1) % 3) != 0) || ((*(array)) < 9 && *(array) > 15 && *(array+1) < 9 && *(array+1) > 24))
                {
                    mensagemAjuda();
                    exit(1);
                }
                break;
            
            case 'j': // Quer configurar o modo de jogo que vai ser jogado
                sscanf(argv[i+1],"%d", &*(array+2));
                if(*(array+2) < -1 || *(array+2) > 2)
                {
                    mensagemAjuda();
                    exit(1);
                }
                break;
                
            case 'd': // Quer configurar o modo 
                sscanf(argv[i+1], "%d", &*(array+4));
                if(*(array+4) < 0 || *(array+4) > 3)
                {
                    mensagemAjuda();
                    exit(1);
                }
                break;

            case 'p':
                sscanf(argv[i+1], "%d", &*(array+3));
                if(*(array+3) < 1 || *(array+3) > 2)
                {
                    printf("coco");
                    mensagemAjuda();
                    exit(1);
                }
                break;

            case '1': case'2' : case '3': case '4': case'5': case'6': case '7': case '8':
                numero_da_peca = (argv[i][1])-'0';
                *(array+4+numero_da_peca)=strtol(argv[i+1], NULL, 10);
                break;
            }
        }
    }
}