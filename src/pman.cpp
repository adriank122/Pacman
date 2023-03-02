#include "pman.h"
#include <iostream>
#include <conio.h>

using namespace std;

void init_pman(SPman &pman)
{
    pman.lives = 3;
    pman.points = 0;
}

void pman_move(SPman &pman, SMap &map){

    //tutaj opisuje ruchy pacmana

    if(map.map[map.xp][map.yp]=='A')
    {
        pman.lives--;
        map.map[map.xp][map.yp]='A';
        map.xp=13;
        map.yp=9;
    }

    if(_kbhit()){

    char input=getch();

    int points=pman.points;
    int xp=map.xp, yp=map.yp;

    switch (input){

    case 'a':

        if(xp==8&&yp==0)
        {
            map.map[xp][yp]=' ';
            if(map.map[8][19]=='.')
                points++;
            yp=19;
            break;
        }

            if(map.map[xp][yp-1]!='x'){
                if(map.map[xp][yp-1]=='.'){
                    points++;
                }
                if(map.map[xp][yp-1]=='e'){
                    points+=5;
                }
                if(map.map[xp][yp-1]=='A'){
                    pman.lives--;
                    map.map[xp][yp]=' ';
                    xp=13;
                    yp=9;
                }
                map.map[xp][yp]=' ';
                yp--;
                break;
            }
            else
                break;

    case 'w':
            if(map.map[xp-1][yp]!='x'){
                if(map.map[xp-1][yp]=='.'){
                    points++;
                }
                if(map.map[xp-1][yp]=='e'){
                    points+=5;
                }
                if(map.map[xp-1][yp]=='A'){
                    pman.lives--;
                    map.map[xp][yp]=' ';
                    xp=13;
                    yp=9;
                }
                map.map[xp][yp]=' ';
                xp--;
                break;
            }
            else
                break;

    case 's':
            if(map.map[xp+1][yp]!='x'){
                if(map.map[xp+1][yp]=='.'){
                    points++;
                }
                if(map.map[xp+1][yp]=='e'){
                    points+=5;
                }
                if(map.map[xp+1][yp]=='A'){
                    pman.lives--;
                    map.map[xp][yp]=' ';
                    xp=13;
                    yp=9;
                }
                map.map[xp][yp]=' ';
                xp++;
                break;
            }
            else
                break;

    case 'd':
        if(xp==8&&yp==19)
        {
            map.map[xp][yp]=' ';
            if(map.map[8][0]=='.')
                points++;
            yp=0;
            break;
        }
            if(map.map[xp][yp+1]!='x'){
                if(map.map[xp][yp+1]=='.'){
                    points++;
                }
                if(map.map[xp][yp+1]=='e'){
                    points+=5;
                }
                if(map.map[xp][yp+1]=='A'){
                    pman.lives--;
                    map.map[xp][yp]=' ';
                    xp=13;
                    yp=9;
                }
                map.map[xp][yp]=' ';
                yp++;
                break;
            }
            else
                break;
    default:
        break;

    }

    if(map.map[map.xp][map.yp]=='A')
    {
        pman.lives--;
        map.map[xp][yp]='A';
        xp=13;
        yp=9;
    }

    map.map[xp][yp]='O';
    map.xp=xp;
    map.yp=yp;
    pman.points=points;
}
}

void pman_boost(){

    //tutaj opisuje pacmana po zjedzeniu wzmacniacza

}
