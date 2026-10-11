/*
 * USB CDC EiBotBoard. EM → EN (active low) + MS1–3.
 * SM/XM → STEP/DIR on core1. MOTION_STEP_DIV scales full-step proto.
 */

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/stdio_usb.h"
#include "board_pins.h"
#include "ebb_parser.h"
#include "motion.h"

static ebb_state_t g_state;
static char rx_line[256];
static size_t rx_len;

static void apply_enables(void) {
    gpio_put(PIN_M1_EN, g_state.motor1_enabled ? 0 : 1);
    gpio_put(PIN_M2_EN, g_state.motor2_enabled ? 0 : 1);
    gpio_put(PIN_M3_EN, g_state.motor2_enabled ? 0 : 1);
}

/* A4988/DRV8825: EM Enable1 1=1/16 … 5=full. Plugin always uses 1/16. */
static void apply_microstep(void) {
    int ms1 = 0, ms2 = 0, ms3 = 0;
    switch (g_state.step_mode) {
        case 1: ms1 = ms2 = ms3 = 1; break;
        case 2: ms1 = ms2 = 1; break;
        case 3: ms2 = 1; break;
        case 4: ms1 = 1; break;
        default: break;
    }
    gpio_put(PIN_MS1, ms1);
    gpio_put(PIN_MS2, ms2);
    gpio_put(PIN_MS3, ms3);
}

static void pins_init(void) {
    const int outs[] = {
        PIN_M1_STEP, PIN_M1_DIR, PIN_M1_EN,
        PIN_M2_STEP, PIN_M2_DIR, PIN_M2_EN,
        PIN_MS1, PIN_MS2, PIN_MS3, PIN_M3_EN,
        PIN_SERVO, PIN_LED,
    };
    for (size_t i = 0; i < sizeof(outs) / sizeof(outs[0]); i++) {
        gpio_init(outs[i]);
        gpio_set_dir(outs[i], GPIO_OUT);
    }
    gpio_put(PIN_M1_STEP, 0);
    gpio_put(PIN_M2_STEP, 0);
    gpio_init(PIN_PAUSE);
    gpio_set_dir(PIN_PAUSE, GPIO_IN);
    gpio_pull_up(PIN_PAUSE);
}

static void cdc_write(const char *s) {
    fwrite(s, 1, strlen(s), stdout);
    fflush(stdout);
}

int main(void) {
    stdio_init_all();
    stdio_set_translate_crlf(&stdio_usb, false);
    pins_init();
    ebb_state_init(&g_state);
    apply_microstep();
    apply_enables();
    motion_init();

    char out[256];
    uint32_t last_blink = 0;
    int led = 0;

    while (true) {
        uint32_t now = to_ms_since_boot(get_absolute_time());
        if (now - last_blink >= 250) {
            last_blink = now;
            led = !led;
            gpio_put(PIN_LED, led);
        }

        int ch = getchar_timeout_us(0);
        if (ch == PICO_ERROR_TIMEOUT) {
            tight_loop_contents();
            continue;
        }
        if (ch == '\n') continue;
        if (ch == '\r' || rx_len >= sizeof(rx_line) - 1) {
            rx_line[rx_len] = 0;
            int extra_ok = ebb_process_line(&g_state, rx_line, out, sizeof(out));
            apply_microstep();
            apply_enables();
            if (g_state.flush_motion) {
                motion_flush();
            }
            if (g_state.has_move) {
                motion_move_t mv = {
                    .steps1 = g_state.move_s1,
                    .steps2 = g_state.move_s2,
                    .duration_ms = g_state.move_ms,
                };
                motion_enqueue(mv);
            }
            cdc_write(out);
            cdc_write("\r\n");
            if (extra_ok) {
                cdc_write("OK\r\n");
            }
            rx_len = 0;
        } else {
            rx_line[rx_len++] = (char)ch;
        }
    }
}
