#include "lab4b.h"

#include <time.h>

#define N_TESTS 50
#define N_NODES 1000
#define N_KEYS 500

int addFunc(Node **node) {
  unsigned key = 0, value = 0;
  if (!dialogAdd(&key, &value))
    return 0;
  if (searchNode(*node, key) != NULL) {
    printf("Already exists\n");
    return 1;
  }
  *node = insertIntoRoot(*node, key, value);
  return 1;
}

int delFunc(Node **node) {
  unsigned key = 0;
  printf("Input key: ");
  if (!inputUnsigned(&key))
    return 0;
  if (searchNode(*node, key) == NULL) {
    printf("Node does not exists\n");
    return 1;
  }
  *node = deleteFromRoot(*node, key);
  return 1;
}

int walkFunc(Node **node) {
  walkLRN(*node);
  return 1;
}

int searchFunc(Node **node) {
  unsigned key = 0;
  printf("Input key: ");
  if (!inputUnsigned(&key))
    return 0;
  Node *found = searchNode(*node, key);
  if (!found) {
    printf("Not found\n");
    return 1;
  }
  if (found->color == RED)
    printf("RED %u : %u\n", found->key, *(found->value));
  else
    printf("BLACK %u : %u\n", found->key, *(found->value));
  return 1;
}

int searchSpecialFunc(Node **node) {
  unsigned key = 0;
  printf("Input key: ");
  if (!inputUnsigned(&key))
    return 0;

  unsigned count = 0;
  Node **found = searchSpecial(*node, key, &count);
  if (count == 2) {
    if ((found[0])->color == RED)
      printf("Found RED %u : %u\n", (found[0])->key, *((found[0])->value));
    else
      printf("Found BLACK %u : %u\n", (found[0])->key, *((found[0])->value));
    if ((found[1])->color == RED)
      printf("Found RED %u : %u\n", (found[1])->key, *((found[1])->value));
    else
      printf("Found BLACK %u : %u\n", (found[1])->key, *((found[1])->value));
  } else if (count == 1) {
    if ((found[0])->color == RED)
      printf("Found RED %u : %u\n", (found[0])->key, *((found[0])->value));
    else
      printf("Found BLACK %u : %u\n", (found[0])->key, *((found[0])->value));
  } else
    printf("Not found");
  free(found);
  return 1;
}

int printFunc(Node **node) {
  print(*node);
  return 1;
}

int graphvizFunc(Node **node) {
  char *filePath = NULL;
  filePath = readline("Input output file path (.dot): ");
  if (!filePath)
    return 0;
  FILE *f = fopen(filePath, "wt");
  exportGraphviz(*node, f);
  fclose(f);
  free(filePath);
  return 1;
}

int importFunc(Node **node) {
  char *filePath = NULL;
  filePath = readline("Input input file path: ");
  if (!filePath)
    return 0;
  FILE *f = fopen(filePath, "rt");
  if (!f) {
    printf("Bad file path\n");
    free(filePath);
    return 1;
  }
  freeNode(*node);
  *node = importText(f);
  fclose(f);
  free(filePath);
  return 1;
}

void timingAdd() {
  srand(time(NULL));
  clock_t tStart, tEnd;
  unsigned keys[N_KEYS];
  for (int i = 0; i < N_KEYS; i++)
    keys[i] = (unsigned)(abs(rand() * rand()) * 2);

  Node *node = NULL;
  printf("ADD:\nnTest nNodes time\n");
  for (int j = 0; j < N_TESTS; j++) {
    tStart = clock();
    for (int i = 0; i < N_NODES; i++) {
      unsigned k = (unsigned)(abs(rand() * rand()));
      node = insertIntoRoot(node, k, 0);
    }
    tEnd = clock();

    double dt = (double)(tEnd - tStart) / CLOCKS_PER_SEC;
    printf("%d %d %.5lf\n", j + 1, (j + 1) * N_NODES, dt);
  }

  freeNode(node);
  return;
}

void timingDel() {
  srand(time(NULL));
  clock_t tStart, tEnd;
  unsigned keys[N_KEYS];
  for (int i = 0; i < N_KEYS; i++)
    keys[i] = (unsigned)(abs(rand() * rand()));

  Node *node = NULL;
  printf("DEL:\nnTest nNodes time\n");
  for (int j = 0; j < N_TESTS; j++) {
    for (int i = 0; i < N_NODES; i++) {
      unsigned k = (unsigned)(abs(rand() * rand()));
      node = insertIntoRoot(node, k, 0);
    }

    tStart = clock();
    for (int i = 0; i < N_KEYS; i++)
      node = deleteFromRoot(node, keys[i]);
    tEnd = clock();

    double dt = (double)(tEnd - tStart) / CLOCKS_PER_SEC;
    printf("%d %d %.5lf\n", j + 1, (j + 1) * N_NODES, dt);
  }

  freeNode(node);
  return;
}

void timingSearch() {
  srand(time(NULL));
  clock_t tStart, tEnd;
  unsigned keys[N_KEYS];
  for (int i = 0; i < N_KEYS; i++)
    keys[i] = (unsigned)(abs(rand() * rand()));

  Node *node = NULL;
  printf("SEARCH:\nnTest nNodes time\n");
  for (int j = 0; j < N_TESTS; j++) {
    for (int i = 0; i < N_NODES; i++) {
      unsigned k = (unsigned)(abs(rand() * rand()));
      node = insertIntoRoot(node, k, 0);
    }

    tStart = clock();
    for (int i = 0; i < N_KEYS; i++)
      searchNode(node, keys[i]);
    tEnd = clock();

    double dt = (double)(tEnd - tStart) / CLOCKS_PER_SEC;
    printf("%d %d %.5lf\n", j + 1, (j + 1) * N_NODES, dt);
  }

  freeNode(node);
  return;
}

void timingSearchSpecial() {
  srand(time(NULL));
  clock_t tStart, tEnd;
  unsigned keys[N_KEYS];
  for (int i = 0; i < N_KEYS; i++)
    keys[i] = (unsigned)(abs(rand() * rand()));

  Node *node = NULL;
  printf("SEARCH SPECIAL:\nnTest nNodes time\n");
  for (int j = 0; j < N_TESTS; j++) {
    for (int i = 0; i < N_NODES; i++) {
      unsigned k = (unsigned)(abs(rand() * rand()));
      node = insertIntoRoot(node, k, 0);
    }

    unsigned c;
    tStart = clock();
    for (int i = 0; i < N_KEYS; i++) {
      Node **found = searchSpecial(node, keys[i], &c);
      free(found);
    }
    tEnd = clock();

    double dt = (double)(tEnd - tStart) / CLOCKS_PER_SEC;
    printf("%d %d %.5lf\n", j + 1, (j + 1) * N_NODES, dt);
  }

  freeNode(node);
  return;
}

int timingFunc(Node **unused) {
  // timingAdd();
  // timingDel();
  // timingSearch();
  timingSearchSpecial();
  return 1;
}
