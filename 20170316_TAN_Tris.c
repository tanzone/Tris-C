/**
*@Author Manuel Tanzi && Francesco Cavalieri
*@Date 16 Marzo 2017
*@Argument Progetto del tris
*
*/



#include <stdio.h>
#include <windows.h>

#include "FunzioniBase.c"
#include "StrutturePerProgetto.c"
#include "Supporto_Gioco.c"

/**
*Firma di funzioni nel main
**/
void Gioco() ;
void Compile_Settings();
void rules();


/**
*SCELTA del programma dal menu
**/
void SceltaProgramma()
{
    int scelta;
    struct Menu TypicalMenu;
        do
    {
        scelta=MenuInizialeO(TypicalMenu);

        switch(scelta)
        {
        case 0:
            break;
        case 1:
            Gioco();
            break;
        case 2:
            rules();
            break;
        case 3:
            Compile_Settings();  /// METTER A POSTO LA MATRICE
            break;
        case 4:
            break;
        }
    }
    while(scelta!=0);

}


/**
*MAIN PRINCIPALE
**/
int main()
{

    Graf1.BorderColor=15;
    Graf1.Player1Color=15;
    Graf1.Player2Color=15;

{
    INTRODUZIONE();
}

    SceltaProgramma();
    TITOLI_CODA();

    return 0;
}


///--------------------------MENU INIZIALE--------------///
int MenuInizialeO (struct Menu  _MenuIniziale)
{
    struct Menu _MenuColor;
    struct Titolo _Menu;

    char grigliaVuota[100][100]= {0};

    int i,j;
    int scelta;

    _MenuIniziale.dimX=40;
    _MenuIniziale.dimY=7;
    _MenuIniziale.paddingchar=32;
    _MenuIniziale.NumberOfElements=4;

    for(i=0 ; i<_MenuIniziale.dimY; i++)
        for(j=0 ; j< _MenuIniziale.dimX ; j++)
            _MenuIniziale.Spaziomenu[i][j]= _MenuIniziale.paddingchar;

    MatrixCat( _MenuIniziale.Spaziomenu, " Exit", 5, 0);
    MatrixCat(  _MenuIniziale.Spaziomenu, " Play", 5, 1);
    MatrixCat(  _MenuIniziale.Spaziomenu, " Rules", 5, 2);
    MatrixCat(  _MenuIniziale.Spaziomenu, " Settings", 5, 3);

    _MenuIniziale.Spaziomenu[2][2]='>';
    strcpy(_MenuIniziale.LabelOfMenu, "MENU SETTINGS");

    MatrixCat(_Menu.NomeTitolo,"              ___ __ __   ______   ___   __    __  __  ",0,0);
    MatrixCat(_Menu.NomeTitolo,"             /__//_//_/\\ /_____/\\ /__/\\ /__/\\ /_/\\/_/\\    ",0,1);
    MatrixCat(_Menu.NomeTitolo,"             \\::\\| \\| \\ \\\\::::_\\/_\\::\\_\\\\  \\ \\\\:\\ \\:\\ \\   ",0,2);
    MatrixCat(_Menu.NomeTitolo,"              \\:.      \\ \\\\:\\/___/\\\\:. `-\\  \\ \\\\:\\ \\:\\ \\  ",0,3);
    MatrixCat(_Menu.NomeTitolo,"               \\:.\\-/\\  \\ \\\\::___\\/_\\:. _    \\ \\\\:\\ \\:\\ \\ ",0,4);
    MatrixCat(_Menu.NomeTitolo,"                \\. \\  \\  \\ \\\\:\\____/\\\\. \\`-\\  \\ \\\\:\\_\\:\\ \\ ",0,5);
    MatrixCat(_Menu.NomeTitolo,"                 \\__\\/ \\__\\/ \\_____\\/ \\__\\/ \\__\\/ \\_____\\/ ",0,6);

    _Menu.NumRighe=7;

    scelta=MenuOrizzontale(  _MenuIniziale,0,_Menu,grigliaVuota );

    return scelta;
}

