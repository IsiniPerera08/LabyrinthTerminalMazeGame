/*
File: player.h
Name: Isini Ayansa Perera
Student ID: 23601321
Unit: COMP1000(Unix and C programming)
Purpose: Stores the player functions declared
Last modified: 2026-05-20
*/
#ifndef PLAYER_H
#define PLAYER_H
#include "map.h"

/*stores player row, col, whether collected treasure,and reached goal */
typedef struct{
    int row;
    int col;
    int hasTreasure;
    int hasGoal;
}Player;

void initPlayer(Map * map, Player * player); /*initialised the player poition and default values*/

int movePlayer(Map * map, Player * player , char input); /*movement of player handled*/

#endif