#include "scoreboard.h"

#include "rtc.h"

int check_highscore(int points){
  FILE *scoreboard;
  scoreboard = fopen(SCOREBOARDPATH, "r+");

  char * line = NULL;
  char * score_str = NULL;
  char delim[] = "   ";

  int score = -1, place = 1, counter = 0;
  size_t len = 0;


  while(getline(&line,&len,scoreboard) != -1){
    score_str = strtok(line,delim);
    score = atoi(score_str);
    if(points > score){
      fclose(scoreboard);
      return place;
    }
    place++;
    counter++;
  }

  if(counter < 4){
    fclose(scoreboard);
    return place;
  }

  fclose(scoreboard);
  return 0;
}

int add_new_score(char * name, int points, int place){
  FILE *scoreboard;
  scoreboard = fopen(SCOREBOARDPATH, "r+");

  char * line = NULL;
  char new_score[50];
  char content[4][50] = {""};
  int index = 0;
  size_t len = 0;

  uint8_t date[6];
  if(rtc_get_date(date)) return 1;

  while(getline(&line,&len,scoreboard) != -1){
    strcpy(content[index],line);
    index++;
  }

  fclose(scoreboard);
  scoreboard = fopen(SCOREBOARDPATH, "w");

  sprintf(new_score,"%d//%02d:%02d:%02d %02d-%02d-%02d//%s\n", points, date[0], date[1], date[2],date[3],date[4],date[5],name);

  for(int i = 3; i >= place; i--){
    strcpy(content[i],content[i-1]); 
  }
  strcpy(content[place-1],new_score);

  for(int i = 0; i < 4; i++){
    fprintf(scoreboard,"%s",content[i]);
  }

  fclose(scoreboard);
  return 0;
}

int display_scores(sprite_t * font){
  FILE *scoreboard;
  scoreboard = fopen(SCOREBOARDPATH, "r+");

  char * line = NULL;
  char * score_str = NULL;
  char delim[] = "//";
  size_t len = 0;

   while(getline(&line,&len,scoreboard) != -1){
    score_str = strtok(line,delim);
    if(print_string(score_str,font,652,font->y_pos)) return 1;
    score_str = strtok(NULL,delim);
    if(print_string(score_str,font,294,font->y_pos)) return 1;
    score_str = strtok(NULL,delim);
    if(print_string(score_str,font,80,font->y_pos)) return 1;
    font->y_pos += 74;
  }

  fclose(scoreboard);
  return 0;
}

char * write_name(char * name, uint8_t scancode){
  if(scancode >= 0 && scancode <= 50){
    if(scancode == BACKSPACE_MAKECODE) name[strlen(name)-1] = '\0';
    else strcat(name,keycodes[scancode]);
  }
  return name;
}

