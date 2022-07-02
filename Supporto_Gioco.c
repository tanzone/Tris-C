#include <stdio.h>
#include <windows.h>

#include "Stampa_O.c"
#include "Stampa_X.c"
#include "StrutturePerProgetto.c"

#define grandezza (8)  //GGRANDEZZA DELLA CELLA DEL TRIS SI PUO DIMENSIONARE COME SI VUOLE
#define dim (90)      //DIMENSIONE STRUTTURA



/**
*VARIABILI IMPORTANTI NELLA STRUCT
**/
struct variabili
{

    int giocatore;
    int num_giocate;
    int selezione[dim];
    int riga_X, riga_O;
    int colon_X, colon_O;
    int diag_X, diag_O;
    int antidiag_X, antidiag_O;
    int vincita_X, vincita_O;

} var;



/**
*FUNZIONE PER IL COLORE DEI SIMBOLI   X - O
**/
void setcolor(unsigned short color)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon,color);
}

/**
*CURSORE VISIBILE-INVISIBILE
**/
void cursore( int visibilita, int grandezza_cursore)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = grandezza_cursore;
    info.bVisible = visibilita;
    SetConsoleCursorInfo(consoleHandle, &info);
}


/**
*GIOCO PRINCIPALE = )
**/
void gioco_principale(struct PLAYER _player12[2])
{
    char struttura[dim][dim] = {0};
    int partite;

    /*COSTRUISCO LA STRUTTURA----------------------------------------*/
    Iniazzializzazione(struttura);

    /*STAMPO STRUTTURA VUOTA-----------------------------------------*/
    StampaStruttura_Vuota(struttura,Graf1);

    /*AZZERAMENTO VARIUABILI DEL GIOCO VINCITA-----------------------*/
    _player12[0].RelativeWin=0;
    _player12[1].RelativeWin=0;
    _player12[0].AbsoluteWin=0;
    _player12[1].AbsoluteWin=0;

    /*NUMERO DI PARTITE DA GIOCARE-----------------------------*/
    for(partite=0; (partite < (_player12[0].VittorieDaRaggiungere*2+1))&& (_player12[0].AbsoluteWin!=1)&&(_player12[1].AbsoluteWin!=1); partite++)
    {

        Proseguimento(struttura,Graf1,_player12);

        Azzeramento(struttura);

        Iniazzializzazione(struttura);
    }
    /*PREMIO PER CHI VINCE PIU PARTITE---------------------------*/
    Premio(struttura,_player12);

//FINE

    fine();
}


/**
*INIZIALIZZAZIONE DELLA STRUTTURA E DEI NUMERI
**/
void Struttura_Tris(char struttura[dim][dim])
{

    int i, j;

    /*Inizializzo la tabella del tris--------------*/
    for(i = 0; i < grandezza*3; i++)
    {
        //Colonne
        for(j = grandezza; j <= grandezza*2; j = j*2)
            struttura[i][j] = 254;

        //Righe
        if(i == grandezza || i == grandezza*2)
        {
            for(j = 0; j < grandezza*3; j++)
                struttura[i][j] = 254;
        }
    }
}

void Struttura_Numeri(char struttura[dim][dim])
{

    int i, j;
    char k = '1';

    /*Metto i numeri nelle celle permanentemente--------------*/
    for(i = grandezza-1; i < grandezza*3; i = i+grandezza)
        for(j = grandezza-1; j < grandezza*3; j = j+grandezza)
            struttura[i][j] = k++;
}



/**
*INIZZIALIZZO LA STRUTTURA
**/
void Iniazzializzazione(char struttura[dim][dim])
{

    /*STRUTTURA------------------------------------------------------*/
    Struttura_Tris(struttura);

    /*NUMERI ALL'INTERNO DELLA STRUTTURA-----------------------------*/
    Struttura_Numeri(struttura);
}



/**
*STAMPA DELLA STRUTTURA VUOTA CON EFFETO DI DISCESA
**/
void StampaStruttura_Vuota(char struttura[dim][dim])
{

    int i, j;

    /*Cursore nullo */
    cursore(0,1);

    /*Ciclo che stampa riga per riga-----------------*/
    for(i=1; i<grandezza*3; i++)
    {
        putchar(10);
        printf("\t      ");
        Sleep(100);
        for(j=1; j< grandezza*3; j++)
        {
            putchar(32);
            setcolor(Graf1.BorderColor);
            printf("%c", struttura[i][j]);
        }
    }

    /*PRONTO a partire solo in questa funzione----------------------*/
    printf("\n\n\nQuando sei PRONTO premi un tasto. . .");
    getch();
}



