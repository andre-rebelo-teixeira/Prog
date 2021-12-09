#ifndef ALFA
#define ALFA

#include "Struct.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

FIX_DATA *alphabeticalOrganizator(FIX_DATA *start);
FIX_DATA *troca(FIX_DATA *left, FIX_DATA *right);
FIX_DATA *populationOrganizator(FIX_DATA *start, int mode);
FIX_DATA *casesOrganizator(FIX_DATA *start, int year, int week, char *indicator);

VAR_DATA *confirmaDatas(int year, int week, char *indicator, VAR_DATA *start);

#endif