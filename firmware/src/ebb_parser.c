#include "ebb_parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void ebb_state_init(ebb_state_t *st) {
    memset(st, 0, sizeof(*st));
    st->pen_up = 1;
    st->step_mode = 1;
    st->servo_min = 12000;
    st->servo_max = 16000;
}

static void upper_cmd(char *dst, const char *src, size_t n) {
    size_t i = 0;
    while (src[i] && i + 1 < n) {
        dst[i] = (char)toupper((unsigned char)src[i]);
        i++;
    }
    dst[i] = 0;
}

static int skip_trailing_ok(const char *cmd) {
    /* plotink.ebb_serial.query does not consume a second OK line for these. */
    return strcmp(cmd, "V") == 0 || strcmp(cmd, "A") == 0 ||
           strcmp(cmd, "I") == 0 || strcmp(cmd, "MR") == 0 ||
           strcmp(cmd, "PI") == 0 || strcmp(cmd, "QM") == 0 ||
           strcmp(cmd, "QG") == 0;
}

static int reply_extra_ok(const char *cmd, const char *out) {
    if (skip_trailing_ok(cmd)) return 0;
    if (strcmp(out, "OK") == 0) return 0;
    return 1;
}

int ebb_process_line(ebb_state_t *st, const char *line, char *out, size_t out_sz) {
    char buf[256];
    char cmd[8] = {0};
    st->has_move = 0;
    st->flush_motion = 0;
    upper_cmd(buf, line, sizeof(buf));

    char *comma = strchr(buf, ',');
    if (comma) {
        size_t n = (size_t)(comma - buf);
        if (n >= sizeof(cmd)) n = sizeof(cmd) - 1;
        memcpy(cmd, buf, n);
        cmd[n] = 0;
    } else {
        strncpy(cmd, buf, sizeof(cmd) - 1);
    }

    if (strcmp(cmd, "V") == 0) {
        snprintf(out, out_sz, "%s", EBB_VERSION_STRING);
        return reply_extra_ok(cmd, out);
    }

    if (strcmp(cmd, "EM") == 0) {
        int e1 = 0, e2 = -1;
        sscanf(buf, "EM,%d,%d", &e1, &e2);
        if (e1 >= 1 && e1 <= 5) {
            st->step_mode = e1;
            st->motor1_enabled = 1;
        } else {
            st->motor1_enabled = 0;
        }
        if (e2 >= 0) {
            st->motor2_enabled = (e2 != 0);
        }
        snprintf(out, out_sz, "OK");
        return reply_extra_ok(cmd, out);
    }

    if (strcmp(cmd, "SM") == 0) {
        long dur = 0, s1 = 0, s2 = 0;
        sscanf(buf, "SM,%ld,%ld,%ld", &dur, &s1, &s2);
        if (dur < 0) dur = 0;
        st->steps1 += (int32_t)s1;
        st->steps2 += (int32_t)s2;
        if (s1 || s2) {
            st->motor1_enabled = 1;
            st->motor2_enabled = 1;
        }
        st->has_move = 1;
        st->move_s1 = (int32_t)s1;
        st->move_s2 = (int32_t)s2;
        st->move_ms = (uint32_t)dur;
        snprintf(out, out_sz, "OK");
        return reply_extra_ok(cmd, out);
    }

    if (strcmp(cmd, "XM") == 0) {
        long dur = 0, a = 0, b = 0;
        sscanf(buf, "XM,%ld,%ld,%ld", &dur, &a, &b);
        if (dur < 0) dur = 0;
        int32_t s1 = (int32_t)(a + b);
        int32_t s2 = (int32_t)(a - b);
        st->steps1 += s1;
        st->steps2 += s2;
        st->motor1_enabled = 1;
        st->motor2_enabled = 1;
        st->has_move = 1;
        st->move_s1 = s1;
        st->move_s2 = s2;
        st->move_ms = (uint32_t)dur;
        snprintf(out, out_sz, "OK");
        return reply_extra_ok(cmd, out);
    }

    if (strcmp(cmd, "SP") == 0) {
        int val = 1;
        sscanf(buf, "SP,%d", &val);
        if (val == 0) st->pen_up = 0;
        else st->pen_up = 1;
        snprintf(out, out_sz, "OK");
        return reply_extra_ok(cmd, out);
    }

    if (strcmp(cmd, "TP") == 0) {
        st->pen_up = st->pen_up ? 0 : 1;
        snprintf(out, out_sz, "OK");
        return reply_extra_ok(cmd, out);
    }

    if (strcmp(cmd, "SC") == 0) {
        int k = 0, v = 0;
        sscanf(buf, "SC,%d,%d", &k, &v);
        if (k == 4) st->servo_min = (uint16_t)v;
        if (k == 5) st->servo_max = (uint16_t)v;
        snprintf(out, out_sz, "OK");
        return reply_extra_ok(cmd, out);
    }

    if (strcmp(cmd, "QP") == 0) {
        snprintf(out, out_sz, "%d", st->pen_up);
        return reply_extra_ok(cmd, out);
    }

    if (strcmp(cmd, "QB") == 0) {
        snprintf(out, out_sz, "0");
        return reply_extra_ok(cmd, out);
    }

    if (strcmp(cmd, "QS") == 0) {
        snprintf(out, out_sz, "%ld,%ld", (long)st->steps1, (long)st->steps2);
        return reply_extra_ok(cmd, out);
    }

    if (strcmp(cmd, "CS") == 0) {
        st->steps1 = 0;
        st->steps2 = 0;
        snprintf(out, out_sz, "OK");
        return reply_extra_ok(cmd, out);
    }

    if (strcmp(cmd, "QC") == 0) {
        snprintf(out, out_sz, "0,400");
        return reply_extra_ok(cmd, out);
    }

    if (strcmp(cmd, "QG") == 0) {
        snprintf(out, out_sz, "00");
        return reply_extra_ok(cmd, out);
    }

    if (strcmp(cmd, "QM") == 0) {
        snprintf(out, out_sz, "QM,%d,%d,0,0", st->motor1_enabled, st->motor2_enabled);
        return reply_extra_ok(cmd, out);
    }

    if (strcmp(cmd, "PI") == 0) {
        /* Fake PIC pin levels so query_enable_motors() works. */
        int ms1 = 0, ms2 = 0, ms3 = 0;
        switch (st->step_mode) {
            case 1: ms1 = ms2 = ms3 = 1; break;
            case 2: ms1 = ms2 = 1; break;
            case 3: ms2 = 1; break;
            case 4: ms1 = 1; break;
            default: break;
        }
        char port = 0;
        int bit = 0;
        sscanf(buf, "PI,%c,%d", &port, &bit);
        int level = 0;
        if (port == 'E' && bit == 0) level = st->motor1_enabled ? 0 : 1;
        else if (port == 'C' && bit == 1) level = st->motor2_enabled ? 0 : 1;
        else if (port == 'E' && bit == 2) level = ms1;
        else if (port == 'E' && bit == 1) level = ms2;
        else if (port == 'A' && bit == 6) level = ms3;
        snprintf(out, out_sz, "PI,%d", level);
        return reply_extra_ok(cmd, out);
    }

    if (strcmp(cmd, "SL") == 0) {
        int v = 0;
        sscanf(buf, "SL,%d", &v);
        st->layer = (uint8_t)v;
        snprintf(out, out_sz, "OK");
        return reply_extra_ok(cmd, out);
    }

    if (strcmp(cmd, "QL") == 0) {
        snprintf(out, out_sz, "%u", (unsigned)st->layer);
        return reply_extra_ok(cmd, out);
    }

    if (strcmp(cmd, "ES") == 0) {
        st->flush_motion = 1;
        snprintf(out, out_sz, "OK");
        return reply_extra_ok(cmd, out);
    }

    if (strcmp(cmd, "PO") == 0 || strcmp(cmd, "PD") == 0 ||
        strcmp(cmd, "CU") == 0 || strcmp(cmd, "SR") == 0 ||
        strcmp(cmd, "R") == 0 ||
        strcmp(cmd, "HM") == 0 || strcmp(cmd, "ST") == 0) {
        snprintf(out, out_sz, "OK");
        return reply_extra_ok(cmd, out);
    }

    if (strcmp(cmd, "QT") == 0) {
        snprintf(out, out_sz, "%s", st->nickname);
        return reply_extra_ok(cmd, out);
    }

    snprintf(out, out_sz, "!8 Err: unrecognized command: '%s'", cmd);
    return 1;
}
