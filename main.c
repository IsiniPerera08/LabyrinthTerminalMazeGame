#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "color.h"
#include "terminal.h"
#include "player.h"
#include "random.h"
#include "enemy.h"
#include "linkedList.h"
#include "newSleep.h"
/* #include <ctype.h> */

int main(int argc, char * argv[]){
    Map map;
    Player player;
    Enemy enemy;
    int success;
    int running;
    char input;
    Node *undo;
    GameState *state;

    /* default values initisialised*/
    success= 1;
    running= 1;
    input= ' ';
    undo=NULL;
    state= NULL;
    
    /*random number generator also initialised*/
    initRandom();

    /*checks proper command line arg */
    if (argc != 2){
        printf("Usage: %s <map_file_name>\n", argv[0]);
        success= 0;
    }

    /*load map file*/
    if (success== 1){
        success= loadMap(argv[1], &map);
    }

    /*initialise player and enemy*/
    if(success== 1){
        initPlayer(&map, &player);
        initEnemy(&map, &enemy);
    }

    while(success == 1 && running == 1){
        printMap(&map, player.hasTreasure); /*prints map*/

        disableBuffer();
        scanf(" %c", &input); /*reads char value user inputs*/
        /* input= tolower(input); */
        enableBuffer();

        if(input == 'q'){   /*q to quit the game*/
            running = 0;
        }
        else if(input== 'u'){ /* u to undo the previous movement*/
            state= (GameState*)pop(&undo);
            if(state != NULL){
                /*then we clear curr player and enemy positions inorder to undo */
                map.grid[player.row][player.col]=' ';
                map.grid[enemy.row][enemy.col]=enemy.prev;

                /*  restores the previous state of theplayer... the player's row, col, treasure,...*/
                player.row= state->playerRow;
                player.col= state->playerCol;
                player.hasTreasure= state->hasTreasure;
                player.hasGoal= state->hasGoal;

                /*restors the previous state of the enemy... enemey's row, col, dir, prev*/
                enemy.row= state->enemyRow;
                enemy.col= state->enemyCol;
                enemy.dir= state->enemyDir;
                enemy.prev= state->enemyPrev;

                /* map.grid[player.row][player.col]='P';
                map.grid[enemy.row][enemy.col]= enemy.dir; */

                /*only if need restore the treasure*/
                if(player.hasTreasure== 0){
                    map.grid[state->treasureRow][state->treasureCol]= 'T';
                }
               
                if(player.hasGoal==0){
                    map.grid[map.goalRow][map.goalCol]='G';
                }
                map.grid[player.row][player.col]='P';
                map.grid[enemy.row][enemy.col]= enemy.dir;


                /*free memory*/
                free(state);
                state=NULL;
            }
        }
        else{   /* jhandle the game*/
            state= (GameState*)malloc(sizeof(GameState));  /*need to allocate memeory for curr state of the gsme*/
            if(state != NULL){

                /*saves the current player,enemy states, treasure location and enemy dir*/
                /*saves curr player*/
                state->playerRow= player.row;
                state->playerCol= player.col;
                state->hasTreasure= player.hasTreasure;
                state->hasGoal= player.hasGoal;
                /*saves the curr enemy*/
                state->enemyRow= enemy.row;
                state->enemyCol= enemy.col;
                /*saves the treasure location*/
                state->treasureRow= map.treasureRow;
                state->treasureCol= map.treasureCol;
                /*saves enemy dir */
                state->enemyDir= enemy.dir;
                state->enemyPrev= enemy.prev;

                /*player movesment*/
                if(movePlayer(&map, &player, input)==1){
                    /*saves to linked list*/
                    push(&undo, state);
                    
                /* 1st enemy move */
                    moveEnemy(&map, &enemy);
                    if(enemy.row==player.row && enemy.col == player.col){   /*check the players loosing condition*/
                        printMap(&map, player.hasTreasure);
                        newSleep(0.25); /*print the win or loose message smoothluy*/
                        printf("You lose !\n");
                        running= 0;
                    }

                /* 2nd enemy move */
                    if(running== 1){   
                        moveEnemy(&map, &enemy);
                        if(enemy.row==player.row && enemy.col==player.col){ /*player being caught*/
                            printMap(&map, player.hasTreasure);
                            newSleep(0.25); /*print the win or loose message smoothluy*/
                            printf("You lose!\n");
                            running= 0;
                        }
                    }

                /* furious */
                    if(running== 1 && player.hasTreasure== 1){
                        moveEnemy(&map, &enemy);

                        if(enemy.row==player.row && enemy.col==player.col){ /*player getting caught condition*/
                            printMap(&map, player.hasTreasure);
                            newSleep(0.25); /*print the win or loose message smoothluy*/
                            printf("You lose!\n");
                            running= 0;
                        }
                    }

                    /*winning condition of the player when reaching goal*/
                    if(running==1 && player.hasGoal==1){
                        printMap(&map, player.hasTreasure);
                        newSleep(0.25); /*print the win or loose message smoothluy*/
                        printf("You win!\n");
                        running= 0;
                    }
                }else{ /*free the unused state is movmnt is invalid*/
                    free(state);
                    state=NULL;
                }
            }
        }
    }   /*freeing the linked list memory*/
        freeList(&undo);
/*FREES THE MAP MEMORY*/
        if (success == 1){
            freeMap(&map);
    }
    return 0;
}
