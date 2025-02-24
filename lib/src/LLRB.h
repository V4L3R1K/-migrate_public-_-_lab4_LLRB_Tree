#pragma once

#include <stdio.h>
#include <stdlib.h>

#define BLACK 0
#define RED 1

typedef struct Node {
  unsigned key;
  unsigned *value;
  struct Node *left;
  struct Node *right;
  char color;
} Node;

Node *newNode(unsigned key, unsigned value);
void freeNode(Node *node);

int isRed(Node *node);
Node *rotateL(Node *node);
Node *rotateR(Node *node);
void flipColors(Node *node);

Node *insertIntoRoot(Node *root, unsigned key, unsigned value);
Node *insertNode(Node *node, unsigned key, unsigned value);

Node *deleteFromRoot(Node *root, unsigned key);
Node *deleteNode(Node *node, unsigned key);
Node *findMin(Node *node);
Node *moveRedLeft(Node *node);
Node *moveRedRight(Node *node);
Node *deleteMin(Node *node);

void walkLRN(Node *node);

Node *searchNode(Node *node, unsigned key);

Node **searchSpecial(Node *node, unsigned key, unsigned *count);

void print(Node *node);
void printer(Node *node, unsigned depth);

void exportGraphviz(Node *node, FILE *f);
void dotWrite(Node *node, FILE *f);

Node *importText(FILE *f);