#include <stdlib.h>
#include <stdio.h>
#include "include/selector.h"

#define MAX 4096

const char *types[] = {"h1", "h2", "body", "p", "div"};

struct selector * selectorInit(int type){
    struct selector * s = malloc(MAX*(sizeof(struct selector)));
    s->type = type;
    s->fontSize = malloc(MAX*(sizeof(char)));
    
    for(int i =0; i<4; i++){
         s->margin[i] = 0;
     }
    
    for(int i =0; i<4; i++){
         s->padding[i] = 0;
     }
    
    return s;

}

void setColor(int color, struct selector * selectorStruct){
    selectorStruct->color = color;
}


void setFontSize(char * font, struct selector * selectorStruct){
     selectorStruct->fontSize = font;
}

void setMargin(int m, struct selector * selectorStruct){
     for(int i =0; i<4; i++){
         selectorStruct->margin[i] = m;
     }
}

void setMarginTop(int m, struct selector * selectorStruct){
         selectorStruct->margin[TOP] = m;
}

void setMarginBottom(int m, struct selector * selectorStruct){
         selectorStruct->margin[BOTTOM] = m;
}

void setMarginRight(int m, struct selector * selectorStruct){
         selectorStruct->margin[RIGHT] = m;
}

void setMarginLeft(int m, struct selector * selectorStruct){
         selectorStruct->margin[LEFT] = m;
}

void setPadding(int p, struct selector * selectorStruct){
     for(int i =0; i<4; i++){
         selectorStruct->padding[i] = p;
     }
}

void setPaddingTop(int p, struct selector * selectorStruct){
         selectorStruct->padding[TOP] = p;
}

void setPaddingBottom(int p, struct selector * selectorStruct){
         selectorStruct->padding[BOTTOM] = p;
}

void setPaddingRight(int p, struct selector * selectorStruct){
         selectorStruct->padding[RIGHT] = p;
}

void setPaddingLeft(int p, struct selector * selectorStruct){
         selectorStruct->padding[LEFT] = p;
}

