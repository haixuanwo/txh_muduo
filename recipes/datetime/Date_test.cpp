
#include "Date.h"
#include <stdio.h>
#include <stdlib.h>

using namespace muduo;

int main(int argc, char* argv[])
{
    if (2 == argc)
    {
        int jdn = atoi(argv[1]);
        Date date(jdn);
        printf("%d-%d-%d\n", date.year(), date.month(), date.day());
        printf("%s\n", date.toIsoString().c_str());
    }
    else if (4 == argc)
    {
        int year = atoi(argv[1]);
        int month = atoi(argv[2]);
        int day = atoi(argv[3]);
        Date date(year, month, day);
        printf("%d\n", date.julianDayNumber());
    }
    else
    {
        printf("Usage: %s julian_day_number | year month day\n", argv[0]);
    }
}

/*

$ ./date_test 2000 1 1
2451545
$ ./date_test 2451545
2000-1-1
2000-01-01

*/