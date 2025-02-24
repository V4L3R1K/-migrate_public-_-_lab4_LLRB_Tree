#include "lab4b.h"

int main() {
  Node *llrb = NULL;

  int (*arrFunc[])(Node **) = {NULL,      addFunc,      delFunc,
                               walkFunc,  searchFunc,   searchSpecialFunc,
                               printFunc, graphvizFunc, importFunc,
                               timingFunc};
  int rc;
  while (rc = dialog()) {
    if (!arrFunc[rc](&llrb))
      break;
  }

  freeNode(llrb);
  return 0;
}