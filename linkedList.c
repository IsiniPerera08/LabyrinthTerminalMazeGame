/*
File: linkedList.c
Name: Isini Ayansa Perera
Student ID: 23601321
Unit: COMP1000(Unix and C programming)
Purpose: to implemt the generic linked list to undo
Last modified: 2026-05-20
*/
#include<stdio.h>
#include<stdlib.h>
#include "linkedList.h"

void push(Node **head, void *data){ /*to insert new node*/
    Node *newNode;

    /*allocating memory for the new node*/
    newNode= (Node*)malloc(sizeof(Node));

    if(newNode != NULL){
        newNode->data= data; /*storing the data inside node*/
        newNode->next= *head; /*point new node to the current*/
        *head= newNode; /*uodating the head to the new node*/
    }
}

void *pop(Node **head){/*removing the latest node frm the linked list*/
    Node *temp;
    void *data;
    data = NULL;

    if(*head !=NULL){/*check if list isnt empty*/
        temp= *head;/*storing the curr head node*/
        data= temp->data;/*storing the node data*/
        *head= temp->next;/*moving the head to next node*/
        free(temp); /*freeing temp*/
    }
    return data;
}
/*free entire linked list memory*/
void freeList(Node **head){
    Node *temp;
    /*continuing until list is empty*/
    while(*head != NULL){
        temp= *head;
        *head= (*head)->next;
        free(temp->data);
        free(temp);
    }
}