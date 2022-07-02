
#include <stdio.h>
#include <windows.h>
#include "StrutturePerProgetto.c"

#ifndef FunzioniBase_c

void SetColor(short Color)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE); // oppure system("COLOR E9");
    SetConsoleTextAttribute(hCon,Color);
}

void hidecursor( int visibility, int cursor_size)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = cursor_size;
    info.bVisible = visibility;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void SetPosition(int X, int Y)
{
    HANDLE Screen;
    Screen = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position= {X, Y};

    SetConsoleCursorPosition(Screen, Position);
}

void MyExit()
{
    fflush(stdin);
    hidecursor( 0, 5);
    printf("\n\n\n\t\t\tPremere un tasto per continuare");
    getch();
    hidecursor( 1, 5);
}

void refreshing() ///cambia nome
{
    char screenspace[100][100];

    int i, j;
    int extrem=0;

    hidecursor(0, 1);
    for(i=0 ; i<100 ; i++)
        for(j=0 ; j<100 ; j++)
            screenspace[i][j]=254;

    SetPosition(0, 0);

    {
        for(i=0 ; i<60 ; i++)
        {
            for(j=0 ; j< 39 ; j++)
            {
                SetColor(7);
                if(j%2==0)
                    SetColor(5);
                putchar(screenspace[i][j]);
                putchar(32);
            }

            putchar(10);
            Sleep(15);
        }

        hidecursor(1, 5);
        SetColor(15);
    }

    system("cls");
}
/**
* ------------------------------------------------- NON C'ENTRANO NULLA MA SERVONO -------------------
*/
void center( int space)
{
    int _center;

    for(_center=0; _center<space; _center++)
        putchar(32);
}

void INTRODUZIONE() ///main
{
    hidecursor(0, 5);
    center(25);
    printf("Progetto assegnato il 14 / 02 / 2017\n\n");
    center(35);
    printf("Progetto Tris\n\n");
    center(38);
    printf("Scritto da :\n\n");
    center(25);
    printf("Cavalieri Francesco && Manuel Tanzi\n\n");
    center(33);
    printf("All right reserved\n\n\n");
    center(33);
    putchar(10);
    center(27);
    printf("Premi un tasto per continuare ...");

    Sleep(500);
    fflush(stdin);
    getch();
    fflush(stdin);
}

/// SPAZIO DA LASCIARE (INUTILE... ) MA CARUCCIO
void invii(int Ninvii)
{
    int i;
    for(i=0 ; i<Ninvii; i++)
        putchar(10);
}

void TITOLI_CODA() ///main
{
    refreshing();
    system("CLS");
    invii(7);
    center(40);
    printf("Grazie per aver giocato con noi \n\n\n");
    center(50);
    printf("A presto");
    invii(7);
}

/**
*-------------------------------------------Funzioni  Matrici---------------------------------------
*/

void MatrixCat( char matriceDaCaricare[100][100],const char stringa[], int X, int Y)
{
    int i,j;
    for(j=0 ; j<strlen(stringa) ; j++, X++)
        matriceDaCaricare[Y][X]=stringa[j];

    matriceDaCaricare[Y][X]=0;


}

