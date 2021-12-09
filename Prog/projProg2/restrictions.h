#ifndef RESTRICTIONS
#define RESTRICTIONS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "Struct.h"
#include "sort.h"
#include "auxiliar.h"

FIX_DATA *filterByPopulation(FIX_DATA *startFixed, long populationRestriction, int mode);
FIX_DATA *filterByDates(FIX_DATA *startFixed, int year1, int year2, int week1, int week2);
FIX_DATA *removeOneFixData(FIX_DATA *head, char *countryName);
int confirmFirstData(int year1, int week1, int year2, int week2);

#endif