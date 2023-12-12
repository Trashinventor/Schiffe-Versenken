#pragma once

#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>

#define END_TEXT "\033[m""\033[94m"
#define COLOR_YELLOW_BOLD "\033[1;33m"
#define COLOR_BOLD_SLOW_BLINKING_BRIGHT_BLUE  "\e[1;5;94m"
#define COLOR_RED_BOLD   "\033[1;31m"
#define BOLD "\033[1m"
#define UEBERSCHRIFT "\e[1;4m"
#define COLOR_BRIGHT_BLUE "\e[94m"
#define EBENE_1 2

#ifdef __cplusplus
extern "C" {
#endif

extern void test(void);
extern void startupscreen(void);
void wait(unsigned int);
int menuPrint(int);
int spielfeld(char*, int, int, char*, char*);
int menu(void);
char* timer(time_t);
void SchiffSetzen(int, int, int, char*);
int checkPos(int, int, int, char*);
int coordsToField(char , int );
void clear(void);
void TextCentered(char[],short,int,char[]);
void setDecMode(void);
void drawBox(int,int);
char* Countdown(time_t, time_t);
void WinnerScreen(void);
void LoserScreen(void);
void initSpielfeld(void);
void UserInput();
void undecidedScreen(void);

#ifdef __cplusplus
}
#endif
