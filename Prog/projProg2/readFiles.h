#ifndef READFILES
#define READFILES

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "add.h"
#include "Struct.h"
#include "add.h"

#define MAX 200

FIX_DATA *ReadInBynary(char *name);
FIX_DATA *ReadInCSV(char *name, char *continent, int mode);

#endif
