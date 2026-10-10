#ifndef BOARD_PINS_H
#define BOARD_PINS_H

/* Raspberry Pi Pico GPIO numbers. See hardware/PINOUT.md */

#define PIN_M1_STEP 2
#define PIN_M1_DIR  3
#define PIN_M1_EN   4 /* active low */

#define PIN_M2_STEP 5
#define PIN_M2_DIR  6
#define PIN_M2_EN   7 /* active low */

#define PIN_MS1 10
#define PIN_MS2 11
#define PIN_MS3 12

#define PIN_PAUSE 14
#define PIN_SERVO 15
#define PIN_LED   25
#define PIN_VMOT_ADC 26

#endif
