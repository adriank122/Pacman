#include "map.h"
#include <iostream>
#include <iomanip>

using namespace std;

void init_map(SMap &map)
{
    map.xp=13;
    map.yp=9;
}

void map_create1(SMap &map)
{
    int xp=map.xp, yp=map.yp;

    for(int i=0; i<17; i++)
    {
        for(int j=0; j<20; j++)
        {
            map.map[i][j]='x';
        }
    }

    for(int i=1; i<19; i++)
    {
        map.map[1][i]='.';
        map.map[3][i]='.';
        map.map[6][i]='.';
        map.map[8][i]='.';
        map.map[10][i]='.';
        map.map[13][i]='.';
        map.map[15][i]='.';
    }

    for(int i=1; i<16; i++)
    {
        map.map[i][1]='.';
        map.map[i][3]='.';
        map.map[i][5]='.';
        map.map[i][7]='.';
        map.map[i][12]='.';
        map.map[i][14]='.';
        map.map[i][16]='.';
        map.map[i][18]='.';
    }

    map.map[2][5]='x';
    map.map[2][7]='x';
    map.map[2][12]='x';
    map.map[2][14]='x';

    map.map[3][2]='x';
    map.map[3][4]='x';
    map.map[3][15]='x';
    map.map[3][17]='x';

    map.map[6][2]='x';
    map.map[6][4]='x';
    map.map[6][6]='x';
    map.map[6][13]='x';
    map.map[6][15]='x';
    map.map[6][17]='x';

    map.map[8][4]='x';
    map.map[8][6]='x';
    map.map[8][13]='x';
    map.map[8][15]='x';

    map.map[10][2]='x';
    map.map[10][6]='x';
    map.map[10][13]='x';
    map.map[10][17]='x';

    map.map[13][2]='x';
    map.map[13][4]='x';
    map.map[13][15]='x';
    map.map[13][17]='x';

    map.map[14][5]='x';
    map.map[14][7]='x';
    map.map[14][12]='x';
    map.map[14][14]='x';

    map.map[xp][yp]='O';
}

void map_create2(SMap &map)
{
    int xp=map.xp, yp=map.yp;

    for(int i=0; i<17; i++)
    {
        for(int j=0; j<20; j++)
        {
            map.map[i][j]='x';
        }
    }

    for(int j=1; j<19; j++)
    {
        map.map[1][j]='.';
        map.map[4][j]='.';
        map.map[6][j]='.';
        map.map[10][j]='.';
        map.map[15][j]='.';
    }

    map.map[2][1]='.';
    map.map[3][1]='.';
    map.map[5][1]='.';
    map.map[8][1]='.';
    map.map[11][1]='.';
    map.map[13][1]='.';
    map.map[14][1]='.';

    map.map[2][18]='.';
    map.map[3][18]='.';
    map.map[5][18]='.';
    map.map[8][18]='.';
    map.map[11][18]='.';
    map.map[13][18]='.';
    map.map[14][18]='.';

    map.map[8][3]='.';

    map.map[8][16]='.';

    map.map[7][4]='.';
    map.map[8][4]='.';
    map.map[9][4]='.';

    map.map[7][8]='.';
    map.map[8][8]='.';
    map.map[9][8]='.';

    map.map[7][11]='.';
    map.map[8][11]='.';
    map.map[9][11]='.';

    map.map[7][15]='.';
    map.map[8][15]='.';
    map.map[9][15]='.';

    map.map[2][7]='.';
    map.map[3][7]='.';
    map.map[13][7]='.';
    map.map[14][7]='.';

    map.map[2][12]='.';
    map.map[3][12]='.';
    map.map[13][12]='.';
    map.map[14][12]='.';

    map.map[8][0]='.';
    map.map[8][2]='.';
    map.map[8][17]='.';
    map.map[8][19]='.';

    map.map[12][1]='.';
    map.map[12][2]='.';
    map.map[12][3]='.';
    map.map[12][4]='.';
    map.map[12][5]='.';
    map.map[12][6]='.';
    map.map[12][7]='.';
    map.map[12][12]='.';
    map.map[12][13]='.';
    map.map[12][14]='.';
    map.map[12][15]='.';
    map.map[12][16]='.';
    map.map[12][17]='.';
    map.map[12][18]='.';

    map.map[13][8]='.';
    map.map[13][9]='.';
    map.map[13][10]='.';
    map.map[13][11]='.';


    map.map[xp][yp]='O';
}

void map_create3(SMap &map){                  //poczatek tworzenia tablicy

    //tutaj tworze mape

    int xp=map.xp, yp=map.yp;

    for(int i=0; i<17; i++)         //wypelniamy tablice 'x'
        for(int j=0; j<20; j++)
            map.map[i][j]='x';

    for(int j=1; j<19; j++){        //wstawiamy ciasteczka
        map.map[1][j]='.';
        map.map[3][j]='.';
        map.map[13][j]='.';
        map.map[15][j]='.';
    }

    for(int i=1; i<7; i++){
        map.map[i][1]='.';
        map.map[i][18]='.';
    }

    for(int i=10; i<16; i++){
        map.map[i][1]='.';
        map.map[i][18]='.';
    }

    for(int j=3; j<17; j++){
        map.map[5][j]='.';
        map.map[11][j]='.';
    }

    for(int i=1; i<7; i++){
        map.map[i][1]='.';
        map.map[i][18]='.';
    }

    for(int j=7; j<13; j++){
        map.map[6][j]='.';
        map.map[10][j]='.';
    }

    for(int i=5; i<14; i++){
        map.map[i][3]='.';
        map.map[i][16]='.';
    }

    for(int j=0; j<6; j++)
        map.map[8][j]='.';

    for(int j=14; j<20; j++)
        map.map[8][j]='.';

    for(int j=5; j<8; j++){
        map.map[7][j]='.';
        map.map[9][j]='.';
    }

    for(int j=12; j<15; j++){
        map.map[7][j]='.';
        map.map[9][j]='.';
    }

    for(int j=7; j<13; j++)
        map.map[8][j]='.';

    map.map[6][2]='.';
    map.map[10][2]='.';

    map.map[2][5]='.';
    map.map[14][5]='.';

    map.map[4][7]='.';
    map.map[12][7]='.';

    map.map[4][12]='.';
    map.map[12][12]='.';

    map.map[2][14]='.';
    map.map[14][14]='.';

    map.map[6][17]='.';
    map.map[10][17]='.';

    map.map[1][1]='e';                 //wstawiamy dopalacze
    map.map[15][1]='e';
    map.map[1][18]='e';
    map.map[15][18]='e';

    map.map[map.xp][map.yp]='O';



}                                   //koniec tworzenia tablicy

void map_show(SMap map){                    //wyswietlanie tablicy

    //tutaj wyswietlam mape

    cout<<"\n";
    for(int i=0; i<17; i++){
        cout<<"\n\t";
        for(int j=0; j<20; j++)
            cout<<setw(2)<<map.map[i][j];
    }
    cout<<"\n";

}
