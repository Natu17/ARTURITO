
#ifndef SELECTOR_H
#define SELECTOR_H



struct selector {
    int type;
    int color;
    char * fontSize;
    int margin[4];
    int padding[4];
};


struct selector * selectorInit(int type);
void setColor(int color, struct selector * selectorStruct);
void setFontSize(char * font, struct selector * selectorStruct);
void setMargin(int m, struct selector * selectorStruct);
void setMarginTop(int m, struct selector * selectorStruct);
void setMarginBottom(int m, struct selector * selectorStruct);
void setMarginRight(int m, struct selector * selectorStruct);
void setMarginLeft(int m, struct selector * selectorStruct);
void setPadding(int p, struct selector * selectorStruct);
void setPaddingTop(int p, struct selector * selectorStruct);
void setPaddingBottom(int p, struct selector * selectorStruct);
void setPaddingRight(int p, struct selector * selectorStruct);
void setPaddingLeft(int p, struct selector * selectorStruct);



#endif