#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

#define PROMPT                                                                 \
  "1 - add\n"                                                                  \
  "2 - delete\n"                                                               \
  "3 - walk LRN\n"                                                             \
  "4 - search by key\n"                                                        \
  "5 - search special\n"                                                       \
  "6 - print to console\n"                                                     \
  "7 - export graphviz\n"                                                      \
  "8 - import from file\n"                                                     \
  "9 - timing\n"                                                               \
  "0 - exit\n"                                                                 \
  "Input: "

int inputInt(int *n);
int inputUnsigned(unsigned *n);
int dialog();
int dialogAdd(unsigned *key, unsigned *value);