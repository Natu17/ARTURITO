
#ifndef GENERATOR_FILE_H
#define GENERATOR_FILE_H
#include <stdlib.h>
#include <stdio.h>

FILE * createCssFile();
void closeFile(FILE * cssFile);
int newSelectors();
void addSelectors(struct selector s);
FILE *createCssFile();
void writeSelectors(FILE *cssFile);
const char * setType(struct selector s);

#endif