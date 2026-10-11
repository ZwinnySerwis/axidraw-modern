/*
 * Pico USB-CDC stub. Compiles once PICO_SDK_PATH and ARM GCC are installed.
 * Protocol handling lives in ebb_parser.c (also used as reference for tools/ebb_sim).
 */

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "tusb.h"
#include "board_pins.h"
#include "ebb_parser.h"

static ebb_state_t g_state;
static char rx_line[256];
static size_t rx_len;

static void pins_init(void) {
    const int outs[] = {
        PIN_M1_STEP, PIN_M1_DIR, PIN_M1_EN,
        PIN_M2_STEP, PIN_M2_DIR, PIN_M2_EN,
        PIN_MS1, PIN_MS2, PIN_MS3,
        PIN_SERVO, PIN_LED,
    };
    for (size_t i = 0; i < sizeof(outs) / sizeof(outs[0]); i++) {
        gpio_init(outs[i]);
        gpio_set_dir(outs[i], GPIO_OUT);
    }
    gpio_put(PIN_M1_EN, 1);
    gpio_put(PIN_M2_EN, 1);
    gpio_init(PIN_PAUSE);
    gpio_set_dir(PIN_PAUSE, GPIO_IN);
    gpio_pull_up(PIN_PAUSE);
}

int main(void) {
    stdio_init_all();
    pins_init();
    ebb_state_init(&g_state);

    char out[256];
    absolute_time_t next_blink = get_absolute_time();
    while (true) {
        tud_task();
        if (time_reached(next_blink)) {
            gpio_xor_mask(1u << PIN_LED);
            next_blink = delayed_by_ms(next_blink, 250);
        }
        if (!tud_cdc_connected() || !tud_cdc_available()) {
            tight_loop_contents();
            continue;
        }
        int32_t ch = tud_cdc_read_char();
        if (ch < 0) continue;
        if (ch == '\n') continue;
        if (ch == '\r' || rx_len >= sizeof(rx_line) - 1) {
            rx_line[rx_len] = 0;
            int extra_ok = ebb_process_line(&g_state, rx_line, out, sizeof(out));
            tud_cdc_write_str(out);
            tud_cdc_write_str("\r\n");
            if (extra_ok) {
                tud_cdc_write_str("OK\r\n");
            }
            tud_cdc_write_flush();
            rx_len = 0;
        } else {
            rx_line[rx_len++] = (char)ch;
        }
    }
}
