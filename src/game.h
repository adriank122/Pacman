#ifndef GAME_H
#define GAME_H

#include "map.h"
#include "pman.h"
#include "ghost.h"

// Forward declaration to avoid circular dependency
class Renderer;


struct SGame{
    struct SPman pman;
    struct SMap map;
    struct SGhost ghost1, ghost2, ghost3, ghost4;

    int timer;
    int delay;
    int food;
};

void game_menu(SGame &game, Renderer &renderer);
int game_quit(Renderer &renderer);
void game_count(SGame &game, Renderer &renderer);
void game_new(SGame &game, int level, Renderer &renderer);
void game_instruction(SGame &game, Renderer &renderer);
void game_init(SGame &game);
void show_leaderboard(Renderer &renderer);
void save_leaderboard(SGame game, Renderer &renderer);
void game_leaderboard(SGame game, Renderer &renderer);


#endif // GAME_H
