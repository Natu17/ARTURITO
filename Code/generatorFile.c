#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/selector.h"
#include "include/generatorFile.h"
#include "../ErrorHandling/errorHandling.h"
#define MAX 4096

struct selector *selectors;
int size;

int newSelectors()
{
    selectors = malloc(MAX * sizeof(struct selector));
    if (selectors == NULL)
    {
        memoryAllocationErr();
        return -1;
    }
    size = 0;
    return 0;
    
}

void addSelectors(struct selector* s)
{
    if (size == MAX)
    {
        // agrando? o error?
    }
    selectors[size] = *s;
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
        setType(selectors[i],cssFile);
        fputs("{\n", cssFile);
        fprintf(cssFile, "\tcolor: #%x;\n", selectors[i].color);
        if (selectors[i].fontSize != DEF_FONT_SIZE)
        {
            fprintf(cssFile, "\tfont-size: %dpx;\n", selectors[i].fontSize);
        }
        fputs("\tmargin: ", cssFile);
        for (size_t j = 0; j < LEFT; j++)
        {
            fprintf(cssFile, "%dpx ", selectors[i].margin[j]);
        }

        fprintf(cssFile, "%dpx;\n", selectors[i].margin[LEFT]);

        fputs("\tpadding: ", cssFile);
        for (size_t j = 0; j < LEFT; j++)
        {
            fprintf(cssFile, "%dpx ", selectors[i].margin[j]);
        }

        fprintf(cssFile, "%dpx;\n", selectors[i].margin[LEFT]);

        fputs("}\n", cssFile);
    }
}

void setType(struct selector s, FILE * cssFile)
{
    if (s.type < CLASS)
    {
        fputs(types[s.type], cssFile);
        return;
    }
    else
    {
        char *string = malloc((strlen(s.name) + 1) * sizeof(char));
        if (s.type == CLASS)
        {
            string[0] = '#';
        }
        else
        {
            string[0] = '.';
        }
        strcat(string, s.name);
        fputs(string, cssFile);
        free(string);
        return;
    }
}

void closeFile(FILE *cssFile)
{
    fclose(cssFile);
}

// int main(int argc, char const *argv[])
// {

//     FILE *file = createCssFile();



//     struct selector *s = selectorInit(ID);
//     setName("hola", s);


    
//     setColor(0xCB905C, s);
//     setMarginRight(10, s);
//     setPadding(10, s);
//     newSelectors();
//     addSelectors(*s);
//     writeSelectors(file);
//     closeFile(file);
// }
