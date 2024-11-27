#include "madvanced.h"

void advanced(){
    Menu menupoints[] = {
        { "Gauss-elimination",  gaussElim},
        { "Determinant", det },
        { "Transponate", transponate },
        { "Back", menu },
        { "Exit", exitMenu },
        { NULL, NULL }
    };

    int option = scanOption(menupoints, header, advanced);

    return header(menupoints[option-1].fgv);
}

void gaussElim(){
    int option;
    MatrixNode* node = NULL;
    printf("Note: you should pass the augmented matrix!\n");
    printf("Note: this does affect the original matrix!\n");
    chooseMatrix(&node, &option, advanced);
    if(node == NULL) return;

    mtrxGaussElim(node->mtrx);
    printf("Result: ");
    mtrxPrint(node->mtrx);
    waitForEnter();
    return header(advanced);
}
void det(){
    int option;
    MatrixNode* node = NULL;
    chooseMatrix(&node, &option, advanced);
    if(node == NULL) return;

    printf("\nDeterminant: %.2f\n", mtrxDeterminant(node->mtrx));
    waitForEnter();

    return header(advanced);
}
void transponate(){
    int option;
    MatrixNode* node = NULL;
    chooseMatrix(&node, &option, advanced);
    if(node == NULL) return;

    Matrix* transponated = mtrxTransponate(node->mtrx);
    printf("Result: ");
    mtrxPrint(transponated);
    clearInput();
    
    bool save = scanSave();
    if(save) insertMatrix(transponated);
    else mtrxFree(transponated);

    return header(advanced);

}

