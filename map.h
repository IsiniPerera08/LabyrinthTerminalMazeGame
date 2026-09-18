/*
File: map.h
Name: Isini Ayansa Perera
Student ID: 23601321
Unit: COMP1000(Unix and C programming)
Purpose: Stores the map structure and functions related to the map handling
Last modified: 2026-05-20
*/
#ifndef MAP_H
#define MAP_H

/*stores the no.of rows, cols,2D map,goalposition, treasure position*/
typedef struct{
    int rows;
    int cols;
    int treasureRow;
    int treasureCol;
    int goalRow;
    int goalCol;
    char **grid;
} Map;

int loadMap(char *filename, Map *map); /*to load the map from the file */

void printMap(Map *map, int enemyFast); /*print the map*/

void freeMap(Map *map); /*freeing memory*/

#endif