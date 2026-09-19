#include <stdio.h>
#include <stdlib.h>
#include "color.h"
#include "map.h"

int loadMap(char *filename, Map *map){

    FILE * fptr;

    int i;
    int j;
    int value;
    int success;

    success= 1;

    fptr= fopen(filename,"r");

    /*checks whether the file opened successfully*/
    if (fptr == NULL){
        printf("Error: Could not open file\n");
        success= 0;
    }

    if(success== 1){
        fscanf(fptr, "%d %d", &map->rows, &map->cols); /*read no.of rows and cols*/
        map->grid= (char**)malloc(map->rows *sizeof(char *)); /*allocate the memeory for the map*/

        if(map->grid== NULL){
            success= 0;
        }
    }

    if(success== 1){
        for(i=0; i<map->rows; i++){ /*allocate memeory for each col*/
            map->grid[i]= (char *)malloc(map->cols * sizeof(char));

            if(map->grid[i]== NULL){
                success= 0; /*checks if the allocation is a success*/
            }
        }
    }

    if(success== 1){
        for(i=0; i<map->rows; i++){ /*reading map vals from the file*/
            for (j=0; j<map->cols; j++){
                fscanf(fptr, "%d", &value);

                if(value==0){ /*for empty spaces*/
                    map->grid[i][j]= ' ';
                }
                else if(value== 1){ /*for walls */
                    map->grid[i][j]= '*';
                }
                else if(value== 2){ /*for the goal*/
                    map->grid[i][j]= 'G';
                    /*storing the position of G*/
                    map->goalRow=i;
                    map->goalCol=j;
                }
                else if(value== 3){ /*for the treasure*/
                    map->grid[i][j]= 'T';
                    /*stroing the position of T*/
                    map->treasureRow= i;
                    map->treasureCol=j;
                }
                else if(value== 4){/*for the player*/
                    map->grid[i][j]= 'P';
                    /* map->playerRow= i;
                    map->playerCol=j; */
                }
                else if(value== 5){ /*for the enemy*/
                    map->grid[i][j]= '<';
                    /* map->enemyRow= i;
                    map->enemyCol=j; */
                }
            }
        }
    }

    if(fptr != NULL){   /*closes the file once read*/
        fclose(fptr);
    }
    return success;
}

void printMap(Map *map, int enemyFast){
    int i;
    int j;

    system("clear"); /*clearing the terminal*/
    /* printf("\033[H\033[J"); */

    for(j= 0; j<map->cols+2; j++){
        printf("*"); /*top border being printed*/
    }
    printf("\n");

    /*to printout the contents of the map on the svreen*/
    for(i=0; i<map->rows; i++){
        printf("*");

        for(j=0; j<map->cols; j++){
            if(map->grid[i][j]== '*'){ /*printing walls*/
                setBackground("white");
                printf(" ");
                setBackground("reset");
            }
            else if(map->grid[i][j]== 'P'){ /*printing player*/
                setForeground("blue");
                printf("P");
                setForeground("reset");
            }
            else if(map->grid[i][j]== 'G'){ /*printing the goal*/
                setBackground("green");
                setForeground("black");
                printf("G");
                setBackground("reset");
                setForeground("reset");
            }
            else if(map->grid[i][j]== 'T'){ /*printing the treasure*/
                setBackground("yellow");
                setForeground("black");
                printf("T");
                setBackground("reset");
                setForeground("reset");
            }
            /*printing out the enmy*/
            else if(map->grid[i][j]== '<' || map->grid[i][j]== '>' ||
                    map->grid[i][j]== '^' || map->grid[i][j]== 'v'){
                        if(enemyFast== 1){ /*printing the furitous enemuy*/
                            setBackground("red");
                            setForeground("white");
                            printf("%c", map->grid[i][j]);
                            setForeground("reset");
                            setBackground("reset");
                        }else{ /*printing the normal enemuy*/
                            setForeground("red");
                            printf("%c", map->grid[i][j]);
                            setForeground("reset");
                        }
            }
            else{
                printf("%c", map->grid[i][j]); /*printing empty spaces*/
            }
        }
        printf("*\n");/*printing the right boeder */
    }
    for(j= 0; j<map->cols+2; j++){ /*printing the bottom boeder*/
        printf("*");
    }
    printf("\n");

    /*displaying the instructions to the user*/
    printf("Press 'w' to move UP\n");
    printf("Press 's' to move DOWN\n");
    printf("Press 'a' to move LEFT\n");
    printf("Press 'd' to move RIGHT\n");
    printf("Press 'u' to UNDO\n");
}
void freeMap(Map *map){
    int i;

    /*freeing each border of the map*/
    for(i=0; i<map->rows; i++){
        free(map->grid[i]);
        map->grid[i]= NULL;
    }

    /*freeing main grid*/
    free(map->grid);
    map->grid= NULL;
}
