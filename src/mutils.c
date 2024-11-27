#include "mutils.h"


int scanOption(Menu* points, OnInValid onInvalid, MenuFgv next){
    int option = 0;
    int i;
    for(i=0; points[i].nev != NULL; i++){
        printf("[%d] %s\n", i+1, points[i].nev);
    }
    printf("> ");
    int scanned = scanf("%d", &option);
    if(scanned != 1 || option > i+1) { 
        onInvalid(next);
        return -1;
    }
    return option;
}

void header(MenuFgv next){
    printf("\033c"); // 

    printf("#####  #####  #####  #####  #####  #      #   #   #\n");
    printf("  #    #      #      #      #      #      #    # #\n");
    printf("  #    ####   #####  #####  ####   #      #     #\n");
    printf("  #    #          #      #  #      #      #    # #\n");
    printf("  #    #####  #####  #####  #####  #####  #   #   #\n");

    printf("\nEnter the option after the '>' to operate\n");
    for(int i=0; i<80; i++)printf("-");
    printf("\n");
    next();
    return;
}

void insertMatrix(Matrix* mtrx){
    MatrixNode* node = (MatrixNode*)malloc(sizeof(MatrixNode));
    node->mtrx = mtrx;
    node->next = NULL;

    if(head == NULL){
        head = node;
        return;
    }

    MatrixNode* move;
    for(move = head; move->next != NULL; move = move->next);
    move->next = node;
}

void removeMatrix(int index){
    int i;
    MatrixNode* move;
    if(head == NULL) return;
    if(index == 1){
        MatrixNode* del = head;
        head = head->next;
        mtrxFree(del->mtrx);
        free(del);
        return;
    }
    for(i = 1, move = head; i<index-1 && move != NULL; i++, move = move->next);
    //Most vagyunk az előtte levőnél
    MatrixNode* del = move->next;
    move->next = del->next;
    mtrxFree(del->mtrx);
    free(del);
}

void exportMatrices(char* const name){
    MatrixNode* node = head;
    if(node == NULL) return;
    FILE* fp = fopen(name, "w");

    while(node != NULL){
        Matrix* mtrx = node->mtrx;
        mtrxExport(fp, mtrx);
        node = node->next;
    }

    fclose(fp);
}

void importMatrices(char* const name){
    FILE* fp = fopen(name, "r");
    if(fp == NULL) {
        return;
    }

    Matrix** mtrxArr = mtrxImport(fp);

    for(int i=0; mtrxArr[i] != NULL; i++){
        insertMatrix(mtrxArr[i]);
    }
    free(mtrxArr);

    fclose(fp);
}



MatrixNode* getNode(int index){
    int i;
    MatrixNode* move;
    if(head ==NULL) return NULL;
    if(index == 1) return head;
    for(i = 1, move = head; i<index && move != NULL; i++, move = move->next);
    return move;
}

void printMatrices(int* i){
    MatrixNode* move;
    for(*i=0, move = head; move != NULL; *i += 1, move = move->next) {
        printf("%-2s%d.", "", *i+1);
        mtrxPrint(move->mtrx);
    }
    printf("\n");
}

void waitForEnter(){
    char c;
    printf("Press Enter to go continue!\n> ");
    while((c = getchar()) != '\n' && c != EOF);
    getchar();
}

void clearInput(){
    char c;
    while((c =getchar()) != '\n');
}

bool scanSave(){
    char save;
    printf("\nWould you like to save it? (Y/n)\n> ");
    int scanned = scanf("%c", &save);

    while(scanned != 1){
        printf("Error, try again!\n> ");
        scanned = scanf("%c", &save);
    }

    return save == 'Y' || save == 'y';
}

bool scanSaveMatrices(){
    char save;
    printf("\nWould you like to save all matrices to 'matrix.txt' (Y/n)\n> ");
    int scanned = scanf("%c", &save);

    while(scanned != 1){
        printf("Error, try again!\n> ");
        scanned = scanf("%c", &save);
    }

    return save == 'Y' || save == 'y';

}

void chooseTwoMatrix(MatrixNode** nodeA, MatrixNode** nodeB, MenuFgv onError){
    int i, a, b;
    printMatrices(&i);

    if(i < 2){
        printf("\nYou need more than 2 matrices!");
        waitForEnter();
        return header(onError);
    }

    printf("Enter the matrices' index ( ex: '1 2' )\n> ");
    int scanned = scanf("%d %d", &a, &b);
    while(scanned != 2 || a < 1 || a > i || b < 1 || b > i || b == a){
        printf("Error, try again!\n> ");
        scanned = scanf("%d %d", &a, &b);
    }
    *nodeA = getNode(a);
    *nodeB = getNode(b);
}

void chooseMatrix(MatrixNode **node, int *a, MenuFgv onError){
    int i;
    printMatrices(&i);

    if(i == 0){
        printf("\nYou need more than 2 matrices!");
        waitForEnter();
        return header(onError); //Doesnt return in the function and does not stop;
    }

    printf("Enter the matrix' index\n> ");
    int scanned = scanf("%d", a);
    while(scanned != 1 || *a < 1 || *a > i){
        printf("Error, try again!\n> ");
        scanned = scanf("%d", a);
    }
    *node = getNode(*a);
}