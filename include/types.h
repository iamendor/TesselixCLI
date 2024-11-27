#ifndef TYPES_H
#define TYPES_H

#include <tesselix.h>



typedef struct MatrixNode{
    Matrix* mtrx;
    struct MatrixNode* next;
} MatrixNode;


typedef void (*MenuFgv)();
typedef void (*OnInValid)(MenuFgv next);
typedef struct Menu{
    char const *nev;
    MenuFgv fgv;
} Menu;

extern MatrixNode* head;
extern char defIO[];



#endif