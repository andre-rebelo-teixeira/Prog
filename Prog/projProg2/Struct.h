#ifndef STRUCT
#define STRUCT

#define COUNTRYNAME 64
#define COUNTRYCODE 5
#define CONTINENT 25
#define INDICATOR 10
typedef struct fixed
{
    char countryName[COUNTRYNAME];
    char countryCode[COUNTRYCODE];
    char continent[CONTINENT];
    long population;
    struct fixed *next; //proximo país
    struct variable *data;
} FIX_DATA;

//used to store the diferent variable values
typedef struct variable
{
    int year;
    int week;
    int weeklyCount;
    int cumulativeCount;
    double rate2Weeks;
    struct variable *next;
    char indicator[INDICATOR];
} VAR_DATA;

#endif