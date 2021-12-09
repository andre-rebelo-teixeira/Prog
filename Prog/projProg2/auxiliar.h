#ifndef AUXILIAR
#define AUXILIAR

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Struct.h"

void Cleanup(FIX_DATA *startFixed);
VAR_DATA *removeVarNode(VAR_DATA *varHead, VAR_DATA *freeMe);
FIX_DATA *confirmCountry(FIX_DATA *start, FIX_DATA *objective);
void confirmToken(int selector, char token[], FIX_DATA *startFixed, FILE *pToFile, FIX_DATA *newest, VAR_DATA *newestVar);
void removeVarDataList(VAR_DATA *head);
int confirmInput(char *input);

#endif
