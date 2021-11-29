#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Code/include/selector.h"
#include "Code/include/generatorFile.h"
int main(){
	FILE * file = createCssFile();
	newSelectors();
	int n = 3;
struct selector *h = selectorInit(H1);
setColor(13340764, h );
setMarginTop(n , h );
setMarginLeft(n , h );
setPadding(n , h );
addSelectors(h );
writeSelectors(file);
	closeFile(file);
	}
	