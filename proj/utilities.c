#include "utilities.h"

int (util_get_LSB)(uint16_t val, uint8_t *lsb) {
  if(lsb == NULL) return 1;

  *lsb = val;
  return 0;
}

int (util_get_MSB)(uint16_t val, uint8_t *msb) {
  if (msb == NULL) return 1;

  *msb = val >> 8;
  return 0;
}

#ifdef LAB3
  uint32_t sys_counter = 0;
 #endif

int (util_sys_inb)(int port, uint8_t *value) {
  if (value == NULL) return 1;

  uint32_t var;
  
  if(sys_inb(port,&var) != OK) return 1;

  *value = var;
  #ifdef LAB3
    sys_counter++;
  #endif
  return 0;
}

uint16_t min(uint16_t a, uint16_t b){
  if(a < b) return a;
  return b;
}

int16_t max(int16_t a, int16_t b){
  if(a > b) return a;
  return b;
}

queue_t * create_queue(){
  uint8_t *arr = malloc(100*sizeof(uint8_t));
  queue_t *queue = malloc(sizeof(queue_t));
  queue->sz = 0;
  queue->arr = arr;
  return queue;
}

void destroy_queue(queue_t * q){
  free(q->arr);
  free(q);
}

void push(queue_t *q, uint8_t c){
  q->arr[q->sz] = c;
  q->sz++;
}

uint8_t top(queue_t *q){
  return q->arr[0];
}

void pop(queue_t *q){
  if(q->sz== 0){
		return;
	}
	else{
		int i;
		for(i=0;i<q->sz-1;i++){
			q->arr[i]=q->arr[i+1];
		}
		q->sz--;
	}
}

bool empty(queue_t *q){
  return q->sz == 0;
}

void int_to_char(int value, char * str){
  sprintf(str, "%d", value);
}
