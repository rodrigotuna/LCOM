#pragma once

#include <lcom/lcf.h>
#include "rtc.h"
#include "sprite.h"

#define SCOREBOARDPATH "/home/lcom/labs/proj/scoreboard.txt"

int check_highscore(int points);

int add_new_score(char * name, int points, int place);

int display_scores();
