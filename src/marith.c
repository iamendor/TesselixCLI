#include "marith.h"


void arith(){
    Menu menupoints[] = {
        { "Scalar operation",  scalar},
        { "Matrix add/substract", addSub },
        { "Matrix multiplication", multiply },
        { "Matrix comparison", compare },
        { "Back", menu },
        { "Exit", exitMenu },
        { NULL, NULL }
    };

    int option = scanOption(menupoints, header, arith);

    return header(menupoints[option-1].fgv);
}

void scalar(){
    int i, a, scalar;  
    char op;
    printMatrices(&i);

    if(i == 0){
        printf("\nNo matrices to operate with!\n");
        waitForEnter();
        return header(crud);
    }

    printf("Enter operation!\
    \n(ex: '2 + 1' adds 1 to every cell of matrix at index 2)!\n> ");
    int scanned = scanf("%d %c %d", &a, &op, &scalar);
    while(scanned != 3 || a < 1 || a > i || \
       (op != '+' && op != '-' && op != '*' && op != '/') ){
        printf("Error, try again!\n> ");
        scanned = scanf("%d %c %d", &a, &op, &scalar);
    }
    MatrixNode* node = getNode(a);
    mtrxOp(scalar, op, node->mtrx);

    printf("Result: ");
    mtrxPrint(node->mtrx);

    clearInput();

    bool save = scanSave();

    if(!save){
        if(op == '+') mtrxOp(scalar, '-', node->mtrx);
        else if(op == '-') mtrxOp(scalar, '+', node->mtrx);
        else if(op == '*') mtrxOp(scalar, '/', node->mtrx);
        else if(op == '/') mtrxOp(scalar, '*', node->mtrx);
    }
    
    return header(arith);
}

void addSub(){
    int i, a, b;  
    char op; 
    printMatrices(&i);

    if(i < 2){
        printf("\nNo matrices to operate with!\n");
        waitForEnter();
        return header(arith);
    }

    printf("Enter operation!\
    \n(ex: '1 + 2' adds the second matrix to the first)!\n> ");
    int scanned = scanf("%d %c %d", &a, &op, &b);
    while(scanned != 3 || a < 1 || a > i || b < 1 || b > i ||\
       (op != '+' && op != '-' ) ){
        printf("Error, try again!\n> ");
        scanned = scanf("%d %c %d", &a, &op, &b);
    }

    MatrixNode* mtrxA = getNode(a);
    MatrixNode* mtrxB = getNode(b);

    Matrix* res = mtrxOpMtrx(mtrxA->mtrx, op, mtrxB->mtrx);
    if(res == NULL){
        printf("\nInvalid operation!\n");
        waitForEnter();
        return header(arith);
    }

    printf("Result: ");
    mtrxPrint(mtrxA->mtrx);


    clearInput();
    bool save = scanSave();

    if(save){
        if(op == '+') mtrxOpMtrx(mtrxA->mtrx, '-', mtrxB->mtrx);
        else if(op == '-') mtrxOpMtrx(mtrxA->mtrx, '+', mtrxB->mtrx);
    }
    return header(arith);

}

void multiply(){
    MatrixNode *nodeA = NULL, *nodeB = NULL;

    chooseTwoMatrix(&nodeA, &nodeB, arith);
    if(nodeA == NULL || nodeB == NULL) return;

    Matrix* result = mtrxMultiplMtrx(nodeA->mtrx, nodeB->mtrx);
    if(result == NULL){
        printf("\nInvalid operation!\n");
        waitForEnter();
        return header(arith);
    }

    printf("Result: ");
    mtrxPrint(result);

    clearInput();
    bool save = scanSave();


    if(save){
        insertMatrix(result);
    }else mtrxFree(result);
    return header(arith);

}

void compare(){
    MatrixNode *nodeA, *nodeB;

    chooseTwoMatrix(&nodeA, &nodeB, arith);
    if(nodeA == NULL || nodeB == NULL) return;
    clearInput();

    bool equal = mtrxCompare(nodeA->mtrx, nodeB->mtrx);

    if(equal){
        printf("The two matrices are equal!\n");
    }else{
        printf("Matrices are not matching!\n");
    }

    waitForEnter();
    return header(arith);
}

