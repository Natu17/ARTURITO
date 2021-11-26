#include <stdlib.h>
#include <stdio.h>
#include "selector.h"
#include "generatorFile.h"
#define MAX 4096



FILE * createCssFile(){
    FILE *cssFile;
    cssFile  = fopen ("StyleSheet.css", "w");
    return cssFile;
}



void closeFile(FILE * cssFile){
    fclose(cssFile);
}
