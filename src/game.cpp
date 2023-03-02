#include "game.h"
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <fstream>

using namespace std;

void game_menu(SGame &game){

    system("cls");

    cout<<"\t\tPACMAN by Adrian Kaliciecki\n\n\n";

    cout<<"Wcisnij:\n\n";
    cout<<"1 -->\tNowa gra\n";
    cout<<"2 -->\tInstrukcja\n";
    cout<<"3 -->\tRanking\n";
    cout<<"4 -->\tWyjscie\n\n";

    char zn=getch();

    switch (zn) {
    case '1':
        game_init(game);
        game_new(game, 1);
        break;
    case '2':
        game_instruction(game);
        break;
    case '3':
        game_ranking(game);
        break;
    case '4':
        game_quit();
        break;
    default:
        game_menu(game);
        break;
    }

}

void game_new(SGame &game, int level){

    //tutaj rozpoczynamy gre

    system("cls");

    if(level==1)
    {
        map_create1(game.map);
    }
    if(level==2)
    {
        map_create2(game.map);
    }
    game_count(game);


   while(game.pman.lives>0&&game.stoper>0&&game.food>0){
        system("cls");
        ghost_move(game.ghost1, game.map);
        ghost_move(game.ghost2, game.map);
        ghost_move(game.ghost3, game.map);
        ghost_move(game.ghost4, game.map);
        pman_move(game.pman, game.map);
        game_count(game);
        map_show(game.map);
        Sleep(game.delay);

    }

   system("cls");

   if(game.pman.lives<=0)
   {
         cout<<"Koniec gry!\n\n\nWyczerpales limit zyc.\n\n\nWpisz swoje imie i zatwierdz enterem:\n\n";
         save_ranking(game);
         show_ranking();
         cout<<"\n\n\nWcisnij 'm', aby wrocic do menu glownego.";
         char zn=getch();
         while(zn!='m')
         {
             zn=getch();
         }
         game_menu(game);
   }

   if(game.stoper<=0)
   {
       cout<<"Koniec gry!\n\n\nWyczerpales limit czasu.\n\n\nWcisnij enter, aby wrocic do menu\n\n";
       char zn=getch();
       if(zn)
       {
           game_menu(game);
       }
   }
   if(game.food<=0)
   {
       cout<<"Zjadles wszystkie ciasteczka i ukonczyles poziom!\n\n\nWcisnij 'o', aby przejsc do nastepnego poziomu.\n\n";
       cout<<"Wcisnij 'm', aby wrocic do menu glownego.\n\n";
       char zn=getch();
       while(zn!='m'&&zn!='o')
       {
           zn=getch();
       }
       if(zn=='m')
       {
           game_menu(game);
       }
       if(zn=='o')
       {
           game_init(game);
           game_new(game, 2);
       }
   }
}


void game_count(SGame &game){

    //tutaj tworze liczniki


//              licznik czasu
    game.stoper-=game.delay;
    cout<<"Pozostaly czas: "<<game.stoper/1000<<"\n\n";


//              licznik punktów
    cout<<"Punkty: "<<game.pman.points<<"\n\n";


//              licznik jedzenia
    game.food=0;

    for(int i=0; i<17; i++)
        for(int j=0; j<20; j++)
            if(game.map.map[i][j]=='.'||game.map.map[i][j]=='e')
                game.food++;

    cout<<"Suma ciasteczek: "<<game.food<<"\n\n";


//              licznik życia

    if(game.ghost1.xg==game.map.xp&&game.ghost1.yg==game.map.yp||game.ghost2.xg==game.map.xp&&game.ghost2.yg==game.map.yp)
    {
        game.pman.lives--;
        game.map.xp=13;
        game.map.yp=9;
        game.map.map[game.map.xp][game.map.yp]='O';
    }
    cout<<"Ilosc zyc: "<<game.pman.lives<<"\n\n";

}

int game_quit(){

    //tutaj tworze wyjscie z gry

    system("cls");
    return 1;

}





void game_instruction(SGame &game){

    //instrukcja

    system("cls");

    cout<<"\nW --> ruch do gory\n";
    cout<<"A --> ruch w lewo\n";
    cout<<"S --> ruch do dolu\n";
    cout<<"D --> ruch w prawo\n\n";
    cout<<"Zbierz wszystkie ciasteczka, aby przejsc etap!\nNie daj sie zjesc duchom.\n";
    cout<<"Masz trzy zycia\n\n\n\n";

    cout<<"1 -->Wroc do menu\n";

    char zn=getch();
    if(zn=='1')
        game_menu(game);
    else
        game_instruction(game);

}

void game_init(SGame &game)
{
    init_map(game.map);
    init_pman(game.pman);
    game.stoper=200000;
    game.delay=300;
    init_ghost(game.ghost1, 15, 1);
    init_ghost(game.ghost2, 15, 18);
    init_ghost(game.ghost3, 1, 1);
    init_ghost(game.ghost4, 1, 18);
}

void game_ranking(SGame game)
{
    system("cls");
    cout<<"Lista wynikow graczy:\n";
    show_ranking();
    cout<<"\n\n\n";
    cout<<"1 --> Wroc do menu glownego";
    char zn=getch();
    if(zn=='1')
        game_menu(game);
    else
        game_ranking(game);
}

void show_ranking()
{
    cout<<"\n\n\n";
    string napis;
    ifstream we;
    we.open("ranking.txt");
    while(!we.eof())
    {
        getline(we, napis);
        cout<<napis<<"\n\n";
    }
    we.close();
}

void save_ranking(SGame game)
{
    ifstream we;
    int iloscpozycji=0;
    string napis;
    we.open("ranking.txt");
    while(!we.eof())
    {
        getline(we, napis);
        iloscpozycji++;
    }
    we.close();

    string tab[iloscpozycji];

    we.open("ranking.txt");
    for(int i=0; i<iloscpozycji; i++)
    {
        getline(we, napis);
        tab[i]=napis;
    }

    ofstream wy;
    wy.open("ranking.txt");
    cin>>napis;
    for(int i=0; i<iloscpozycji; i++)
    {
        wy<<tab[i]<<"\n";
    }

    wy<<napis<<"-"<<game.pman.points;
    wy.close();
}
