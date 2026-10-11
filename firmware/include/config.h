#ifndef FIRMWARE_CONFIG_H
#define FIRMWARE_CONFIG_H

/*
 * Tunables for the Pico proto. Edit this file, rebuild UF2, copy to RPI-RP2.
 *
 * Speed, work area, steps/mm, and X/Y kinematics live in the Inkscape
 * AxiDraw plugin (Options tab + axidraw_conf.py), not here. Firmware only
 * plays STEP/DIR for the SM/XM pulses the host already computed.
 */

/* Plugin sends 1/16. A4988 with MS1–3 floating = full step.
 * 16T GT2 + 200 steps/rev matches AxiDraw mm after /16.
 * Set to 1 when MS1/MS2/MS3 are tied to 3V3. */
#define MOTION_STEP_DIV 16

/* 1 = invert that motor DIR (walk goes the wrong way). */
#define INVERT_DIR_M1 0
#define INVERT_DIR_M2 0

/* 1 = swap EBB motor1/motor2 (plugin X/Y native axes swapped). */
#define SWAP_MOTORS 0

/* Cap 25 kHz (EBB). Raise only after 1/16 is wired. */
#define MIN_STEP_US 40

#define STEP_PULSE_US 5
#define DIR_SETUP_US 10

#endif
