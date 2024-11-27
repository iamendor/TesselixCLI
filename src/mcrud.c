#include "mcrud.h"

void crud(){
    Menu menupoints[] = {
        { "Create", create },
        { "Create Identity", identity },
        { "Duplicate", duplicate },
        { "Merge", merge },
        { "Resize", resize },
        { "Delete", rm },
        { "Back", menu },
        { "Exit", exitMenu },
        { NULL, NULL } 
    };
    int option = scanOption(menupoints, header, crud);

    return header(menupoints[option-1].fgv);
}

void identity(){
    int n;
    printf("Enter the dimension of the matrix!\n> ");
    int scanned = scanf("%d", &n);
    while(scanned != 1 && n < 1){
        printf("Error, try again!\n> ");
        scanned = scanf("%d", &n);
    }

    Matrix* identity = mtrxCreateIdentity(n);
    insertMatrix(identity);

    return header(crud);
}

void duplicate(){
    int option;
    MatrixNode* node = NULL;

    chooseMatrix(&node, &option, crud);
    if(node == NULL) return;

    Matrix* copy = mtrxCopy(node->mtrx);
    insertMatrix(copy);

    return header(crud);
}

void rm(){
    int option; 
    MatrixNode* node = NULL;

    chooseMatrix(&node,&option, crud);
    if(node == NULL) return;

    removeMatrix(option);
    
    return header(crud);
}

void merge(){
    
    MatrixNode *nodeA = NULL, *nodeB = NULL;

    chooseTwoMatrix(&nodeA, &nodeB, crud);
    if(nodeA == NULL || nodeB == NULL) return;

    Matrix* mtrx = mtrxCreateAug(nodeA->mtrx, nodeB->mtrx);

    if(mtrx == NULL){
        printf("Cannot merge the two matrices!\n");
        waitForEnter();
        return header(crud);
    }

    printf("Result:");
    mtrxPrint(mtrx);
    clearInput();

    bool save = scanSave();
    
    if(save){
        insertMatrix(mtrx);
    }else mtrxFree(mtrx);
    return header(crud);
}

void create(){
    int h = 1, w = 1;

    printf("H= ");
    scanf("%d", &h);
    printf("W= ");
    scanf("%d", &w);

    double* arr= (double*)malloc(h*w*sizeof(double));
    if(arr == NULL) return header(menu);

    for(int i=0; i<(h*w); i++){
        printf("a%d%d= ", i/w + 1, i%w + 1);
        scanf("%lf", &arr[i]);
    }
    Matrix* mtrx = mtrxCreate(h, w, arr);

    insertMatrix(mtrx);

    free(arr);

    return header(crud);
}

void resize(){
    int option, h, w;
    MatrixNode* node = NULL;
    chooseMatrix(&node, &option, crud);
    if(node == NULL) return;

    clearInput();
    printf("Enter the new dimensions and to resize! ( H W )\n(Note: you can only shrink or expand at time)\n> ");
    int scanned = scanf("%d %d", &h, &w);
    while(scanned != 2 || h < 1 || w < 1 || (h < node->mtrx->height && w > node->mtrx->width) || (h > node->mtrx->height && w < node->mtrx->width)){
        printf("Error, try again!\n> ");
        scanned = scanf("%d %d", &h, &w);
    }

    if(w > node->mtrx->width || h > node->mtrx->height){
        mtrxExpand(node->mtrx, h, w);
    }
    else if(w < node->mtrx->width || h < node->mtrx->height){
        mtrxShrink(node->mtrx, h, w);
    }

    printf("Result: ");
    mtrxPrint(node->mtrx);

    waitForEnter();
    return header(crud);
}