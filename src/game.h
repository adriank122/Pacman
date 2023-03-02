#ifndef GAME_H
#define GAME_H

#include <map.h>
#include <pman.h>
#include <ghost.h>


struct SGame{
    struct SPman pman;
    struct SMap map;
    struct SGhost ghost1, ghost2, ghost3, ghost4;

    int stoper;
    int delay;
    int food;
};

void game_menu(SGame &game);
int game_quit();
void game_count(SGame &game);
void game_new(SGame &game, int level);
void game_instruction(SGame &game);
void game_init(SGame &game);
void show_ranking();
void save_ranking(SGame game);
void game_ranking(SGame game);


#endif // GAME_H
