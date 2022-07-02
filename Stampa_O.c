#include <stdio.h>

#define grandezza (8)//GGRANDEZZA DELLA CELLA DEL TRIS SI PUO DIMENSIONARE COME SI VUOLE
#define dim (90)


void StampaDelleO(char struttura[dim][dim], int casella){

    /*FIGURE A'INTERNO DEI RIQUADRI COI CERCHI-----------------------*/

    switch(casella){

    case '1':StampaO_Primo(struttura);    break;

    case '2':StampaO_Secondo(struttura);  break;

    case '3':StampaO_Terzo(struttura);    break;

    case '4':StampaO_Quarto(struttura);   break;

    case '5':StampaO_Quinto(struttura);   break;

    case '6':StampaO_Sesto(struttura);    break;

    case '7':StampaO_Settimo(struttura);  break;

    case '8':StampaO_Ottavo(struttura);   break;

    case '9':StampaO_Nono(struttura);     break;

    }


}


void StampaO_Primo(char struttura[dim][dim]){

    int i, j;

    ///primo riquadro
    for(i=2, j=2; i < grandezza-1; i++)
        struttura[i][j] = ' ';
    for(i=2, j=2; j < grandezza-1; j++)
        struttura[i][j] = ' ';
    for(i=2, j=grandezza-2; i < grandezza-1; i++)
        struttura[i][j] = ' ';
    for(i=grandezza-2, j=2; j < grandezza-1; j++)
        struttura[i][j] = ' ';
}

void StampaO_Secondo(char struttura[dim][dim]){

    int i, j;

    ///secondo riquadro
    for(i=2, j=grandezza+2; i < grandezza-1; i++)
        struttura[i][j] = ' ';
    for(i=2, j=grandezza+2; j < grandezza*2-1; j++)
        struttura[i][j] = ' ';
    for(i=2, j=grandezza*2-2; i < grandezza-1; i++)
        struttura[i][j] = ' ';
    for(i=grandezza-2, j=grandezza+2; j < grandezza*2-1; j++)
        struttura[i][j] = ' ';
}

void StampaO_Terzo(char struttura[dim][dim]){

    int i, j;

    ///terzo riquadro
    for(i=2, j=grandezza*2+2; i < grandezza-1; i++)
        struttura[i][j] = ' ';
    for(i=2, j=grandezza*2+2; j < grandezza*3-1; j++)
        struttura[i][j] = ' ';
    for(i=2, j=grandezza*3-2; i < grandezza-1; i++)
        struttura[i][j] = ' ';
    for(i=grandezza-2, j=grandezza*2+2; j < grandezza*3-1; j++)
        struttura[i][j] = ' ';
}

void StampaO_Quarto(char struttura[dim][dim]){

    int i, j;

    ///quarto riquadro
    for(i=grandezza+2, j=2; i < grandezza*2-1; i++)
        struttura[i][j] = ' ';
    for(i=grandezza+2, j=2; j < grandezza-1; j++)
        struttura[i][j] = ' ';
    for(i=grandezza+2, j=grandezza-2; i < grandezza*2-1; i++)
        struttura[i][j] = ' ';
    for(i=grandezza*2-2, j=2; j < grandezza-1; j++)
        struttura[i][j] = ' ';
}

void StampaO_Quinto(char struttura[dim][dim]){

    int i, j;

    ///quinto riquadro
    for(i=grandezza+2, j=grandezza+2; i < grandezza*2-1; i++)
        struttura[i][j] = ' ';
    for(i=grandezza+2, j=grandezza+2; j < grandezza*2-1; j++)
        struttura[i][j] = ' ';
    for(i=grandezza+2, j=grandezza*2-2; i < grandezza*2-1; i++)
        struttura[i][j] = ' ';
    for(i=grandezza*2-2, j=grandezza+2; j < grandezza*2-1; j++)
        struttura[i][j] = ' ';
}

void StampaO_Sesto(char struttura[dim][dim]){

    int i, j;

    ///sesto riquadro
    for(i=grandezza+2, j=grandezza*2+2; i < grandezza*2-1; i++)
        struttura[i][j] = ' ';
    for(i=grandezza+2, j=grandezza*2+2; j < grandezza*3-1; j++)
        struttura[i][j] = ' ';
    for(i=grandezza+2, j=grandezza*3-2; i < grandezza*2-1; i++)
        struttura[i][j] = ' ';
    for(i=grandezza*2-2, j=grandezza*2+2; j < grandezza*3-1; j++)
        struttura[i][j] = ' ';
}

void StampaO_Settimo(char struttura[dim][dim]){

    int i, j;

    ///settimo riquadro
    for(i=grandezza*2+2, j=2; i < grandezza*3-1; i++)
        struttura[i][j] = ' ';
    for(i=grandezza*2+2, j=2; j < grandezza-1; j++)
        struttura[i][j] = ' ';
    for(i=grandezza*2+2, j=grandezza-2; i < grandezza*3-1; i++)
        struttura[i][j] = ' ';
    for(i=grandezza*3-2, j=2; j < grandezza-1; j++)
        struttura[i][j] = ' ';
}

void StampaO_Ottavo(char struttura[dim][dim]){

    int i, j;

    ///ottavo riquadro
    for(i=grandezza*2+2, j=grandezza+2; i < grandezza*3-1; i++)
        struttura[i][j] = ' ';
    for(i=grandezza*2+2, j=grandezza+2; j < grandezza*2-1; j++)
        struttura[i][j] = ' ';
    for(i=grandezza*2+2, j=grandezza*2-2; i < grandezza*3-1; i++)
        struttura[i][j] = ' ';
    for(i=grandezza*3-2, j=grandezza+2; j < grandezza*2-1; j++)
        struttura[i][j] = ' ';
}

void StampaO_Nono(char struttura[dim][dim]){

    int i, j;

    ///nono riquadro
    for(i=grandezza*2+2, j=grandezza*2+2; i < grandezza*3-1; i++)
        struttura[i][j] = ' ';
    for(i=grandezza*2+2, j=grandezza*2+2; j < grandezza*3-1; j++)
        struttura[i][j] = ' ';
    for(i=grandezza*2+2, j=grandezza*3-2; i < grandezza*3-1; i++)
        struttura[i][j] = ' ';
    for(i=grandezza*3-2, j=grandezza*2+2; j < grandezza*3-1; j++)
        struttura[i][j] = ' ';
}


