#include "scoreboard.h"

int check_highscore(int points){
  /*FILE *scoreboard;
  if(scoreboard = fopen(SCOREBOARDPATH, "r+")) return 0;

  char * line = NULL;
  char * score_str = NULL;
  char delim[] = "   ";

  int score = -1, place = 1, counter = 0;
  size_t len = 0;

  while(getline(&line,&len,scoreboard) != -1 && size < 4){
    score_str = strtok(&line,delim);
    score = atoi(score_str);
    if(points > score) return place;
    place++;
    counter++;
  }

  if(counter < 4) return place;

  fclose(scoreboard);*/
  return 0;
}

int add_new_score(char * name, int points, int place){
  /*FILE *scoreboard;
  if(scoreboard = fopen(SCOREBOARDPATH, "r+")) return 1;

  char * line = NULL;
  char * content = NULL;
  int index = 0;
  size_t len = 0;

  uint8_t date[6];
  if(rtc_get_date(date)) return 1;

  while(getline(&line,&len,scoreboard) != -1){
    content[index] = line;
    if(index == (place - 1)){
      fprintf(scoreboard,"%s   %02d:%02d:%02d  %02d-%02d-%02d   %d",                            name, date[0], date[1], date[2], date[3],date[4],date[5],points); 
    }
    index++;
  }



  fclose(scoreboard);*/
  return 0;
}

int display_scores(){
  return 0;
}