int MenuOrizzontale(struct Menu MenuOrizzontale, int funz, struct Titolo _Titolo, char _griglia[100][100])
{
    char griglia[100][100];

    char scelta;
    int contatore=2;
    int contatore2=0;
    int i,j;
    int colore=10;

    refreshing();
    hidecursor(0,5);

    do
    {

        MenuOrizzontale.Spaziomenu[contatore][2]='>';
        system("cls");

        ///-------------------------------STAMPA MENU LABEL----------------------///
        {
            for(contatore2=0 ; contatore2<_Titolo.NumRighe; contatore2++)
            {
                SetColor(14);
                printf(_Titolo.NomeTitolo[contatore2]);
                putchar(10);
                SetColor(15);
            }
            printf("\n\n\t\t\t\t\tMENU");

            putchar(10);
            putchar(10);
            putchar(10);
            putchar(10);

        }
///-----------------STAMPA DELLE VOCI DEL MENU-------------------------///
        {
            for(i=0 ; i<MenuOrizzontale.NumberOfElements ; i++)
            {
                putchar(32);
                putchar(32);
                putchar(32);

                for(contatore2=0 ; contatore2<strlen(MenuOrizzontale.Spaziomenu[i]); contatore2++)
                {
                    if(funz==1)
                    {
                        if( (MenuOrizzontale.Spaziomenu[i][contatore2]==MenuOrizzontale.CharDaRisaltare))
                            SetColor(i+8);

                        else
                            SetColor(15);
                    }
                    else
                    {
                        if(MenuOrizzontale.Spaziomenu[i][2]=='>')
                        {
                            SetColor(14);
                        }

                        else
                            SetColor(12);
                    }


                    printf("%c",MenuOrizzontale.Spaziomenu[i][contatore2]);
                }


                putchar(32);
                putchar(32);
                putchar(32);
                SetColor(15);
            }
        }

        putchar(10);

///.....STAMPA DELL'ANTEPRIMA SE LA FUNZIONE VALE 1...//
        {
            if(funz==1)
                for(i=0 ; i<15 ; i++)
                {
                    putchar(10);
                    center(20);

                    if(contatore!=0)
                        SetColor(contatore+8);

                    else
                        SetColor(MenuOrizzontale.ColorAttuale);

                    printf(_griglia[i]);
                }
        }

        SetPosition(0,0);

        scelta=getch();

        if(scelta==-32)  ///....CASO CHE ELABORA IL MOVIMENTO...///
        {
            scelta=getch();

            switch(scelta)
            {
            case 77:
                MenuOrizzontale.Spaziomenu[contatore][2]=' ';
                contatore=(contatore!=MenuOrizzontale.NumberOfElements-1)? contatore+1:0;
                break;
            case 75:
                MenuOrizzontale.Spaziomenu[contatore][2]=' ';
                contatore=(contatore!=0)? contatore-1:MenuOrizzontale.NumberOfElements-1;
                break;
            }
        }

        if(scelta=='\r' && funz==1 && contatore!=0)
        {
            colore=contatore+8;
            scelta='A';
            MenuOrizzontale.ColorAttuale=contatore;
        }

    }
    while(scelta!='\r');

    if(funz==1)
        contatore=colore;


    return contatore;
}

int MenuVerticale(char matrice[100][100],char mod[])
{
    char griglia[100][100];

    char scelta;
    int contatore=2;
    int contatore2=0;
    int i,j;

    int colore=10;

    hidecursor(0,5);
    do
    {
        matrice[contatore][0]='>';
        system("cls");

        ///-------------------------------STAMPA MENU LABEL----------------------///
        setcolor(14);
        printf("\n\n\t\t\t\t\%s",mod);

        putchar(10);
        putchar(10);
        putchar(10);
        putchar(10);
///-----------------STAMPA DELLE VOCI DEL MENU-------------------------///
        {
            for(i=0 ; i<3 ; i++)
            {

                if(matrice[i][0]=='>')
                    center(8);
                center(35);
                for(contatore2=0 ; contatore2<strlen(matrice[i]); contatore2++)
                {
                    SetColor(12);

                    if(matrice[i][0]=='>')
                        SetColor(14);

                    if(matrice[i][contatore2]=='>')
                    {
                        putchar(32);
                        continue;
                    }

                    printf("%c",matrice[i][contatore2]);
                }
                putchar(10);
                putchar(10);
                putchar(10);
                SetColor(15);
            }
        }
        putchar(10);

///.....STAMPA DELL'ANTEPRIMA SE LA FUNZIONE VALE 1...//
        SetPosition(0,0);
        scelta=getch();
        if(scelta==-32)  ///....CASO CHE ELABORA IL MOVIMENTO...///
        {
            scelta=getch();

            switch(scelta)
            {
            case 80 :
                matrice[contatore][0]=' ';
                contatore=(contatore!=3-1)? contatore+1:0;
                break;
            case 72:
                matrice[contatore][0]=' ';
                contatore=(contatore!=0)? contatore-1:3-1;
                break;
            }
        }

    }
    while(scelta!='\r');
    return contatore;
}
#endif
