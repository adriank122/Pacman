#include "core/game.h"
#include "rendering/renderer.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

namespace pacman {
namespace core {

void game_menu(SGame &game, rendering::Renderer &renderer){
    renderer.showMenu();

    while (!renderer.keyAvailable()) { renderer.sleep(50); }
    char c=renderer.getChar();

    switch (c) {
    case '1':
        game_init(game);
        game_new(game, 1, renderer);
        break;
    case '2':
        game_instruction(game, renderer);
        break;
    case '3':
        game_leaderboard(game, renderer);
        break;
    case '4':
        game_quit(renderer);
        break;
    default:
        game_menu(game, renderer);
        break;
    }

}

void game_new(SGame &game, int level, rendering::Renderer &renderer){
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


   while(game.pman.lives>0&&game.timer>0&&game.food>0){
        ghost_move(game.ghost1, game.map);
        ghost_move(game.ghost2, game.map);
        ghost_move(game.ghost3, game.map);
        ghost_move(game.ghost4, game.map);
        pman_move(game.pman, game.map, renderer);
        game_count(game, renderer);
        renderer.showGameState(game);
        renderer.sleep(game.delay);

    }

   renderer.clear();

   if(game.pman.lives<=0)
   {
         renderer.showGameOver("lives");
         save_leaderboard(game, renderer);
         show_leaderboard(renderer);
         cout<<"\n\n\nPress 'm', to go back to main menu.";
         while (!renderer.keyAvailable()) { renderer.sleep(50); }
         char c=renderer.getChar();
         while(c!='m')
         {
             while (!renderer.keyAvailable()) { renderer.sleep(50); }
             c=renderer.getChar();
         }
         game_menu(game, renderer);
   }

   if(game.timer<=0)
   {
       renderer.showGameOver("time");
       while (!renderer.keyAvailable()) { renderer.sleep(50); }
       char c=renderer.getChar();
       if(c)
       {
           game_menu(game, renderer);
       }
   }
   if(game.food<=0)
   {
       renderer.showGameOver("won");
       while (!renderer.keyAvailable()) { renderer.sleep(50); }
       char c=renderer.getChar();
       while(c!='m'&&c!='o')
       {
           while (!renderer.keyAvailable()) { renderer.sleep(50); }
           c=renderer.getChar();
       }
       if(c=='m')
       {
           game_menu(game, renderer);
       }
       if(c=='o')
       {
           game_init(game);
           game_new(game, 2, renderer);
       }
   }
}


void game_count(SGame &game, rendering::Renderer &renderer){
    game.timer-=game.delay;
    game.food=0;

    for(int i=0; i<17; i++)
        for(int j=0; j<20; j++)
            if(game.map.map[i][j]=='.'||game.map.map[i][j]=='e')
                game.food++;

    if(game.ghost1.xg==game.map.xp&&game.ghost1.yg==game.map.yp||game.ghost2.xg==game.map.xp&&game.ghost2.yg==game.map.yp)
    {
        game.pman.lives--;
        game.map.xp=13;
        game.map.yp=9;
        game.map.map[game.map.xp][game.map.yp]='O';
    }
    
    renderer.showGameCounter(game);
}

int game_quit(rendering::Renderer &renderer){
    renderer.clear();
    return 1;
}

void game_instruction(SGame &game, rendering::Renderer &renderer){

    renderer.showInstructions();

    while (!renderer.keyAvailable()) { renderer.sleep(50); }
    char c=renderer.getChar();
    if(c=='1')
        game_menu(game, renderer);
    else
        game_instruction(game, renderer);

}

void game_init(SGame &game)
{
    init_map(game.map);
    init_pman(game.pman);
    game.timer=200000;
    game.delay=300;
    init_ghost(game.ghost1, 15, 1);
    init_ghost(game.ghost2, 15, 18);
    init_ghost(game.ghost3, 1, 1);
    init_ghost(game.ghost4, 1, 18);
}

void game_leaderboard(SGame game, rendering::Renderer &renderer)
{
    renderer.showLeaderboard();
    while (!renderer.keyAvailable()) { renderer.sleep(50); }
    char c=renderer.getChar();
    if(c=='1')
        game_menu(game, renderer);
    else
        game_leaderboard(game, renderer);
}

void show_leaderboard(rendering::Renderer &renderer)
{
    // Note: This is called from rendering components
}

void save_leaderboard(SGame game, rendering::Renderer &renderer)
{
    ifstream f;
    int positions=0;
    string line;
    f.open("leaderboard.txt");
    while(!f.eof())
    {
        getline(f, line);
        positions++;
    }
    f.close();

    string tab[positions];

    f.open("leaderboard.txt");
    for(int i=0; i<positions; i++)
    {
        getline(f, line);
        tab[i]=line;
    }

    ofstream of;
    of.open("leaderboard.txt");
    string player_name = "Player";
    for(int i=0; i<positions; i++)
    {
        of<<tab[i]<<"\n";
    }

    of<<player_name<<"-"<<game.pman.points;
    of.close();
}

} // namespace core
} // namespace pacman
