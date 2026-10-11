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

#define PIN_M3_EN 13 /* active low; STEP/DIR shared with motor2 on PCB */

#define PIN_PAUSE 14
#define PIN_SERVO 15
#define PIN_LED   25
#define PIN_VMOT_ADC 28 /* ADC2; GP26/27 reserved for I2C1 */

/* Reserved — not driven in MVP firmware */
#define PIN_ENC1_SDA 0  /* I2C0, AS5600 motor1 */
#define PIN_ENC1_SCL 1
#define PIN_TMC_TX   8
#define PIN_TMC_RX   9
#define PIN_IMU_MISO 16 /* SPI0, LSM6DS3TR-C */
#define PIN_IMU_CS   17
#define PIN_IMU_SCK  18
#define PIN_IMU_MOSI 19
#define PIN_SPARE_20 20
#define PIN_SPARE_21 21
#define PIN_IMU_INT1 22
#define PIN_ENC2_SDA 26 /* I2C1, AS5600 motor2 */
#define PIN_ENC2_SCL 27

#endif
