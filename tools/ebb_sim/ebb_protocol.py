"""Software EiBotBoard: same ASCII protocol the Inkscape plugin speaks.

This is the golden model for firmware/. Run without hardware via pytest,
or over a COM port once USB CDC is up.
"""

from __future__ import annotations

VERSION = "EBBv13_and_above EBB Firmware Version 2.8.1"

# Queries that plotink.ebb_serial.query() does not read an extra OK line for.
NO_EXTRA_OK = {"v", "a", "i", "mr", "pi", "qm", "qg"}


def _ms_pins(step_mode: int) -> tuple[int, int, int]:
    mapping = {
        1: (1, 1, 1),  # 1/16
        2: (1, 1, 0),  # 1/8
        3: (0, 1, 0),  # 1/4
        4: (1, 0, 0),  # 1/2
        5: (0, 0, 0),  # full
    }
    return mapping.get(step_mode, (1, 1, 1))


class EbbDevice:
    def __init__(self) -> None:
        self.motor1_enabled = False
        self.motor2_enabled = False
        self.step_mode = 1
        self.pen_up = True
        self.steps1 = 0
        self.steps2 = 0
        self.servo_min = 12000
        self.servo_max = 16000
        self.servo_rate_up = 0
        self.servo_rate_down = 0
        self.layer = 0
        self.nickname = ""
        self.button = 0
        self.voltage_counts = 400
        self.current_counts = 0
        self.gpio_b = [0] * 8

    def handle(self, raw: str) -> tuple[str, bool]:
        """Return (first_line, extra_ok_needed). First line has no CR/LF."""
        line = raw.strip().strip("\x00")
        if not line:
            return ("!4 Err: Missing parameter(s)", True)
        parts = line.split(",")
        cmd = parts[0].strip().upper()
        args = [p.strip() for p in parts[1:]]
        body = self._dispatch(cmd, args)
        # Commands already reply "OK" (one line). plotink.command() reads that
        # single line. Queries listed in NO_EXTRA_OK return data only. All other
        # queries (and errors) get a following OK line that query() consumes.
        if cmd.lower() in NO_EXTRA_OK:
            extra = False
        elif body == "OK":
            extra = False
        else:
            extra = True
        return body, extra

    def handle_session(self, raw: str) -> str:
        """Full wire payload including line endings, legacy mode."""
        body, extra = self.handle(raw)
        out = body + "\r\n"
        if extra:
            out += "OK\r\n"
        return out

    def _dispatch(self, cmd: str, args: list[str]) -> str:
        if cmd == "V":
            return VERSION
        if cmd == "EM":
            return self._em(args)
        if cmd == "SM":
            return self._sm(args)
        if cmd == "XM":
            return self._xm(args)
        if cmd == "SP":
            return self._sp(args)
        if cmd == "TP":
            self.pen_up = not self.pen_up
            return "OK"
        if cmd == "SC":
            return self._sc(args)
        if cmd == "QP":
            return "1" if self.pen_up else "0"
        if cmd == "QB":
            return str(self.button)
        if cmd == "QS":
            return f"{self.steps1},{self.steps2}"
        if cmd == "CS":
            self.steps1 = 0
            self.steps2 = 0
            return "OK"
        if cmd == "QC":
            return f"{self.current_counts},{self.voltage_counts}"
        if cmd == "QG":
            return "00"
        if cmd == "QM":
            return f"QM,{int(self.motor1_enabled)},{int(self.motor2_enabled)},0,0"
        if cmd == "PI":
            return self._pi(args)
        if cmd == "PO":
            return self._po(args)
        if cmd == "PD":
            return "OK"
        if cmd == "SL":
            if not args:
                return "!4 Err: Missing parameter(s)"
            self.layer = int(args[0]) & 0xFF
            return "OK"
        if cmd == "QL":
            return str(self.layer)
        if cmd in {"CU", "SR", "ES", "R", "HM", "ST", "RB"}:
            if cmd == "ST" and args:
                self.nickname = args[0][:16]
            if cmd == "ES":
                return "0"
            return "OK"
        if cmd == "QT":
            return self.nickname
        return f"!8 Err: unrecognized command: '{cmd}'"

    def _em(self, args: list[str]) -> str:
        if not args:
            return "!4 Err: Missing parameter(s)"
        e1 = int(args[0])
        if e1 == 0:
            self.motor1_enabled = False
        elif 1 <= e1 <= 5:
            self.step_mode = e1
            self.motor1_enabled = True
        if len(args) > 1:
            e2 = int(args[1])
            self.motor2_enabled = e2 != 0
        return "OK"

    def _sm(self, args: list[str]) -> str:
        if len(args) < 2:
            return "!4 Err: Missing parameter(s)"
        duration = int(args[0])
        if duration <= 0:
            return "!9 Err: Invalid parameter value"
        s1 = int(args[1])
        s2 = int(args[2]) if len(args) > 2 else 0
        self.steps1 += s1
        self.steps2 += s2
        if s1 or s2:
            self.motor1_enabled = True
            self.motor2_enabled = True
        return "OK"

    def _xm(self, args: list[str]) -> str:
        if len(args) < 3:
            return "!4 Err: Missing parameter(s)"
        a = int(args[1])
        b = int(args[2])
        return self._sm([args[0], str(a + b), str(a - b)])

    def _sp(self, args: list[str]) -> str:
        if not args:
            return "!4 Err: Missing parameter(s)"
        val = int(args[0])
        if val == 0:
            self.pen_up = False
        else:
            self.pen_up = True
        return "OK"

    def _sc(self, args: list[str]) -> str:
        if len(args) < 2:
            return "!4 Err: Missing parameter(s)"
        key, value = int(args[0]), int(args[1])
        if key == 4:
            self.servo_min = value
        elif key == 5:
            self.servo_max = value
        elif key == 11:
            self.servo_rate_up = value
        elif key == 12:
            self.servo_rate_down = value
        return "OK"

    def _pi(self, args: list[str]) -> str:
        if len(args) < 2:
            return "!4 Err: Missing parameter(s)"
        port = args[0].upper()
        bit = int(args[1])
        ms1, ms2, ms3 = _ms_pins(self.step_mode)
        level = 0
        if port == "E" and bit == 0:
            level = 0 if self.motor1_enabled else 1
        elif port == "C" and bit == 1:
            level = 0 if self.motor2_enabled else 1
        elif port == "E" and bit == 2:
            level = ms1
        elif port == "E" and bit == 1:
            level = ms2
        elif port == "A" and bit == 6:
            level = ms3
        return f"PI,{level}"

    def _po(self, args: list[str]) -> str:
        if len(args) >= 3 and args[0].upper() == "B":
            pin = int(args[1])
            if 0 <= pin < 8:
                self.gpio_b[pin] = int(args[2])
        return "OK"
