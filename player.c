/*
File: player.c
Name: Isini Ayansa Perera
Student ID: 23601321
Unit: COMP1000(Unix and C programming)
Purpose: Controls the player movement, collision checking, treasure collection and goal reached
Last modified: 2026-05-20
*/
#include <stdio.h>
#include "player.h"
#include "map.h"

/* initialise tje player */
void initPlayer(Map * map, Player *player){
    int pRow;
    int pCol;
    
    /* default player values */
    player->row= 0;
    player->col= 0;
    player->hasTreasure= 0;
    player->hasGoal=0;

    /* search map to find the player starting  position*/
    for (pRow= 0; pRow < map->rows; pRow++){
        for(pCol= 0; pCol < map->cols; pCol++){
            if(map->grid[pRow][pCol]== 'P'){
                player->row= pRow;
                player->col= pCol;
            }
        } 
    }
}

/*schecks if plyer  can move to a new lovation*/
static int moveTo(Map * map, Player *player, int newRow, int newCol){
    int pass;
    char target;

    pass= 1;
 
    /*prevents movement outside map walls*/
    if(newRow<0 || newRow >= map->rows || newCol<0 || newCol >= map->cols){
        pass= 0;
    }else{
        target= map->grid[newRow][newCol];
        /*stops player moving through enemy*/
        if(target=='*' || target== '^' || target=='v' || target== '<' || target=='>'){
            pass= 0;
        }else if (target== 'G' && player->hasTreasure== 0){ /* prevents player going to goal befroe collecting the treasure*/
            pass= 0;
        }
    }
    return pass;
}

/*player movment and interaction*/
int movePlayer(Map *map, Player* player, char input){
    int newRow;
    int newCol;
    int moved;
    char target;

    /*stores players current position*/
    newRow= player->row;
    newCol= player->col;
    moved= 0;

    /*Updste the target movemtn dir*/
    if(input== 'w'){
        newRow--;
    }
    else if (input == 's'){
        newRow++;
    }
    else if(input== 'a'){
        newCol--;
    }
    else if(input== 'd'){
        newCol++;
    }else{
        printf("Invalid key\n");
    }

    /*checks if a valid input key*/
    if(input=='w' || input== 's' || input== 'a' || input == 'd'){
        if (moveTo(map, player, newRow, newCol)== 1){   /*checks if movement allowed*/
            target= map->grid[newRow][newCol];

            if(target=='T'){    /*player collects treasure*/
                player->hasTreasure= 1; 
            }

            if(target=='G' && player->hasTreasure== 1){ /*if player reach goal after collecting treasure*/
                player->hasGoal= 1;
            }
            /*update player position on map*/
            map->grid[player->row][player->col]= ' ';
            map->grid[newRow][newCol]= 'P';

            player->row=newRow;
            player->col= newCol;

                moved= 1;
        }
    }
    return moved;
}