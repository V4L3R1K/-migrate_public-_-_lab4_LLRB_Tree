#include "LLRB.h"

Node *newNode(unsigned key, unsigned value) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->key = key;
  node->value = (unsigned *)malloc(sizeof(unsigned));
  *(node->value) = value;
  node->color = RED;
  node->left = NULL;
  node->right = NULL;
  return node;
}

void freeNode(Node *node) {
  if (node) {
    freeNode(node->left);
    freeNode(node->right);
    free(node->value);
    free(node);
  }
  return;
}

int isRed(Node *node) {
  if (!node)
    return 0;
  return node->color == RED;
}

Node *rotateL(Node *node) {
  Node *child = node->right;
  node->right = child->left;
  child->left = node;
  child->color = node->color;
  node->color = RED;
  return child;
}

Node *rotateR(Node *node) {
  Node *child = node->left;
  node->left = child->right;
  child->right = node;
  child->color = node->color;
  node->color = RED;
  return child;
}

void flipColors(Node *node) {
  if (node->color == RED)
    node->color = BLACK;
  else
    node->color = RED;

  if (node->left->color == RED)
    node->left->color = BLACK;
  else
    node->left->color = RED;

  if (node->right->color == RED)
    node->right->color = BLACK;
  else
    node->right->color = RED;
  return;
}

Node *insertIntoRoot(Node *root, unsigned key, unsigned value) {
  root = insertNode(root, key, value);
  root->color = BLACK;
  return root;
}

Node *insertNode(Node *node, unsigned key, unsigned value) {
  if (!node)
    return newNode(key, value);

  if (node->key == key)
    return node;

  if (key < node->key)
    node->left = insertNode(node->left, key, value);
  if (key > node->key)
    node->right = insertNode(node->right, key, value);

  if (isRed(node->right) && !isRed(node->left))
    node = rotateL(node);
  if (isRed(node->left) && isRed(node->left->left))
    node = rotateR(node);
  if (isRed(node->left) && isRed(node->right))
    flipColors(node);

  return node;
}

Node *deleteFromRoot(Node *root, unsigned key) {
  root = deleteNode(root, key);
  if (root)
    root->color = BLACK;
  return root;
}

Node *deleteNode(Node *node, unsigned key) {
  if (!node)
    return node;

  if (key < node->key) {
    if (node->left && !isRed(node->left) && !isRed(node->left->left))
      node = moveRedLeft(node);
    node->left = deleteNode(node->left, key);
  } else {
    if (isRed(node->left))
      node = rotateR(node);
    if (key == node->key && !(node->right)) {
      freeNode(node);
      return NULL;
    }

    if (node->right && !isRed(node->right) && !isRed(node->right->left))
      node = moveRedRight(node);
    if (key == node->key) {
      Node *minR = findMin(node->right);
      free(node->value);
      node->value = minR->value;
      node->key = minR->key;
      node->right = deleteMin(node->right);
      free(minR);
    } else
      node->right = deleteNode(node->right, key);
  }

  if (isRed(node->left) && isRed(node->right))
    flipColors(node);
  if (isRed(node->right) && !isRed(node->left))
    node = rotateL(node);
  if (isRed(node->left) && isRed(node->left->left))
    node = rotateR(node);

  return node;
}

Node *findMin(Node *node) {
  if (!node->left)
    return node;
  return findMin(node->left);
}

Node *moveRedLeft(Node *node) {
  flipColors(node);
  if (isRed(node->right->left)) {
    node->right = rotateR(node->right);
    node = rotateL(node);
    flipColors(node);
  }
  return node;
}

Node *moveRedRight(Node *node) {
  flipColors(node);
  if (isRed(node->left->left)) {
    node = rotateR(node);
    flipColors(node);
  }
  return node;
}

Node *deleteMin(Node *node) {
  if (!(node->left))
    return NULL;
  if (!isRed(node->left) && !isRed(node->left->left))
    node = moveRedLeft(node);
  node->left = deleteMin(node->left);

  if (isRed(node->left) && isRed(node->right))
    flipColors(node);
  if (isRed(node->right) && !isRed(node->left))
    node = rotateL(node);
  if (isRed(node->left) && isRed(node->left->left))
    node = rotateR(node);

  return node;
}

void walkLRN(Node *node) {
  if (node) {
    walkLRN(node->left);
    walkLRN(node->right);
    if (node->color == RED)
      printf("(RED %u : %u)\n", node->key, *(node->value));
    else
      printf("(BLACK %u : %u)\n", node->key, *(node->value));
  }
  return;
};