/**
*STAMPO IL BLOCCO con COLORI NEI VARI CASI
**/
void StampaStruttura_Agg(char struttura[dim][dim])
{

    int i, j;

    /*Cursore nullo */
    cursore(0,1);
    system("cls");



    /*Inizio della stampa del tris anche quando ci sarà un aggiornamento-----*/
    for(i=1; i<grandezza*3; i++)
    {
        setcolor(15);
        putchar(10);
        printf("\t      ");
        for(j=1; j< grandezza*3; j++)
        {
            putchar(32);

            /*Se incontra il carattere del O lo coloro verde-------*/
            if(struttura[i][j] == ' ')
            {
                setcolor(Graf1.Player2Color*16+Graf1.Player2Color);
                printf("%c", struttura[i][j]);
            }
            /*Se incontra il carattere della X lo coloro rosso-------*/
            else if(struttura[i][j] == '-')
            {
                setcolor(Graf1.Player1Color*16+Graf1.Player1Color);
                printf("%c", struttura[i][j]);
            }
            /*Altrimenti normale e continua la stampa carattere per carattere*/
            else
            {
                //setcolor(15);
                setcolor(Graf1.BorderColor);
                printf("%c", struttura[i][j]);
                setcolor(15);
            }

        }
    }
    setcolor(15);
    /*Ritorno cursore */
    cursore(1,100);
}



/**
*INSERIMENTO CON CONTROLLI
**/
char Inserimento(char struttura[dim][dim],struct GraficaTris Graf1)
{

    char casella;
    int i;
    int cpu = 0; ///METTERE A 1 PER lA CPU per giocare contro il computer


    do
    {
        /*STAMPA STRUTTURA AGGIORNATA------------------------------------*/
        StampaStruttura_Agg(struttura);
        printf("\n\n\n");

        if(var.giocatore%2 == 0)
        {
            setcolor(Graf1.Player1Color);
            printf("Player 1 - Inserisci il NUMERO della casella: ");
            fflush(stdin);
            casella = getch();
        }
        else if(var.giocatore%2 == 1)
        {
            setcolor(Graf1.Player2Color);
            printf("Player 2 - Inserisci il NUMERO della casella: ");

            //Contro il computer
            if(cpu == 1)
                casella = rand() %9 +49;

            // 1 vs 1
            else
            {
                fflush(stdin);
                casella = getch();
            }
        }

        for(i = 0; i < 10; i++)
        {
            if( casella == var.selezione[i])
                casella = 'x';
        }

    }
    while(casella < '1' || casella > '9'  );  //ritorno se sbaglia l inserimento

    //Ritorno il valore della casella
    return casella;
}



/**
*NON SO IL TITOLO POTREBBE ESSERE PROSEGUIMENTO COMPLESSO
**/
void Proseguimento(char struttura[dim][dim],struct GraficaTris Graf1,struct PLAYER _player12[2])
{

    char casella;
    int count = 0;

    do
    {

        casella = Inserimento(struttura,Graf1);

        if(var.giocatore%2 == 0)
            /*STAMA DELLE X--------------------------------------------------*/
            StampaDelleX(struttura,casella);

        else if(var.giocatore%2 == 1)
            /*STAMA DELLE O--------------------------------------------------*/
            StampaDelleO(struttura,casella);


        /**GESTICO LE VARIABILI**/
        var.selezione[count++] = casella;
        var.num_giocate++;
        var.giocatore++;



        /*VINCITA-------------------------------------------------*/
        Vincite(struttura,_player12);


    }
    while(var.riga_X != 1 && var.riga_O != 1 && var.colon_X != 1 && var.colon_O != 1 && var.diag_X != 1 && var.diag_O != 1 && var.antidiag_X != 1 && var.antidiag_O != 1 && var.num_giocate != 9);
}