/**
*SCELTA NUMERO PARTITE
**/
int ModalitaGioco()
{
    char maticee[100][100];
    int count1=0,count2=0;

    for(count1=0; count1<100 ; count1++)
    {
        for(count2=0 ; count2<100; count2++)
            maticee[count1][count2]=' ';
    }

    MatrixCat(maticee,"Al meglio dei 3",1,0);
    MatrixCat(maticee,"Al meglio dei 5",1,1);
    MatrixCat(maticee,"Al meglio dei 7",1,2);

    for(count2=0 ; count2<100; count2++)
        maticee[count2][20]=0;

    maticee[2][0]='>';

    count1= MenuVerticale(maticee,"modalita gioco");

    if(count1==0)
        count1=3;

    if(count1==1)
        count1=5;

    if(count1==2)
        count1=7;

    return count1;
}

/**
*START DEL GIOCO
**/
void Gioco()  /// DA METTERE IN ORDINE
{
    struct PLAYER player12[2];

    player12[0].VittorieDaRaggiungere=ModalitaGioco();

    player12[1]=player12[0];

    gioco_principale(player12);
}

///----------------BLOCCO OPTIONS---------------///
int OptionsMenu()
{
    struct Menu _MenuOptions;
    struct Titolo _Options;

    int i,j;
    char scelta;
    int count=5;
    char grigliaVuota[100][100]= {0};

    _MenuOptions.dimX=40;
    _MenuOptions.paddingchar=32;
    _MenuOptions.NumberOfElements=4;

    for(i=0 ; i<_MenuOptions.NumberOfElements; i++)
        for(j=0 ; j<  _MenuOptions.dimX ; j++)
            _MenuOptions.Spaziomenu[i][j]= _MenuOptions.paddingchar;

    MatrixCat(  _MenuOptions.Spaziomenu, " Player1", 3, 0);
    MatrixCat(  _MenuOptions.Spaziomenu, " Border", 3, 1);
    MatrixCat(  _MenuOptions.Spaziomenu, " Player2", 3, 2);
    MatrixCat(  _MenuOptions.Spaziomenu, " Back", 3, 3);

    _MenuOptions.Spaziomenu[2][2]='>';
    strcpy(_MenuOptions.LabelOfMenu, "MENU SETTINGS");

    MatrixCat(_Options.NomeTitolo,"    ______   ______   _________  ________  ______   ___   __    ______ ",0,0);
    MatrixCat(_Options.NomeTitolo,"   /_____/\\ /_____/\\ /________/\\/_______/\\/_____/\\ /__/\\ /__/\\ /_____/\\ ",0,1);
    MatrixCat(_Options.NomeTitolo,"   \\:::_ \\ \\\\:::_ \\ \\\\__.::.__\\/\\__.::._\\/\\:::_ \\ \\\\::\\_\\\\  \\ \\\\::::_\\/_ ",0,2);
    MatrixCat(_Options.NomeTitolo,"    \\:\\ \\ \\ \\\\:(_) \\ \\  \\::\\ \\     \\::\\ \\  \\:\\ \\ \\ \\\\:. `-\\  \\ \\\\:\\/___/\\ ",0,3);
    MatrixCat(_Options.NomeTitolo,"     \\:\\ \\ \\ \\\\: ___\\/   \\::\\ \\    _\\::\\ \\__\\:\\ \\ \\ \\\\:. _    \\ \\\\_::._\\:\\",0,4);
    MatrixCat(_Options.NomeTitolo,"      \\:\\_\\ \\ \\\\ \\ \\      \\::\\ \\  /__\\::\\__/\\\\:\\_\\ \\ \\\\. \\`-\\  \\ \\ /____\\:\\",0,5);
    MatrixCat(_Options.NomeTitolo,"       \\_____\\/ \\_\\/       \\__\\/  \\________\\/ \\_____\\/ \\__\\/ \\__\\/ \\_____\\/",0,6);
    _Options.NumRighe=7;

    _MenuOptions.ColorAttuale=Graf1.BorderColor;

    system("cls");
    scelta=MenuOrizzontale(  _MenuOptions, 0,_Options,grigliaVuota);

    return scelta;
}

