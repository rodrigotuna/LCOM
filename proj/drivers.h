#pragma once

#include <lcom/lcf.h>

#include "keyboard.h"
#include "mouse.h"
#include "video.h"

#define TIMER_IRQ_SET BIT(0)
#define KB_IRQ_SET BIT(1)
#define MOUSE_IRQ_SET BIT(12)
#define UART_IRQ_SET BIT(4)

int subscribe_all();

int unsubscribe_all();

uint32_t get_interrupts();

int init_all();

int reset_all();
