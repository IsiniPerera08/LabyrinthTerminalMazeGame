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
