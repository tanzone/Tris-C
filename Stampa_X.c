#include <stdio.h>

#define grandezza (8)//GGRANDEZZA DELLA CELLA DEL TRIS SI PUO DIMENSIONARE COME SI VUOLE
#define dim (90)

void StampaDelleX(char struttura[dim][dim], int casella)
{

    /*FIGURE ALL'INTERNO DEI QUADRATI--------------------------------*/

    switch(casella)
    {

    case '1':
        StampaX_Primo(struttura);
        break;

    case '2':
        StampaX_Secondo(struttura);
        break;

    case '3':
        StampaX_Terzo(struttura);
        break;

    case '4':
        StampaX_Quarto(struttura);
        break;

    case '5':
        StampaX_Quinto(struttura);
        break;

    case '6':
        StampaX_Sesto(struttura);
        break;

    case '7':
        StampaX_Settimo(struttura);
        break;

    case '8':
        StampaX_Ottavo(struttura);
        break;

    case '9':
        StampaX_Nono(struttura);
        break;
    }
}

void StampaX_Primo(char struttura[dim][dim])
{

    int i, j;

    ///primo riquadro
    for(i = 2,j = grandezza-2; i < grandezza-1; i++)
    {
        struttura[i][i] = '-';
        struttura[i][j--] = '-';
    }
}

void StampaX_Secondo(char struttura[dim][dim])
{

    int i, j, q;

    ///secondo riquadro
    for(i = 2,j = grandezza+2, q =grandezza*2-2; i < grandezza-1; i++, j++)
    {
        struttura[i][j] = '-';
        struttura[i][q--] = '-';
    }
}

void StampaX_Terzo(char struttura[dim][dim])
{

    int i, j, q;

    ///terzo riquadro
    for(i = 2,j = grandezza*2+2, q = grandezza*3-2; i < grandezza-1; i++, j++)
    {
        struttura[i][j] = '-';
        struttura[i][q--] = '-';
    }
}

void StampaX_Quarto(char struttura[dim][dim])
{

    int i, j, q;

    ///quarto riquadro
    for(i = grandezza+2,j = 2, q = grandezza-2; i < grandezza*2-1; i++,j++)
    {
        struttura[i][j] = '-';
        struttura[i][q--] = '-';
    }
}

void StampaX_Quinto(char struttura[dim][dim])
{

    int i, j, q;

    ///quinto riquadro
    for(i=grandezza+2, j=grandezza+2,  q=grandezza*2-2; i < grandezza*2-1; i++, j++)
    {
        struttura[i][j] = '-';
        struttura[i][q--] = '-';
    }
}

void StampaX_Sesto(char struttura[dim][dim])
{

    int i, j, q;

    ///sesto riquadro
    for(i=grandezza+2, j=grandezza*2+2, q=grandezza*3-2; i < grandezza*2-1; i++,j++)
    {
        struttura[i][j] = '-';
        struttura[i][q--] = '-';
    }
}

void StampaX_Settimo(char struttura[dim][dim])
{

    int i, j, q;

    ///settimo riquadro
    for(i = grandezza*2+2,j = 2, q = grandezza-2; i < grandezza*3-1; i++,j++)
    {
        struttura[i][j] = '-';
        struttura[i][q--] = '-';
    }
}

void StampaX_Ottavo(char struttura[dim][dim])
{

    int i, j, q;

    ///ottavo riquadro
    for(i = grandezza*2+2, j=grandezza+2, q=grandezza*2-2; i < grandezza*3-1; i++, j++)
    {
        struttura[i][j] = '-';
        struttura[i][q--] = '-';
    }
}

void StampaX_Nono(char struttura[dim][dim])
{

    int i, j, q;

    ///nono riquadro
    for(i=grandezza*2+2, j=grandezza*2+2, q=grandezza*3-2; i < grandezza*3-1; i++,j++)
    {
        struttura[i][j] = '-';
        struttura[i][q--] = '-';
    }
}
