/*
File: enemy.h
Purpose: stors the enemy function declarations
Last modified: 2026-05-20
*/
#ifndef ENEMY_H
#define ENEMY_H

#include "map.h"

/*storing the enemey row, col, direction and the previous movemtn*/
typedef struct{
    int row;
    int col;
    char dir;
    char prev;
}Enemy;

void initEnemy(Map*map, Enemy * enemy); /*initialised the position of enemy and the default vals*/

void moveEnemy(Map*map, Enemy *enemy); /*for the enemy movement handling*/

#endif
