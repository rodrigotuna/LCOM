#pragma once

#include <lcom/lcf.h>
#include "rtc.h"

#define SCOREBOARDPATH "/home/labs/proj/scoreboard.txt"

int check_highscore(int points);

int add_new_score(char * name, int points, int place);

int display_scores();
