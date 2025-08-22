#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios orig_termios;

void die(const char *s) {
  perror(s);
  exit(1);
}

void disableRawMode(void) {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode(void) {
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disableRawMode);

  struct termios raw = orig_termios;
  // IXON: Disables C-s && C-q signals
  // ICRNL: Fixes C-m
  // BRKINT: A break condition causes a SIGINT to be sent to the program
  // ISTRIP: Causes 8th bit of each input to be stripped
  // INPCK: Enables parity checking (doesn't seem to apply to modern terminals)
  // CS8: Not a flag :: Bitmask with multiple bits. Sets char size to 8 bits per byte!
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

  // OPOST: Disables input processing (i.e. "\n" -> "\r\n")
  raw.c_oflag &= ~(OPOST);

  // ECHO: Disables ECHO
  // ICANON: Disables Canonical mode
  // ISIG: Disables C-c && C-z signals
  // IEXTEN: Disables C-v signal
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

  // VMIN & VTIME come from <termios.h>
  // They are indexes to the "control characters" field
  // - VMIN sets min amnt of bytes of input needed before read() can return
  // - VTIME sets max amnt of time to wait b4 read() returns
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main(void) {
  enableRawMode();

  while (1) {
    char c = '\0';
    read(STDIN_FILENO, &c, 1);
    if (iscntrl(c)) {
      printf("%d\r\n", c);
    } else {
      printf("%d ('%c')\r\n", c, c);
    }

    if (c == 'q') break;

  }


  return 0;
}
