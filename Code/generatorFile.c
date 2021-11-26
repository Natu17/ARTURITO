#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/selector.h"
#include "include/generatorFile.h"
#define MAX 4096

struct selector *selectors;
int size;

int newSelectors()
{
    selectors = malloc(MAX * sizeof(struct selector));
    if (selectors == NULL)
    {
        perror("Error! memory not allocated.");
        return -1;
    }
    return 0;
    size = 0;
}

void addSelectors(struct selector s)
{
    if (size == MAX)
    {
        // agrando? o error?
    }
    selectors[size] = s;
    size++;
}

FILE *createCssFile()
{
    FILE *cssFile;
    cssFile = fopen("StyleSheet.css", "w");
    return cssFile;
}

void writeSelectors(FILE *cssFile)
{
    for (size_t i = 0; i < size; i++)
    {
        fputs(setType(selectors[i]),cssFile);
        fputs("{\n",cssFile);
        fprintf(cssFile, "\tcolor: #%x;\n", selectors[i].color);
        if(selectors[i].fontSize != DEF_FONT_SIZE){
            fprintf(cssFile, "\tfont-size: %dpx;\n", selectors[i].fontSize);
        }
        fputs("\tmargin: ",cssFile);
        for (size_t j = 0; j < LEFT ; j++)
        {
            fprintf(cssFile, "%dpx ", selectors[i].margin[j]); 
        }

        fprintf(cssFile, "%dpx;\n", selectors[i].margin[LEFT]); 

        fputs("\tpadding: ",cssFile);
        for (size_t j = 0; j < LEFT ; j++)
        {
            fprintf(cssFile, "%dpx ", selectors[i].margin[j]); 
        }

        fprintf(cssFile, "%dpx;\n", selectors[i].margin[LEFT]);
        
        fputs("}\n",cssFile);
    }
}

const char * setType(struct selector s){
    if(s.type < CLASS){
        return types[s.type];
    }else{
        if(s.type == CLASS){
            return strncat("#", s.name, 1);
        }else{
             return strncat(".", s.name, 1);
        }
    }
}

void closeFile(FILE *cssFile)
{
    fclose(cssFile);
}

int main(int argc, char const *argv[])
{
    
    FILE * file = createCssFile();
    struct selector * s = selectorInit(H1);
    setColor(0xCB905C,s);
    setMarginRight(10,s);
    setPadding(10,s);
    newSelectors();
    addSelectors(*s);
    writeSelectors(file);
    closeFile(file);

}

