#ifndef MOTION_H
#define MOTION_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    int32_t steps1;
    int32_t steps2;
    uint32_t duration_ms;
} motion_move_t;

void motion_init(void);
void motion_enqueue(motion_move_t mv);
void motion_flush(void);
bool motion_busy(void);

#endif