struct Menu  InizializzaPersonalizzazioneColori( struct Menu  _MenuBorder)
{
    int i,j;
    /*------BLOCCO DELLA----------*/
    {
        _MenuBorder.CharDaRisaltare=-2;
        _MenuBorder.dimX=7;
        _MenuBorder.paddingchar=32;
        _MenuBorder.NumberOfElements=6;

        for(i=0 ; i<_MenuBorder.NumberOfElements; i++)
            for(j=0 ; j< _MenuBorder.dimX ; j++)
                _MenuBorder.Spaziomenu[i][j]=_MenuBorder.paddingchar;

        for(i=1 ; i <_MenuBorder.NumberOfElements ; i++)
        {
            _MenuBorder.Spaziomenu[i][5] = -2;
            _MenuBorder.Spaziomenu[i][6] = 0;
        }
        MatrixCat( _MenuBorder.Spaziomenu, "Back", 5, 0 );
    }

    return _MenuBorder;
}

int BorderMenu()
{
    struct Menu _MenuOptions;
    struct Titolo _Options;

    int i,j;
    int _colore;
    int count=5;

    char griglia[100][100];  ///ANTEPRIMA GRIGLIA COLORATA

///------------CREO LA GRIGLIA CHE DEVE FARE DA ANTEPRIMA DEI BORDI--------//
    {
        for(i=0 ; i<100; i++)
        {
            for(j=0 ; j<100 ; j++)
                griglia[i][j]=32;
        }
        for(i=0; i<100; i++)
        {
            griglia[i][10]=-2;
            griglia[i][20]=-2;
        }

        for(i=0; i<100; i+=2)
        {
            griglia[5][i]=-2;
            griglia[10][i]=-2;
        }

        for(i=0; i<100; i++)
        {
            griglia[i][30]=0;
        }

    }
///-----------CREO IL MENU VERO E PROPRIO (CON LA LABEL)
    {
        _MenuOptions=InizializzaPersonalizzazioneColori(_MenuOptions);
        ///....CREO IL MENU....///
///....CREO LA LABEL DEL MENU ...///
        {
            MatrixCat(_Options.NomeTitolo,"\t        _______   ______   ______    ______    ________     ",0,0);
            MatrixCat(_Options.NomeTitolo,"\t      /_______/\\ /_____/\\ /_____/\\  /_____/\\  /_______/\\    ",0,1);
            MatrixCat(_Options.NomeTitolo,"\t      \\::: _  \\  \\:::_ \\ \\:::_ \\ \\ \\:::_ \\ \\ \\__.::._\\/    ",0,2);
            MatrixCat(_Options.NomeTitolo,"\t       \\::(_)  \\/_\\:\\ \\ \\ \\\\:(_) ) )_\\:\\ \\ \\ \\   \\::\\ \\     ",0,3);
            MatrixCat(_Options.NomeTitolo,"\t        \\::  _  \\ \\\\:\\ \\ \\ \\\\: __ `\\ \\\\:\\ \\ \\ \\  _\\::\\ \\__ ",0,4);
            MatrixCat(_Options.NomeTitolo,"\t         \\::(_)  \\ \\\\:\\_\\ \\ \\\\ \\ `\\ \\ \\\\:\\/.:| |/__\\::\\__/\\",0,5);
            MatrixCat(_Options.NomeTitolo,"\t          \\_______\\/ \\_____\\/ \\_\\/ \\_\\/ \\____/_/\\________\\/",0,6);
        }
    }
    _Options.NumRighe=7;

    hidecursor(0,5);
    system("cls");

    _MenuOptions.ColorAttuale=Graf1.BorderColor;
    _colore=MenuOrizzontale(_MenuOptions, 1,_Options,griglia);

    return _colore;
}

