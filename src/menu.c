#include <stdlib.h>
#include <tesselix.h>
#include <stdio.h>
#include "debugmalloc.h"
#include "menu.h"

int main(int argc, char const *argv[])
{    
    head = NULL;
    importMatrices(defIO);
    header(menu);
    return 0;
}

void menu(){
    Menu menupoints[] = {
        { "List", list },
        { "Crud", crud },
        { "Arithmetic", arith },
        { "Advanced", advanced },
        { "Import/Export", io },
        { "Exit", exitMenu },
        { NULL, NULL } 
    };
    int option = scanOption(menupoints, header, menu);

    return header(menupoints[option-1].fgv);
}


void list(){
    int i;
    printMatrices(&i);

    if(i == 0) printf("\nNo matrices stored yet!\n");
    waitForEnter();
    return header(menu);
}

void exitMenu(){
    clearInput();

    if(head != NULL){
        bool save = scanSaveMatrices();
        if(save) exportMatrices(defIO);
    }

    MatrixNode* move = head;
    if(head == NULL) exit(0);
    while(move != NULL){
        MatrixNode* tmp = move->next;
        mtrxFree(move->mtrx);
        free(move);
        move = tmp;
    }
    exit(0);
}