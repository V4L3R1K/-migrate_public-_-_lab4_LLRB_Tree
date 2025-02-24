#include "dialog.h"

int inputInt(int *n) {
  char c = ' ';
  int sf = scanf("%d%c", n, &c);
  while (c != '\n' || sf != 2) {
    if (sf == -1)
      return 0;
    sf = scanf("%*[^\n]");
    printf("Bad input, try again: ");
    sf = scanf("%d%c", n, &c);
  }
  return sf != -1;
}

int inputUnsigned(unsigned *n) {
  char c = ' ';
  int sf = scanf("%u%c", n, &c);
  while (c != '\n' || sf != 2) {
    if (sf == -1)
      return 0;
    sf = scanf("%*[^\n]");
    printf("Bad input, try again: ");
    sf = scanf("%u%c", n, &c);
  }
  return sf != -1;
}

int dialog() {
  printf(PROMPT);
  int n = 0;
  int sf = inputInt(&n);
  if (!sf)
    return 0;
  while (n < 0 || n > 9) {
    printf("Input from 0 to 9: ");
    sf = inputInt(&n);
    if (!sf)
      return 0;
  }
  return n;
}

int dialogAdd(unsigned *key, unsigned *value) {
  printf("Input key: ");
  int ok = inputUnsigned(key);
  if (!ok)
    return 0;
  printf("Input value: ");
  ok = inputUnsigned(value);
  if (!ok)
    return 0;
  return 1;
}