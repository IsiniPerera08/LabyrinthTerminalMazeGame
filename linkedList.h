#ifndef LINKEDLIST_H
#define LINKEDLIST_H


/*to store player position,player status,enemy position,
treasure location,enemy dir and prev tile*/
typedef struct{ 
    int playerRow;
    int playerCol;
    int hasTreasure;
    int hasGoal;
    int enemyRow;
    int enemyCol;
    int treasureRow;
    int treasureCol;
    char enemyDir;
    char enemyPrev;
}GameState;
 /*generic linked list*/
typedef struct Node{
    void *data; /*pointer to stored dataa*/
    struct Node * next; /*pointer for the nextNode*/
}Node;

void push(Node **head, void * data); /*inserting to beginging of the linked list*/
void *pop(Node **head); /*removing the last node from the linked list*/
void freeList(Node **head); /*freeing all the nodes*/

#endif
