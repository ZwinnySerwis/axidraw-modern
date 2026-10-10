#ifndef EBB_PARSER_H
#define EBB_PARSER_H

#include <stddef.h>
#include <stdint.h>

#define EBB_VERSION_STRING "EBBv13_and_above EBB Firmware Version 2.8.1"

typedef struct {
    int motor1_enabled;
    int motor2_enabled;
    int step_mode; /* 1=1/16 .. 5=full, 0=unknown */
    int pen_up;    /* 1 up, 0 down */
    int32_t steps1;
    int32_t steps2;
    uint16_t servo_min;
    uint16_t servo_max;
    uint8_t layer;
    char nickname[17];
    int future_syntax;
} ebb_state_t;

void ebb_state_init(ebb_state_t *st);

/* Process one CR-terminated command without the CR.
 * Writes response (no extra OK) into out, NUL-terminated.
 * Returns 1 if a second "OK" line should be appended (queries with data,
 * and errors). Returns 0 for commands that already reply "OK", and for
 * V/PI/QG/QM (plotink does not read a trailing OK for those).
 */
int ebb_process_line(ebb_state_t *st, const char *line, char *out, size_t out_sz);

#endif
