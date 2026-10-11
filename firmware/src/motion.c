#include "motion.h"

#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/util/queue.h"
#include "hardware/gpio.h"
#include "board_pins.h"
#include "config.h"

#define MOTION_Q_LEN 16

static queue_t g_q;
static volatile bool g_flush;

static void pulse(int pin) {
    gpio_put(pin, 1);
    busy_wait_us_32(STEP_PULSE_US);
    gpio_put(pin, 0);
}

static void exec_move(motion_move_t mv) {
    int32_t s1 = mv.steps1;
    int32_t s2 = mv.steps2;
    gpio_put(PIN_M1_DIR, (s1 < 0) != (INVERT_DIR_M1 != 0));
    gpio_put(PIN_M2_DIR, (s2 < 0) != (INVERT_DIR_M2 != 0));
    if (s1 < 0) s1 = -s1;
    if (s2 < 0) s2 = -s2;
    busy_wait_us_32(DIR_SETUP_US);

    uint32_t dur_us = mv.duration_ms * 1000u;
    if (dur_us > 100000u * 1000u) {
        dur_us = 100000u * 1000u;
    }

    if (s1 == 0 && s2 == 0) {
        if (dur_us) {
            sleep_us(dur_us);
        }
        return;
    }

    uint32_t n = (uint32_t)(s1 > s2 ? s1 : s2);
    uint32_t min_us = n * MIN_STEP_US;
    if (dur_us < min_us) {
        dur_us = min_us;
    }

    int32_t e1 = 0;
    int32_t e2 = 0;
    uint32_t t0 = time_us_32();
    for (uint32_t i = 0; i < n; i++) {
        if (g_flush) {
            return;
        }
        uint32_t due = t0 + (uint32_t)(((uint64_t)(i + 1) * dur_us) / n);
        while ((int32_t)(time_us_32() - due) < 0) {
            tight_loop_contents();
        }
        e1 += s1;
        e2 += s2;
        if (e1 >= (int32_t)n) {
            e1 -= (int32_t)n;
            pulse(PIN_M1_STEP);
        }
        if (e2 >= (int32_t)n) {
            e2 -= (int32_t)n;
            pulse(PIN_M2_STEP);
        }
    }
}

static void core1_entry(void) {
    motion_move_t mv;
    while (true) {
        if (g_flush) {
            motion_move_t dump;
            while (queue_try_remove(&g_q, &dump)) {
            }
            g_flush = false;
        }
        if (queue_try_remove(&g_q, &mv)) {
            exec_move(mv);
        } else {
            tight_loop_contents();
        }
    }
}

void motion_init(void) {
    queue_init(&g_q, sizeof(motion_move_t), MOTION_Q_LEN);
    g_flush = false;
    gpio_put(PIN_M1_STEP, 0);
    gpio_put(PIN_M2_STEP, 0);
    multicore_launch_core1(core1_entry);
}

static int32_t scale_steps(int32_t s) {
#if MOTION_STEP_DIV <= 1
    return s;
#else
    int32_t d = MOTION_STEP_DIV;
    if (s >= 0) {
        return (s + d / 2) / d;
    }
    return -((-s + d / 2) / d);
#endif
}

void motion_enqueue(motion_move_t mv) {
    int32_t s1 = scale_steps(mv.steps1);
    int32_t s2 = scale_steps(mv.steps2);
#if SWAP_MOTORS
    mv.steps1 = s2;
    mv.steps2 = s1;
#else
    mv.steps1 = s1;
    mv.steps2 = s2;
#endif
    queue_add_blocking(&g_q, &mv);
}

void motion_flush(void) {
    g_flush = true;
    motion_move_t dump;
    while (queue_try_remove(&g_q, &dump)) {
    }
}

bool motion_busy(void) {
    return !queue_is_empty(&g_q);
}
