#include "utils.h"
#include <fcntl.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void drawTitle() {
  printf("\n\n");
  printf(
      "\t ██    ██ ███    ██ ████████ ██ ████████ ██      ███████ ██████ \n");
  printf(
      "\t ██    ██ ████   ██    ██    ██    ██    ██      ██      ██   ██ \n");
  printf(
      "\t ██    ██ ██ ██  ██    ██    ██    ██    ██      █████   ██   ██ \n");
  printf(
      "\t ██    ██ ██  ██ ██    ██    ██    ██    ██      ██      ██   ██ \n");
  printf(
      "\t  ██████  ██   ████    ██    ██    ██    ███████ ███████ ██████ \n");
  printf("\t\t\n\n");
}

void set_noncanonical_mode() {
  struct termios t;
  tcgetattr(STDIN_FILENO, &t);
  t.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void drawInstructions() {
  printf("\n\n");
  printf("\t\t\t\t n - New Game \n");
  printf("\t\t\t\t c - Continue Game \n");
  printf("\t\t\t\t q - Quit Game \n");
  printf("\n\n");

  set_noncanonical_mode();
  char ch;
  read(STDIN_FILENO, &ch, 1); // Read a single character
}
