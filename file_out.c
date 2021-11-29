#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Code/include/selector.h"
#include "Code/include/generatorFile.h"
void main(){
	FILE file = createCssFile();
	newSelectors();
	writeSelectors(file);
	closeFile(file);
	}
	