int Player1Menu()
{
    struct Menu _Player1Menu;
    struct Titolo _Player1;

    int i,j;
    int _colore;
    int count=5;

    char grigliaX[100][100];  ///ANTEPRIMA GRIGLIA COLORATA

    ///------------CREO LA GRIGLIA CHE DEVE FARE DA ANTEPRIMA DEI BORDI--------//
    {
        for(i=0 ; i<100; i++)
            for(j=0 ; j<100 ; j++)
                grigliaX[i][j]=32;

        for(i=3; i<6; i++)
            for(j=6 ; j<12 ; j+=2)
            {
                grigliaX[i][j]=-2;
                grigliaX[i][28-j]=-2;
                grigliaX[14-i][j]=-2;
                grigliaX[14-i][28-j]=-2;
            }

        for(i=6; i<9; i++)
            for(j=12 ; j<18; j+=2)
            {
                grigliaX[i][j]=-2;
            }

        for(i=0; i<100; i++)
            grigliaX[i][30]=0;

        for(i=0; i<100; i++)
            grigliaX[30][i]=0;
    }

    ///-----------CREO IL MENU VERO E PROPRIO (CON LA LABEL)
    {
        ///....CREO IL MENU....///
        {
            _Player1Menu=InizializzaPersonalizzazioneColori(_Player1Menu);
        }

        {
            for(i=0 ; i<100 ; i++)
                for(j=0 ; j<100 ; j++)
                    _Player1.NomeTitolo[i][j]=32;

            i=20 ;

            MatrixCat(_Player1.NomeTitolo," ____  _       ____  __ __    ___  ____  ",i,0);
            MatrixCat(_Player1.NomeTitolo,"|    \\| |     /    ||  |  |  /  _]|    \\ ",i,1);
            MatrixCat(_Player1.NomeTitolo,"|  o  ) |    |  o  ||  |  | /  [_ |  D  )",i,2);
            MatrixCat(_Player1.NomeTitolo,"|   _/| |___ |     ||  ~  ||    _]|    / ",i,3);
            MatrixCat(_Player1.NomeTitolo,"|  |  |     ||  _  ||___, ||   [_ |    \\",i,4);
            MatrixCat(_Player1.NomeTitolo,"|  |  |     ||  |  ||     ||     ||  .  \\",i,5);
            MatrixCat(_Player1.NomeTitolo,"|__|  |_____||__|__||____/ |_____||__|\\_|",i,6);
            _Player1.NumRighe=7;
        }
    }

    hidecursor(0,5);
    system("cls");

    _Player1Menu.ColorAttuale=Graf1.BorderColor;
    _colore=MenuOrizzontale(_Player1Menu, 1,_Player1,grigliaX);

    return _colore;
}

