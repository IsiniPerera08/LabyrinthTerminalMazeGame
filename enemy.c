/*
File: enemy.c
Name: Isini Ayansa Perera
Student ID: 23601321
Unit: COMP1000(Unix and C programming)
Purpose: Controls the enemy initialisation, movement,and behaviour
Last modified: 2026-05-20
*/
#include <stdio.h>
#include "enemy.h"
#include "random.h"
#include "map.h"

void initEnemy(Map*map, Enemy *enemy){
    int r;
    int c;

    enemy->row= 0;
    enemy->col= 0;
    enemy->dir= '<';
    enemy->prev= ' ';

    /*search map to find enemy start postion*/
    for(r= 0; r<map->rows; r++){
        for(c= 0; c <map->cols; c++){
            /*checks the enemy char on the map*/
            if(map->grid[r][c]== '<' || map->grid[r][c]=='>' || map->grid[r][c]== '^' || map->grid[r][c]== 'v'){
                enemy->row= r;
                enemy->col= c;
                enemy->dir= map->grid[r][c];    /*direction is stored*/
                enemy->prev= ' ';
            }
        }
    }
}

/*row and col movments offset based on the dir of the enemy*/
static void getOffset(char dir, int *dwnRow, int *dwnCol){
    if(dir== '^'){  /*moves up*/
        *dwnRow= -1;
        *dwnCol= 0;
    }else if(dir == 'v'){/*moves down*/
        *dwnRow= 1;
        *dwnCol= 0;
    }else if(dir =='<'){/*moves left*/
        *dwnRow= 0;
        *dwnCol= -1;
    }else{  /*moves right*/
        *dwnRow= 0;
        *dwnCol= 1;
    }
}
/*enemy rotates clockwise*/
static char rotateClockwise(char dir){
    char result;

    if(dir == '^'){
        result= '>';
    }else if(dir=='>'){
        result= 'v';
    }else if(dir=='v'){
        result= '<';
    }else{
        result= '^';
    }
    return result;
}
/*enemy rotating anticlockwise*/
static char rotateAntiClockwise(char dir){
    char result;

    if(dir== '^'){
        result= '<';
    }else if (dir== '<'){
        result= 'v';
    }else if(dir== 'v'){
        result= '>';
    }else{
        result= '^';
    }
    return result;
}

/*check if enemy can move or not*/
static int canMove(Map *map, int row, int col){
    int move;
    char cell;

    move= 0;
    /*checks the map boundaries*/
    if(row>=0 && row < map->rows && col >= 0 && col < map->cols){
        cell= map->grid[row][col];

        /*prevent enemy frm movinf into walls, treasure, goal*/
        if(cell != '*' && cell != 'T' && cell != 'G'){
            move= 1;
        }
    }
    return move;
}

