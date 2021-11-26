#include <stdlib.h>
#include <stdio.h>
#include "selector.h"

#define MAX 4096

enum type{
    CLASS,
    ID,
    H1,
    H2,
    BODY,
    P,
    DIV,
};


struct selector {
    int type;
    int color;
    char * fontSize;
    int margin;
    int padding;
};


struct selector * selectorInit(int type){
    struct selector * s = malloc(MAX*(sizeof(struct selector)));
    s->type = type;
    s->fontSize = malloc(MAX*(sizeof(char)));

}

int setColor(int color, struct selector * selectorStruct){
    selectorStruct->color = color;
}


int setFontSize(char * font, struct selector * selectorStruct){
     selectorStruct->fontSize = font;
}

int setMargin(int m, struct selector * selectorStruct){
     selectorStruct->margin = m;
}


int setPadding(int p, struct selector * selectorStruct){
     selectorStruct->padding = p;
}