/**
*VARI CONTROLLI PER LA VITTORIA
**/
int Riga_X_Win(char struttura[dim][dim])
{
    if(
        struttura[grandezza-2][grandezza-2] == '-'   && struttura[grandezza-2][grandezza*2-2] == '-'   && struttura[grandezza-2][grandezza*3-2] == '-'      ||
        struttura[grandezza*2-2][grandezza-2] == '-' && struttura[grandezza*2-2][grandezza*2-2] == '-' && struttura[grandezza*2-2][grandezza*3-2] == '-'    ||
        struttura[grandezza*3-2][grandezza-2] == '-' && struttura[grandezza*3-2][grandezza*2-2] == '-' && struttura[grandezza*3-2][grandezza*3-2] == '-'
    )
        ///Imposto la vincita per la X in una delle condizioni delle colonne a 1
        return 1;
}

int Riga_O_Win(char struttura[dim][dim])
{

    if(
        struttura[grandezza-2][grandezza-2] == ' '   && struttura[grandezza-2][grandezza*2-2] == ' '   && struttura[grandezza-2][grandezza*3-2] == ' '      ||
        struttura[grandezza*2-2][grandezza-2] == ' ' && struttura[grandezza*2-2][grandezza*2-2] == ' ' && struttura[grandezza*2-2][grandezza*3-2] == ' '    ||
        struttura[grandezza*3-2][grandezza-2] == ' ' && struttura[grandezza*3-2][grandezza*2-2] == ' ' && struttura[grandezza*3-2][grandezza*3-2] == ' '
    )
        ///Imposto la vincita per la X in una delle condizioni delle colonne a 1
        return 1;
}



/**
*VARI CONTROLLI PER LA VITTORIA
**/
int Colon_X_Win(char struttura[dim][dim])
{

    if(
        struttura[grandezza-2][grandezza-2] == '-'   && struttura[grandezza*2-2][grandezza-2] == '-'   &&   struttura[grandezza*3-2][grandezza-2] == '-'  ||
        struttura[grandezza-2][grandezza*2-2] == '-' && struttura[grandezza*2-2][grandezza*2-2] == '-' && struttura[grandezza*3-2][grandezza*2-2] == '-'  ||
        struttura[grandezza-2][grandezza*3-2] == '-' && struttura[grandezza*2-2][grandezza*3-2] == '-' && struttura[grandezza*3-2][grandezza*3-2] == '-'
    )
        return 1;
}

int Colon_O_Win(char struttura[dim][dim])
{

    if(
        struttura[grandezza-2][grandezza-2] == ' '   && struttura[grandezza*2-2][grandezza-2] == ' '   &&   struttura[grandezza*3-2][grandezza-2] == ' '  ||
        struttura[grandezza-2][grandezza*2-2] == ' ' && struttura[grandezza*2-2][grandezza*2-2] == ' ' && struttura[grandezza*3-2][grandezza*2-2] == ' '  ||
        struttura[grandezza-2][grandezza*3-2] == ' ' && struttura[grandezza*2-2][grandezza*3-2] == ' ' && struttura[grandezza*3-2][grandezza*3-2] == ' '
    )
        return 1;
}



/**
*VARI CONTROLLI PER LA VITTORIA
**/
int Diag_X_Win(char struttura[dim][dim])
{

    if( struttura[grandezza-2][grandezza-2] == '-' && struttura[grandezza*2-2][grandezza*2-2] == '-' && struttura[grandezza*3-2][grandezza*3-2] == '-')
        return 1;
}

int Diag_O_Win(char struttura[dim][dim])
{

    if( struttura[grandezza-2][grandezza-2] == ' ' && struttura[grandezza*2-2][grandezza*2-2] == ' ' && struttura[grandezza*3-2][grandezza*3-2] == ' ')
        return 1;
}



/**
*VARI CONTROLLI PER LA VITTORIA
**/
int Antidiag_X_Win(char struttura[dim][dim])
{

    if( struttura[grandezza-2][grandezza*3-2] == '-' && struttura[grandezza*2-2][grandezza*2-2] == '-' && struttura[grandezza*3-2][grandezza-2] == '-')

        return 1;
}

int Antidiag_O_Win(char struttura[dim][dim])
{

    if( struttura[grandezza-2][grandezza*3-2] == ' ' && struttura[grandezza*2-2][grandezza*2-2] == ' ' && struttura[grandezza*3-2][grandezza-2] == ' ')

        return 1;
}