/*the main enemy movement */
void moveEnemy(Map *map, Enemy * enemy){
    int fwdRow;
    int fwdCol;
    int leftRow;
    int leftCol;
    int rightRow;
    int rightCol;
    int dwnRow;
    int dwnCol;
    int fwdFree;
    int leftFree;
    int rightFree;
    int choice;
    char newDir;
    int newCol;
    int newRow;
    char leftDir;
    char rightDir;

    /*calculate forward movement*/
    getOffset(enemy->dir, &dwnRow, &dwnCol);
    fwdRow= enemy->row + dwnRow;
    fwdCol= enemy->col + dwnCol;
    /*calculate left movement*/
    leftDir= rotateAntiClockwise(enemy->dir);
    getOffset(leftDir, &dwnRow, &dwnCol);
    leftRow= enemy->row + dwnRow;
    leftCol= enemy->col + dwnCol;
    /*calculate right movement*/
    rightDir= rotateClockwise(enemy->dir);
    getOffset(rightDir, &dwnRow, &dwnCol);
    rightRow= enemy->row + dwnRow;
    rightCol= enemy->col + dwnCol;
    /*checks which paths available*/
    fwdFree= canMove(map, fwdRow, fwdCol);
    leftFree= canMove(map, leftRow, leftCol);
    rightFree= canMove(map, rightRow, rightCol);
    /*current enemy position is stored*/
    newRow= enemy->row;
    newCol= enemy->col;
    newDir= enemy->dir;
    /*if only the foward path is avaailable */
    if(fwdFree == 1 && leftFree== 0 && rightFree== 0){
        newRow= fwdRow;
        newCol= fwdCol;
        newDir= enemy->dir;
    }else if(fwdFree== 1 && leftFree == 1 && rightFree== 1){ /*if all 3 paths available*/
            choice = randomUCP(0, 2);   /*randomly choose a direction usinf Random*/
            if (choice== 0){
                newRow= fwdRow;
                newCol= fwdCol;
                newDir= enemy->dir;
            }else if(choice== 1){
                newDir= rotateAntiClockwise(enemy->dir);
                getOffset(newDir, &dwnRow, &dwnCol);
                newRow= enemy->row + dwnRow;
                newCol= enemy->col + dwnCol;
            }else{
                newDir= rotateClockwise(enemy->dir);
                getOffset(newDir, &dwnRow, &dwnCol);
                newRow= enemy->row + dwnRow;
                newCol= enemy->col + dwnCol;
            }
        }
        else if(fwdFree== 1 && leftFree==1){    /*forward and left paths are free*/
            choice= randomUCP(0,1);
            if (choice== 0){
                newRow= fwdRow;
                newCol= fwdCol;
                newDir= enemy->dir;
            }else{
                newDir= rotateAntiClockwise(enemy->dir);
                getOffset(newDir, &dwnRow, &dwnCol);
                newRow= enemy->row + dwnRow;
                newCol= enemy->col + dwnCol;
            }
        }
        else if(fwdFree== 1 && rightFree== 1){  /*if forward and right paths are available*/
            choice= randomUCP(0, 1);
            if(choice== 0){
                newRow= fwdRow;
                newCol= fwdCol;
                newDir= enemy->dir;
            }else{
                newDir= rotateClockwise(enemy->dir);
                getOffset(newDir, &dwnRow, &dwnCol);
                newRow= enemy->row + dwnRow;
                newCol= enemy->col + dwnCol;
            }
        }
        else if(fwdFree== 0 && leftFree== 1 && rightFree== 1){ /*if left and right poaths are available*/
            choice= randomUCP(0,1);
            if(choice == 0){
                newDir= rotateAntiClockwise(enemy->dir);
            }else{
                newDir= rotateClockwise(enemy->dir);
            }
            getOffset(newDir, &dwnRow, &dwnCol);
            newRow= enemy->row + dwnRow;
            newCol= enemy->col + dwnCol;
        }
        else if(fwdFree== 0 && leftFree== 1){   /*if only the left path is available*/
            newDir= rotateAntiClockwise(enemy->dir);
            getOffset(newDir, &dwnRow, &dwnCol);
            newRow= enemy->row + dwnRow;
            newCol= enemy->col + dwnCol;
        }
        else if(fwdFree==0 && rightFree== 1){   /*if only right path is available*/
            newDir= rotateClockwise(enemy->dir);
            getOffset(newDir, &dwnRow, &dwnCol);
            newRow= enemy->row + dwnRow;
            newCol= enemy->col +dwnCol;
        }else{  /*turn backwards if all paths are blocked*/
            newDir= rotateClockwise(rotateClockwise(enemy->dir));
            getOffset(newDir, &dwnRow, &dwnCol);
            newRow= enemy->row + dwnRow;
            newCol= enemy->col + dwnCol;
        }

        /*restoring the prev tiles*/
        map->grid[enemy->row][enemy->col]= enemy->prev;

        /*to store new tile info*/
        if(map->grid[newRow][newCol]== ' ' || map->grid[newRow][newCol]== 'P'){
            enemy->prev= ' ';
        }else{
            enemy->prev= map->grid[newRow][newCol];
        }
/*to update the enemy position*/
        enemy->row= newRow;
        enemy->col= newCol;
        enemy->dir= newDir;
        map->grid[enemy->row][enemy->col]= newDir;  /*placing the enemy to the map*/
    }