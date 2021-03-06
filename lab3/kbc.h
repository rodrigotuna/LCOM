#include <lcom/lcf.h>
#include <lcom/lab3.h>

#include <minix/sysutil.h>

#include <stdint.h>
#include <stdbool.h>

#include "i8042.h"

int hook_id;
uint8_t scancode[2];
uint8_t size;
bool code_completed;


int(kbc_issue_cmd)(uint8_t cmd);

int(kbc_issue_cmd_b)(uint8_t cmd);

int(kbc_read)(uint8_t *data);

int (kbc_restore)();

int (kbc_read_cmd)(uint8_t *cmd);

int (kbc_write_cmd)(uint8_t cmd);
