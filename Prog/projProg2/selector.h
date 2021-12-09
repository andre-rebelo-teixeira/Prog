#ifndef SELECTOR
#define SELECTOR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Struct.h"
#include "auxiliar.h"

VAR_DATA *trocaVAR(VAR_DATA *previous, VAR_DATA *after);
VAR_DATA *moreCases(VAR_DATA *start, FIX_DATA *helper2, char *indicator, int selectorMode);
void freeVarList(VAR_DATA *start);
int moreRecentData(VAR_DATA *first, VAR_DATA *second);

#endif