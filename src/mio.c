#include "mio.h"

void io(){
    Menu menupoints[] = {
        { "Export all matrices",  exportAll },
        { "Import from file", import },
        { "Back", menu },
        { "Exit", exitMenu },
        { NULL, NULL }
    };

    int option = scanOption(menupoints, header, io);

    return header(menupoints[option-1].fgv);
}

void exportAll(){
    char name[40+1] = "default.txt";
    if(head == NULL){
        printf("No matrix to export!\n");
        waitForEnter();
        return header(io);
    }
    printf("Enter the filename(ex: 'lorem.txt')\n> ");
    scanf("%s", name);

    exportMatrices(name);

    printf("Matrices exported successfully!\n");
    waitForEnter();
    return header(io);
}

void import(){
    char name[40+1];
    int i;

    printf("Enter the filename(ex: 'lorem.txt')\n> ");
    scanf("%s", name);

    FILE* fp = fopen(name, "r");
    if(fp == NULL){
        printf("Error opening the file!\n");
        waitForEnter();
        return header(io);
    }

    Matrix** mtrxArr = mtrxImport(fp);
    for(i=0; mtrxArr[i] != NULL; i++){
        insertMatrix(mtrxArr[i]);
    }
    free(mtrxArr);


    printf("Successfully imported %d matrices!\n", i);
    waitForEnter();

    return header(io);
}