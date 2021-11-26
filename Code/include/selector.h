
#ifndef SELECTOR_H
#define SELECTOR_H
#define DEF_FONT_SIZE 16

struct selector
{
    int type;
    int color;
    int fontSize;
    int margin[4];
    int padding[4];
    char * name;
};

enum type
{
    H1,
    H2,
    BODY,
    P,
    DIV,
    CLASS,
    ID,

};

enum orientation
{
    TOP,
    BOTTOM,
    RIGHT,
    LEFT,
};

const char *types[];
struct selector *selectorInit(int type);
void setColor(int color, struct selector *selectorStruct);
void setFontSize(int font, struct selector *selectorStruct);
void setMargin(int m, struct selector *selectorStruct);
void setMarginTop(int m, struct selector *selectorStruct);
void setMarginBottom(int m, struct selector *selectorStruct);
void setMarginRight(int m, struct selector *selectorStruct);
void setMarginLeft(int m, struct selector *selectorStruct);
void setPadding(int p, struct selector *selectorStruct);
void setPaddingTop(int p, struct selector *selectorStruct);
void setPaddingBottom(int p, struct selector *selectorStruct);
void setPaddingRight(int p, struct selector *selectorStruct);
void setPaddingLeft(int p, struct selector *selectorStruct);
void setName(char * name, struct selector * selectorStruct);

#endif