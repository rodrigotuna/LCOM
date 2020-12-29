#pragma once

#include <lcom/lcf.h>
#include "rtc.h"
#include "sprite.h"

#define SCOREBOARDPATH "/home/lcom/labs/proj/scoreboard.txt"
#define BACKSPACE_MAKECODE 0x0E

static char keycodes[51][2] = {"","","1","2","3","4","5","6","7","8","9","0","","","","","Q","W","E","R","T","Y","U","I","O","P","","","","","A","S","D","F","G","H","J","K","L","","","","","","Z","x","C","V","B","N","M"};

int check_highscore(int points);

int add_new_score(char * name, int points, int place);

int display_scores();

char * write_name(char * name, uint8_t scancode);