int Player2Menu() /// fare il cerchio
{
    struct Menu _Player2Menu;
    struct Titolo _Player2;

    int i,j;
    int _colore;
    int count=5;

    char grigliaX[100][100];  ///ANTEPRIMA GRIGLIA COLORATA

///------------CREO LA GRIGLIA CHE DEVE FARE DA ANTEPRIMA DEI BORDI--------//
    {
        for(i=0 ; i<100; i++)
            for(j=0 ; j<100 ; j++)
                grigliaX[i][j]=32;

        for(i=3; i<12; i++)
        {
            for(j=6 ; j<24; j+=2)
            {
                if( ( i>=5 &&i<=9)&&( j>=11 &&j<=16))
                    continue;

                grigliaX[i][j]=-2;
            }
        }

        for(i=0; i<100; i++)
            grigliaX[i][30]=0;
    }

///-----------CREO IL MENU VERO E PROPRIO (CON LA LABEL)
    {
        _Player2Menu=InizializzaPersonalizzazioneColori(_Player2Menu);


        ///....CREO LA LABEL DEL MENU .../// // (SCRIVERE : PLAYER1 )
        {
            for(i=0 ; i<100 ; i++)
                for(j=0 ; j<100 ; j++)
                    _Player2.NomeTitolo[i][j]=32;

            i=20 ;

            MatrixCat(_Player2.NomeTitolo," ____  _       ____  __ __    ___  ____  ",i,0);
            MatrixCat(_Player2.NomeTitolo,"|    \\| |     /    ||  |  |  /  _]|    \\ ",i,1);
            MatrixCat(_Player2.NomeTitolo,"|  o  ) |    |  o  ||  |  | /  [_ |  D  )",i,2);
            MatrixCat(_Player2.NomeTitolo,"|   _/| |___ |     ||  ~  ||    _]|    / ",i,3);
            MatrixCat(_Player2.NomeTitolo,"|  |  |     ||  _  ||___, ||   [_ |    \\",i,4);
            MatrixCat(_Player2.NomeTitolo,"|  |  |     ||  |  ||     ||     ||  .  \\",i,5);
            MatrixCat(_Player2.NomeTitolo,"|__|  |_____||__|__||____/ |_____||__|\\_|",i,6);
            _Player2.NumRighe=7;
        }
    }

    hidecursor(0,5);
    system("cls");

    _Player2Menu.ColorAttuale=Graf1.BorderColor;
    _colore=MenuOrizzontale(_Player2Menu, 1,_Player2,grigliaX);

    return _colore;
}

void Compile_Settings()
{
    int scelta;

    do
    {
        scelta=OptionsMenu();

        switch(scelta)
        {
        case 0:
            Graf1.Player1Color=Player1Menu();
            break;
        case 1:
            Graf1.BorderColor=BorderMenu();
            break;
        case 2:
            Graf1.Player2Color=Player2Menu();
            break;
        case 3:
            break;
        }
    }
    while(scelta!=3);
}


///---------------------------------------REGOLE--------------------------------/// (printf con set collore max 70 rg)

void rules() ///metteree i set color
{
    refreshing();
    system("cls");
    hidecursor(0,5);
    SetColor(14);
    center(30);
    printf("REGOLE\n\n");

    SetColor(2);
    printf("Le regole del gioco sono queste: \n> Inserire la posizione per stampare la X o la O nella tabella: \n\nIl gioco si aprira' con un menu\n\n");
    printf("> Per spostarsi nei menu usa le FRECCIETTE DIREZIONALI \nInizialmente verra' richiesto di inserire la modalita' di gioco,\nanche esso tramite menu\nLe possibili scelte saranno :\n\n");
    printf("> Al meglio dei 3 \n> Al meglio dei 5 \n> Al meglio dei 7\n");

    SetColor(13);
    printf("\n\nIl Gioco principale si aprira' cosi' :\n\n> Si aprira' un menu in cui ci si puo' spostare con le frecciette direzionali\ne opzioni da selezionare saranno \n");
    printf(">Play (Per giocare il gioco)\n>Settings (Per effettuare delle personalizzazioni )\n>Exit (Per Uscire.) \n");
    printf(">Settings (Per effettuare delle personalizzazioni relative )");

    SetColor(12);
    printf(" \n\n\nLe settings si apriranno  cosi' :\n\n> Si aprira' un menu in cui ci si puo' spostare con le FRECCIETTE DIREZIONALI \ne opzioni da selezionare saranno :\n");
    printf("> Border-color (Per Selezionare il colore del bordo)\n> Player (Per Selezionare il colore dei caratteri");

    SetColor(14);
    printf("\n\n\n\n\t\t   Premi un tasto per continuare");
    getch();
}

