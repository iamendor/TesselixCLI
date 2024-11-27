#ifndef MUTILS_H
#define MUTILS_H

#include "types.h"
#include <stdbool.h>

void insertMatrix(Matrix* mtrx);
MatrixNode* getNode(int index);
void removeMatrix(int index); // 1-től
int scanOption(Menu* points, OnInValid onInvalid, MenuFgv next);

void printMatrices(int* i);
void waitForEnter();
void clearInput();
void header(MenuFgv next);
bool scanSave();
bool scanSaveMatrices();
void exportMatrices(char* const name);
void importMatrices(char* const name);
void chooseTwoMatrix(MatrixNode** nodeA, MatrixNode** nodeB, MenuFgv onError);
void chooseMatrix(MatrixNode **node, int *a, MenuFgv onError);

#endif