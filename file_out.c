#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Code/include/selector.h"
#include "Code/include/generatorFile.h"
void main(){
	FILE file = createCssFile();
	newSelectors();
	struct selector *l = selectorInit(id);
addSelectors(l );
setName("hola", l );
double dou = 2.20;
char * h = "hello";
int w = 8;
writeSelectors(file);
	closeFile(file);
	}
	