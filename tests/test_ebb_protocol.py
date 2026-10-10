import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

from ebb_sim.ebb_protocol import VERSION, EbbDevice  # noqa: E402


def test_version_starts_with_ebb_and_has_firmware_tag():
    dev = EbbDevice()
    body, extra = dev.handle("v")
    assert body.startswith("EBB")
    assert "Firmware Version 2.8.1" in body
    assert body == VERSION
    assert extra is False


def test_sm_accumulates_and_xm_mixes_axes():
    dev = EbbDevice()
    assert dev.handle("SM,1000,250,-766")[0] == "OK"
    assert (dev.steps1, dev.steps2) == (250, -766)
    dev.handle("CS")
    # XM: motor1 = A+B, motor2 = A-B
    dev.handle("XM,1000,550,-1234")
    assert dev.steps1 == 550 + (-1234)
    assert dev.steps2 == 550 - (-1234)


def test_pen_and_servo_config():
    dev = EbbDevice()
    assert dev.handle("QP")[0] == "1"
    assert dev.handle("SP,0,150")[0] == "OK"
    assert dev.handle("QP")[0] == "0"
    dev.handle("SC,4,8000")
    dev.handle("SC,5,20000")
    assert dev.servo_min == 8000
    assert dev.servo_max == 20000


def test_em_and_pi_microstep_pins_match_plotink():
    dev = EbbDevice()
    dev.handle("EM,1,1")
    assert dev.handle("PI,E,0")[0] == "PI,0"  # enable active low
    assert dev.handle("PI,C,1")[0] == "PI,0"
    assert dev.handle("PI,E,2")[0] == "PI,1"  # MS1
    assert dev.handle("PI,E,1")[0] == "PI,1"  # MS2
    assert dev.handle("PI,A,6")[0] == "PI,1"  # MS3 → 1/16
    dev.handle("EM,0,0")
    assert dev.handle("PI,E,0")[0] == "PI,1"


def test_qc_voltage_above_plugin_warning():
    body, extra = EbbDevice().handle("QC")
    volts = int(body.split(",")[1])
    assert volts >= 250
    assert extra is True


def test_legacy_session_ok_lines():
    dev = EbbDevice()
    assert dev.handle_session("SM,10,1,0") == "OK\r\n"
    assert dev.handle_session("V") == VERSION + "\r\n"
    assert dev.handle_session("QP") == "1\r\nOK\r\n"
    fresh = EbbDevice()
    assert fresh.handle_session("PI,E,0") == "PI,1\r\n"
