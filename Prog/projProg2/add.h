#ifndef ADD
#define ADD

#define _GNU_SOURCE

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "auxiliar.h"
#include "Struct.h"
#include "reader.h"

#define MAX 200

FIX_DATA *addNodeFixed(FIX_DATA *previous, FILE *pToFile, VAR_DATA *start, char input[MAX], FIX_DATA *startFixed, int readingMode, char continent[]);

VAR_DATA *addNodeVariable(VAR_DATA *previous, char input[MAX], FIX_DATA *startFixed, FILE *pToFile, FIX_DATA *newest);

#endif