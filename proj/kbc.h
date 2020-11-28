#pragma once

#include <lcom/lcf.h>
#include <lcom/lab3.h>

#include <minix/sysutil.h>

#include <stdint.h>
#include <stdbool.h>

#include "i8042.h"

int(kbc_issue_cmd)(uint8_t cmd);

int(kbc_issue_arg)(uint8_t cmd);

int(kbc_read)(uint8_t *data);

int (kbc_restore)();

int (kbc_read_cmd)(uint8_t *cmd);

int (kbc_write_cmd)(uint8_t cmd);
