/*
File: terminal.c
Name: Isini Ayansa Perera
Student ID: 23601321
Unit: COMP1000(Unix and C programming)
Purpose: allows single key inputs to be entered without having click enter
*/
#include<stdio.h>
#include<termios.h>
#include"terminal.h"

void disableBuffer()
{
    struct termios mode;

    tcgetattr(0, &mode);
    mode.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(0, TCSANOW, &mode);
}

void enableBuffer()
{
    struct termios mode;

    tcgetattr(0, &mode);
    mode.c_lflag |= (ECHO | ICANON);
    tcsetattr(0, TCSANOW, &mode);
}
