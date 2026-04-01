#include "game.h"
#include "renderer.h"
#include "cli_renderer.h"
#include "platform_utils.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

void game_menu(SGame &game, Renderer &renderer){

    renderer.showMenu();

    while (!renderer.keyAvailable()) { renderer.sleep(50); }
    char zn=renderer.getChar();

    switch (zn) {
    case '1':
        game_init(game);
        game_new(game, 1, renderer);
        break;
    case '2':
        game_instruction(game, renderer);
        break;
    case '3':
        game_ranking(game, renderer);
        break;
    case '4':
        game_quit(renderer);
        break;
    default:
        game_menu(game, renderer);
        break;
    }

}

void game_new(SGame &game, int level, Renderer &renderer){

    //tutaj rozpoczynamy gre

    renderer.clear();

    if(level==1)
    {
        map_create1(game.map);
    }
    if(level==2)
    {
        map_create2(game.map);
    }
    game_count(game, renderer);


   while(game.pman.lives>0&&game.stoper>0&&game.food>0){
        renderer.clear();
        ghost_move(game.ghost1, game.map);
        ghost_move(game.ghost2, game.map);
        ghost_move(game.ghost3, game.map);
        ghost_move(game.ghost4, game.map);
        pman_move(game.pman, game.map);
        game_count(game, renderer);
        renderer.showMap(game.map);
        renderer.sleep(game.delay);

    }

   renderer.clear();

   if(game.pman.lives<=0)
   {
         renderer.showGameOver("lives");
         save_ranking(game, renderer);
         show_ranking(renderer);
         cout<<"\n\n\nWcisnij 'm', aby wrocic do menu glownego.";
         while (!renderer.keyAvailable()) { renderer.sleep(50); }
         char zn=renderer.getChar();
         while(zn!='m')
         {
             while (!renderer.keyAvailable()) { renderer.sleep(50); }
             zn=renderer.getChar();
         }
         game_menu(game, renderer);
   }

   if(game.stoper<=0)
   {
       renderer.showGameOver("time");
       while (!renderer.keyAvailable()) { renderer.sleep(50); }
       char zn=renderer.getChar();
       if(zn)
       {
           game_menu(game, renderer);
       }
   }
   if(game.food<=0)
   {
       renderer.showGameOver("won");
       while (!renderer.keyAvailable()) { renderer.sleep(50); }
       char zn=renderer.getChar();
       while(zn!='m'&&zn!='o')
       {
           while (!renderer.keyAvailable()) { renderer.sleep(50); }
           zn=renderer.getChar();
       }
       if(zn=='m')
       {
           game_menu(game, renderer);
       }
       if(zn=='o')
       {
           game_init(game);
           game_new(game, 2, renderer);
       }
   }
}


void game_count(SGame &game, Renderer &renderer){

    //tutaj tworze liczniki

    //              licznik czasu
    game.stoper-=game.delay;

    //              licznik jedzenia
    game.food=0;

    for(int i=0; i<17; i++)
        for(int j=0; j<20; j++)
            if(game.map.map[i][j]=='.'||game.map.map[i][j]=='e')
                game.food++;

    //              licznik życia
    if(game.ghost1.xg==game.map.xp&&game.ghost1.yg==game.map.yp||game.ghost2.xg==game.map.xp&&game.ghost2.yg==game.map.yp)
    {
        game.pman.lives--;
        game.map.xp=13;
        game.map.yp=9;
        game.map.map[game.map.xp][game.map.yp]='O';
    }
    
    renderer.showGameCounter(game);
}

int game_quit(Renderer &renderer){

    //tutaj tworze wyjscie z gry

    renderer.clear();
    return 1;

}





void game_instruction(SGame &game, Renderer &renderer){

    //instrukcja

    renderer.showInstructions();

    while (!renderer.keyAvailable()) { renderer.sleep(50); }
    char zn=renderer.getChar();
    if(zn=='1')
        game_menu(game, renderer);
    else
        game_instruction(game, renderer);

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

void game_ranking(SGame game, Renderer &renderer)
{
    renderer.showRanking();
    while (!renderer.keyAvailable()) { renderer.sleep(50); }
    char zn=renderer.getChar();
    if(zn=='1')
        game_menu(game, renderer);
    else
        game_ranking(game, renderer);
}

void show_ranking(Renderer &renderer)
{
    // Note: This is called from cli_renderer.cpp now, but keep for compatibility
}

void save_ranking(SGame game, Renderer &renderer)
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
    // Note: Player name input would be handled by renderer in full implementation
    // For now, using placeholder
    string player_name = "Player";
    for(int i=0; i<iloscpozycji; i++)
    {
        wy<<tab[i]<<"\n";
    }

    wy<<player_name<<"-"<<game.pman.points;
    wy.close();
}
