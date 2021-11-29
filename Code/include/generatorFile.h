
#ifndef GENERATOR_FILE_H
#define GENERATOR_FILE_H
#include <stdlib.h>
#include <stdio.h>

void closeFile(FILE * cssFile);
int newSelectors();
void addSelectors(struct selector* s);
FILE *createCssFile();
void writeSelectors(FILE *cssFile);
void setType(struct selector s, FILE * cssFile);

#endif