Node *searchNode(Node *node, unsigned key) {
  if (node) {
    if (node->key == key)
      return node;
    if (key < node->key)
      return searchNode(node->left, key);
    return searchNode(node->right, key);
  }
  return NULL;
}

Node *searchBigger(Node *node, unsigned key) {
  if (!node)
    return NULL;

  Node *l = searchBigger(node->left, key);
  Node *r = searchBigger(node->right, key);
  if (l && l->key <= key)
    l = NULL;
  if (r && r->key <= key)
    r = NULL;

  if (l && r && l->key - key > r->key - key)
    l = r;
  else if (!l)
    l = r;

  if (!l)
    return node;
  if (node->key <= key)
    return l;
  if (node->key - key < l->key - key)
    return node;
  return l;
}

Node *searchSmaller(Node *node, unsigned key) {
  if (!node)
    return NULL;

  Node *l = searchSmaller(node->left, key);
  Node *r = searchSmaller(node->right, key);
  if (l && l->key >= key)
    l = NULL;
  if (r && r->key >= key)
    r = NULL;

  if (l && r && key - l->key > key - r->key)
    l = r;
  else if (!l)
    l = r;

  if (!l)
    return node;
  if (node->key >= key)
    return l;
  if (key - node->key < key - l->key)
    return node;
  return l;
}

Node **searchSpecial(Node *node, unsigned key, unsigned *count) {
  Node *bigger = searchBigger(node, key);
  Node *smaller = searchSmaller(node, key);
  if (bigger && bigger->key == key)
    bigger = NULL;
  if (smaller && smaller->key == key)
    smaller = NULL;
  Node **res = malloc(2 * sizeof(Node *));
  *count = 1;
  if (bigger && smaller && bigger->key - key == key - smaller->key) {
    *count = 2;
    res[0] = smaller;
    res[1] = bigger;
  } else if (bigger && smaller && bigger->key - key < key - smaller->key)
    res[0] = bigger;
  else if (bigger && smaller && bigger->key - key > key - smaller->key)
    res[0] = smaller;
  else if (bigger && !smaller)
    res[0] = bigger;
  else if (smaller && !bigger)
    res[0] = bigger;
  else
    *count = 0;
  return res;
};

void print(Node *node) {
  if (node)
    printer(node, 0);
  else
    printf("Empty tree, nothing to print\n");
  return;
};

void printer(Node *node, unsigned depth) {
  if (node->color == RED)
    printf("(RED %u : %u)\n", node->key, *(node->value));
  else
    printf("(BLACK %u : %u)\n", node->key, *(node->value));

  if (node->left) {
    for (int i = 0; i < depth + 1; i++)
      printf("│     ");
    printf("\n");
    for (int i = 0; i < depth; i++)
      printf("│     ");
    printf("├──L──");
    printer(node->left, depth + 1);
  }

  if (node->right) {
    for (int i = 0; i < depth + 1; i++)
      printf("│     ");
    printf("\n");
    for (int i = 0; i < depth; i++)
      printf("│     ");
    printf("├──R──");
    printer(node->right, depth + 1);
  }
}

void exportGraphviz(Node *node, FILE *f) {
  fprintf(f, "digraph {\n");
  dotWrite(node, f);
  fprintf(f, "}\n");
}

void dotWrite(Node *node, FILE *f) {
  if (node) {
    if (node->color == RED)
      fprintf(f, "%u [label=\"%u:%u\", color=\"red\"]\n", node->key, node->key,
              *(node->value));
    else
      fprintf(f, "%u [label=\"%u:%u\", color=\"black\"]\n", node->key,
              node->key, *(node->value));
    if (node->left)
      fprintf(f, "%u->%u\n", node->key, node->left->key);
    if (node->right)
      fprintf(f, "%u->%u\n", node->key, node->right->key);
    dotWrite(node->left, f);
    dotWrite(node->right, f);
  }
  return;
}

Node *importText(FILE *f) {
  Node *node = NULL;
  for (;;) {
    unsigned key;
    if (fscanf(f, "%u\n", &key) == EOF)
      return node;

    unsigned value;
    size_t n = 0;
    if (fscanf(f, "%u\n", &value) == EOF)
      return node;

    node = insertIntoRoot(node, key, value);
  }
}