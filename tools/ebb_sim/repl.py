from .ebb_protocol import EbbDevice


def main() -> None:
    dev = EbbDevice()
    print(dev.handle_session("V"), end="")
    while True:
        try:
            line = input()
        except EOFError:
            break
        print(dev.handle_session(line), end="")


if __name__ == "__main__":
    main()
