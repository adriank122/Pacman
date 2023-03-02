#ifndef MAP_H
#define MAP_H

struct SMap
{
    char map[17][20];
    int xp, yp, xg1, yg1, xg2, yg2;
};

void init_map(SMap &map);

void map_create1(SMap &map);  //fukncja do tworzenia tablicy
void map_create2(SMap &map);
void map_create3(SMap &map);
void map_show(SMap map);    //funkcja do wyswietlania tablicy

#endif // MAP_H