/**
*VARIE VINCITE CON STAMPA.....IN FUNZIONI.....PER PREMIO FINALE
**/
void Vincite(char struttura[dim][dim],struct PLAYER _player12[2] )
{
     char WinPlayer1[]="Hai vinto player 1 ";
     char WinPlayer2[]="Hai vinto player 2 ";

    StampaStruttura_Agg(struttura);

    //Controlli per il player 1

    if(var.riga_X = Riga_X_Win(struttura) == 1)
    {
        MessageBox(0, WinPlayer1, "VINCITA", 1);
        _player12[0].RelativeWin++;
    }

    else if(var.colon_X = Colon_X_Win(struttura) == 1)
    {
        MessageBox(0, WinPlayer1, "VINCITA", 1);
        _player12[0].RelativeWin++;
    }

    else if(var.diag_X = Diag_X_Win(struttura) == 1)
    {
        MessageBox(0, WinPlayer1, "VINCITA", 1);
        _player12[0].RelativeWin++;
    }

    else if(var.antidiag_X = Antidiag_X_Win(struttura) == 1)
    {
        MessageBox(0, WinPlayer1, "VINCITA", 1);
        _player12[0].RelativeWin++;
    }

    //Controlli per il player 2

    else if(var.riga_O = Riga_O_Win(struttura) == 1)
    {
        MessageBox(0, WinPlayer2, "VINCITA", 1);
        _player12[1].RelativeWin++;
    }

    else if(var.colon_O = Colon_O_Win(struttura) == 1)
    {
        MessageBox(0, WinPlayer2, "VINCITA", 1);
        _player12[1].RelativeWin++;
    }

    else if(var.diag_O = Diag_O_Win(struttura) == 1)
    {
        MessageBox(0, WinPlayer2, "VINCITA", 1);
        _player12[1].RelativeWin++;
    }

    else if(var.antidiag_O = Antidiag_O_Win(struttura) == 1)
    {
        MessageBox(0, WinPlayer2, "VINCITA", 1);
        //      var.vincita_O++;
        _player12[1].RelativeWin++;
    }
    else if(var.num_giocate == 9)
        MessageBox(0, "Pareggio", "VINCITA", 1);

    //Controllo del pareggio
    if(  _player12[0].RelativeWin== _player12[0].VittorieDaRaggiungere/2+1)
    {
        MessageBox(0, "Hai vinto tutto complimeti Player 1", "VINCITA", 1);
        _player12[0].AbsoluteWin++;
    }


    if(  _player12[1].RelativeWin== _player12[1].VittorieDaRaggiungere/2+1)
    {
        _player12[1].AbsoluteWin++;
        MessageBox(0, "Hai vinto tutto complimeti Player 2", "VINCITA", 1);
    }
}



/**
*AZZERAMENTO PER RICOMINCIRE IL ROUND
**/
void Azzeramento(char struttura[dim][dim])
{

    int i, j;

    var.num_giocate = 0;

    for(i=0; i < dim ; i++)
        var.selezione[i] = 0;

    for(i=0; i<dim; i++)
        for(j=0; j<dim; j++)
            struttura[i][j] = 0;
}



/**
*PREMIO
**/
void Premio(char struttura[dim][dim],struct PLAYER _player12[2])
{

    system("cls");
    Azzeramento(struttura);

    if(_player12[0].AbsoluteWin==1)
    {
        StampaX_Quarto(struttura);
        StampaStruttura_Agg(struttura);
        printf("\n\tCOMPLIMENTI HAI VINTOOOOOO");
    }

    else if(_player12[1].AbsoluteWin==1)
    {
        StampaO_Quarto(struttura);
        StampaStruttura_Agg(struttura);
        printf("\n\tCOMPLIMENTI HAI VINTOOOOOO");
    }
    else if(_player12[0].AbsoluteWin==0 && _player12[1].AbsoluteWin==1)
    {
        StampaX_Quarto(struttura);
        StampaO_Quinto(struttura);
        StampaStruttura_Agg(struttura);
        printf("\n\t\t     PAREGGIOOOOOO");
    }
}



/**
*FINE
**/
void fine()
{

    cursore(0,1);
    printf("\n\n\n");
    system("pause");
}





