#include <stdio.h>

#ifndef StrutturePerProgetto_c_INCLUDED
#define StrutturePerProgetto_c_INCLUDED


#define MaxMatrixY  13
#define MaxMatrixX  25

#define AbsoluteMaxMatrixX  100
#define AbsoluteMaxMatrixY  100

#define MAX 6500

struct Menu
{

    char Spaziomenu[AbsoluteMaxMatrixX][AbsoluteMaxMatrixY];
    char paddingchar;
    int dimX;
    int dimY;
    int NumberOfElements;
    char LabelOfMenu[MAX];

    char CharDaRisaltare;
    int ColorDaRisaltare;
    int ColorAttuale;
};


struct PLAYER
{

    int AbsoluteWin;
    int RelativeWin;
    int VittorieDaRaggiungere;
};

struct GraficaTris
{
    int BorderColor;
    int Player1Color;
    int Player2Color;
} Graf1;

struct Titolo
{
    char NomeTitolo[AbsoluteMaxMatrixX][AbsoluteMaxMatrixY];
    int NumRighe;
};

struct Anteprima
{
    char LabelOfMenu[MAX];
    char Spaziomenu[AbsoluteMaxMatrixX][AbsoluteMaxMatrixY];
    char paddingchar;
    int dimX;
    int dimY;
    char CharDaRisaltare;

};

#endif
