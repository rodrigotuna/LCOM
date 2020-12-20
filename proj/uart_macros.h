#pragma once

/* IRQ LINES*/
#define COM1_IRQ 4
#define COM2_IRQ 3

/*ADDRESSES*/
#define COM1_BASE_ADDR 0x3F8
#define COM2_BASE_ADDR 0x2F8

#define RBR 0
#define THR 0
#define IER 1
#define IIR 2
#define FCR 2
#define LCR 3
#define MCR 4
#define LSR 5
#define MSR 6
#define SR  7

#define DDL 0
#define DLM 1
