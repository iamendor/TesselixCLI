#include "mutils.h"
#include <string.h>

int last = 0;

int scanOption(Menu* points, OnInValid onInvalid, MenuFgv next){
    int option = 0;
    int i;
    for(i=0; points[i].nev != NULL; i++);

    Matrix* identity = mtrxCreateIdentity(i);


    for(i=0; points[i].nev != NULL; i++){
        randomColor();
        printf("[%d] %s", i+1, points[i].nev);
        int optionLen = 4 + strlen(points[i].nev);
        for(int k=0; k<(87-optionLen-2-2*identity->width); k++) printf(" ");
        randomColor();
        
        if(i == 0) printf("/ ");
        else if(i == identity->height -1) printf("\\ ");
        else printf("| ");   
        
        
        for(int j=0; j<identity->width; j++){
            randomColor();
            printf("%d ", (int)identity->data[i][j]);
        }
        randomColor();
    
        if(i == 0)printf("\\ ");
        else if(i == identity->height -1) printf("/");
        else printf("|");
        printf("\n");
    }

    mtrxFree(identity);
    
    randomColor();
    printf("> ");
    resetColor();
    int scanned = scanf("%d", &option);
    if(scanned != 1 || option > i+1) { 
        onInvalid(next);
        return -1;
    }
    return option;
}

void resetColor(){
    printf("\e[0;37m");
}

void randomColor(){
    char colorCodes[6][8] = {"\e[0;31m", "\e[0;32m", "\e[0;33m", "\e[0;34m", "\e[0;35m", "\e[0;36m"};
    int next = rand() % 6;
    while(next == last){
        next = rand() % 6;
    }
    printf("%s", colorCodes[next]);
    last = next;
}

void header(MenuFgv next){
    printf("\033c"); // 

    unsigned int title[8][8] = {
        { 2046, 2046, 2046, 2046, 2046, 1920, 2046, 1799 }, // 1. sor
        { 2046, 2046, 2046, 2046, 2046, 1920, 2046, 910 }, // 2. sor
        { 240, 1792, 1792, 1792, 1792, 1920, 240, 476 }, // 3. sor
        { 240, 2046, 2046, 2046, 2040, 1920, 240, 248 }, // 4. sor
        { 240, 2046, 2046, 2046, 2040, 1920, 240, 248 }, // 5. sor
        { 240, 1792, 14, 14, 1792, 1920, 240, 476 }, // 6. sor
        { 240, 2046, 2046, 2046, 2046, 2046, 2046, 910 }, // 7. sor
        { 240, 2046, 2046, 2046, 2046, 2046, 2046, 1799 }, // 8. sor
    };

    randomColor();
    for(int i=0; i<88; i++)printf("*");
    printf("\n");

    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            int s = title[i][j];
            
            
            for(int k=0; k<11; k++){
                randomColor();
                if(s >> (10-k) & 1) printf("#");
                else printf(" ");
            }
        }
        printf("\n");
    }

    randomColor();
    for(int i=0; i<88; i++)printf("*");

    randomColor();

    printf("\nEnter the option after the '>' to operate\n\n");
    resetColor();
    return next();
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