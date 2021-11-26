
#ifndef SELECTOR_H
#define SELECTOR_H

struct selector * selectorInit(int type);
int setColor(int color, struct selector * selectorStruct);
int setFontSize(char * font, struct selector * selectorStruct);
int setMargin(int m, struct selector * selectorStruct);
int setPadding(int p, struct selector * selectorStruct);

#endif