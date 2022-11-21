#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */

#define NUM_OF_DAYS_IN_4000_YEARS 1460969 // Has 969 leap years in 4000 years --> (969 * 366 + 3031 * 365)
#define STRIKES_IN_ONE_DAY_BELL1 240
#define STRIKES_IN_ONE_DAY_BELL2 156

// functions to decide wether the year is a leap year or not according to specifications mentioned in progtest
int isLeapYear(int year)
{
    return (year % 4 == 0 && ((year % 100 != 0 || year % 400 == 0) && year % 4000 != 0));
}
// if a year turns out to be a leap year we get back 366 days
int getNumOfDaysInYear(int year)
{
    return isLeapYear(year) ? 366 : 365;
}

// An array to store the number of days in said month taking into account leapyears february "29"
int getNumOfDaysInMonth(int year, int month)
{
    if (month == 2 && isLeapYear(year))
        return 29;

    int months[] = {31,
                    28,
                    31,
                    30,
                    31,
                    30,
                    31,
                    31,
                    30,
                    31,
                    30,
                    31};

    return months[month - 1];
}

// convert all our inputs to a single integer "minutes", return value results in sum of minutes since beginning of the year
int MinutesConvert(int year, int month, int day, int hour, int minute)
{
    int result = 0;

    result += minute;
    result += hour * 60;
    result += day * 24 * 60;

    for (int i = 1; i < month; i++)
    {
        result += getNumOfDaysInMonth(year, i) * 24 * 60;
    }

    return result;
}

int countNumOfDaysSinceTheBeginning(int year, int month, int day)
{
    int result = 0;

    result += day;

    for (int i = 1; i < month; i++)
    {
        result += getNumOfDaysInMonth(year, i);
    }

    return result;
}
// returns 0 when day is sunday
int isSunday(int y, int m, int d)
{
    int weekday = (d += m < 3 ? y-- : y - 2, 23 * m / 9 + d + 4 + y / 4 - y / 100 + y / 400) % 7;
    return weekday;
}

long long NumOfDaysBetweenDates(int y1, int m1, int d1, int y2, int m2, int d2)
{
    long long daysDiff = 0;
    long long NumOfSaturdays = 0;

    if (y1 != y2)
    {
        // Remaining days to the end of the year
        daysDiff = getNumOfDaysInYear(y1) - countNumOfDaysSinceTheBeginning(y1, m1, d1);

        if (y2 - y1 > 4000)
        {
            // Skip chunks of 4000 years, every 4000 years have 969 leap years (969 * 366 + 3031 * 365)
            long long count = (y2 - y1) / 4000;

            daysDiff += count * NUM_OF_DAYS_IN_4000_YEARS;

            // Count for the unskippable reminder
            for (int i = y1 + 1 + (count * 4000); i < y2; i++)
            {
                daysDiff += getNumOfDaysInYear(i);
            }
        }
        else
        {
            for (int i = y1 + 1; i < y2; i++)
            {
                daysDiff += getNumOfDaysInYear(i);
            }
        }

        daysDiff += countNumOfDaysSinceTheBeginning(y2, m2, d2);
    }
    else
    {
        daysDiff = countNumOfDaysSinceTheBeginning(y2, m2, d2) - countNumOfDaysSinceTheBeginning(y1, m1, d1);
    }

    for (int i = 0; i < daysDiff; i++)
    {
        if (isSunday(y1, m1, d1) == 0)
        {
            NumOfSaturdays++;
        }
        d1++;
    }

    return daysDiff - NumOfSaturdays;
}

// void strikesPerDays(int y1, int m1, int d1,
//                     int y2, int m2, int d2,
//                     long long int *b1, long long int *b2)
// {
//     *b1 = NumOfDaysBetweenDates(y1, m1, d1, y2, m2, d2) * STRIKES_IN_ONE_DAY_BELL1;
//     *b2 = NumOfDaysBetweenDates(y1, m1, d1, y2, m2, d2) * STRIKES_IN_ONE_DAY_BELL2;
// }

long long countStrikesBetweenTimesb1(int initialHour, int initialMin, int endHour, int endMin)
{

    int currentHour = initialHour;
    int currentMin = initialMin;

    long long Strikes = 0;

    if (currentMin % 15 != 0)
    {
        int minsLeft = 15 - (currentMin % 15);
        currentMin += minsLeft;
        currentMin %= 60;
        switch (currentMin)
        {
        case 0:
            Strikes += 4;
            currentHour++;
            currentHour %= 24;
            break;
        case 15:
            Strikes += 1;
            break;
        case 30:
            Strikes += 2;
            break;
        case 45:
            Strikes += 3;
            break;
        default:
            return 1;
        }
    }

    else
    {
        switch (currentMin)
        {
        case 0:
            Strikes += 4;
            currentMin += 15;
            currentMin %= 60;
            break;
        case 15:
            Strikes += 1;
            currentMin += 15;
            currentMin %= 60;

            break;
        case 30:
            Strikes += 2;
            currentMin += 15;
            currentMin %= 60;
            break;
        case 45:
            Strikes += 3;
            currentHour++;
            currentHour %= 24;
            break;
        default:
            return 1;
        }
    }
    if (endMin == initialMin)
    {
        while (currentHour < endHour || currentMin <= endMin)
        {

            switch (currentMin)
            {
            case 0:
                Strikes += 4;
                currentHour++;
                currentHour %= 24;
                break;
            case 15:
                Strikes += 1;
                break;
            case 30:
                Strikes += 2;
                break;
            case 45:
                Strikes += 3;
                break;
            default:
                return 1;
            }
            currentMin += 15;

            currentMin %= 60;

            // if (currentMin == 0)
            // {
            //     currentHour++;
            //     currentHour %= 24;
            // }

            continue;
        }
    }
    else
    {
        while (currentHour < endHour || currentMin <= endMin)
        {

            switch (currentMin)
            {
            case 0:
                Strikes += 4;
                currentHour++;
                currentHour %= 24;
                break;
            case 15:
                Strikes += 1;
                break;
            case 30:
                Strikes += 2;
                break;
            case 45:
                Strikes += 3;
                break;
            default:
                return 1;
            }
            currentMin += 15;
            if (currentMin > 60)
            {
                currentMin %= 60;
            }

            continue;
        }
    }

    return Strikes;
}

long long countStrikesBetweenTimesb2(int initialHour, int initialMin, int endHour)
{

    long long Strikes = 0;

    int currentHour = initialHour;
    int currentMin = initialMin;

    if (currentMin == 0)
    {
        if (currentHour == 0)
        {
            Strikes += 12;
        }
        currentHour++;
        currentHour %= 24;
    }
    else
    {

        currentHour++;
        currentHour %= 24;
        if (currentHour == 0)
        {
            Strikes += 12;
            currentHour++;
        }

        while (currentHour <= endHour)
        {

            Strikes += currentHour % 12;
            currentHour++;
            currentHour %= 24;
            continue;
        }
    }

    return Strikes;
}

int inputValidator(int y1, int m1, int d1, int h1, int i1,
                   int y2, int m2, int d2, int h2, int i2)
{
    if (y1 < 1600 || y2 < 1600)
        return 0;
    if (m1 < 1 || m1 > 12 || m2 < 1 || m2 > 12)
        return 0;
    if (d1 < 1 || d1 > getNumOfDaysInMonth(y1, m1) || d2 < 1 || d2 > getNumOfDaysInMonth(y2, m2))
        return 0;
    if (h1 < 0 || h1 > 23 || h2 < 0 || h2 > 23)
        return 0;
    if (i1 < 0 || i1 > 59 || i2 < 0 || i2 > 59)
        return 0;

    // Check that second timestamp is after the first
    if (y1 > y2)
        return 0;

    // If years are the same, count minutes from beggining and compare those instead
    if (y1 == y2 &&
        MinutesConvert(y1, m1, d1, h1, i1) > MinutesConvert(y2, m2, d2, h2, i2))
        return 0;

    return 1;
}

//----------------------------------------

long long CountStrikesInEqEnd(int x, int y) // same hour
{

    long long int strikes = 0;

    if (x == 15 && y >= 45)
    {
        strikes += 6;
        return strikes;
    }

    else if (x == 15 && y >= 30)
    {
        strikes += 3;
        return strikes;
    }

    else if (x == 15 && y >= 15)
    {
        strikes += 1;
        return strikes;
    }

    if (x == 30 && y >= 45)
    {
        strikes += 5;
        return strikes;
    }

    else if (x == 30 && y >= 30)
    {
        strikes += 2;
        return strikes;
    }

    else if (x == 30 && y >= 30)
    {
        strikes += 2;
        return strikes;
    }

    if (x == 0 && y >= 45)
    {
        strikes += 10;
        return strikes;
    }

    else if (x == 0 && y >= 30)
    {
        strikes += 7;
        return strikes;
    }

    else if (x == 0 && y >= 15)
    {
        strikes += 5;
        return strikes;
    }
    else if (x == 0 && y < 15)
    {

        strikes += 4;
        return strikes;
    }

    if (x <= 14 && y >= 45)
    {
        strikes += 6;
        return strikes;
    }
    else if (x <= 14 && y >= 30)
    {
        strikes += 3;
        return strikes;
    }

    else if (x <= 14 && y >= 15)
    {
        strikes += 1;
        return strikes;
    }

    if (x <= 29 && y >= 45)
    {
        strikes += 5;
        return strikes;
    }
    else if (x <= 29 && y >= 30)
    {
        strikes += 2;
        return strikes;
    }

    if (x <= 45)
    {
        strikes += 4;
        return strikes;
    }
}

int countStrikesInit(int m)
{ // different hour
    if (m == 0)
        return 10;
    if (m == 15)
        return 6;
    if (m == 30)
        return 5;
    if (m == 45)
        return 3;
    else if (m < 14)
        return 6;
    else if (m < 29)
        return 5;
    else if (m < 44)
        return 3;
    else
        return 0;
}

int countStrikesEnd(int m)
{
    if (m <= 14)
        return 4;
    else if (m <= 29)
        return 5;
    else if (m <= 44)
        return 7;
    else
        return 10;
}

long long countStrikesEq(int initialMin, int endMin)
{
    long long strikes = CountStrikesInEqEnd(initialMin, endMin);

    return strikes;
}

long long countStrikes(int initialHour, int initialMin, int endHour, int endMin)
{
    long long strikes = countStrikesInit(initialMin) + countStrikesEnd(endMin);
    strikes += abs(abs(endHour - initialHour) - 1) * 10;

    return strikes;
}

//-----------------------------------------------------------

int bells(int y1, int m1, int d1, int h1, int i1,
          int y2, int m2, int d2, int h2, int i2,
          long long int *b1, long long int *b2)
{
    if (!inputValidator(y1, m1, d1, h1, i1, y2, m2, d2, h2, i2))
        return 0;

    *b1 = NumOfDaysBetweenDates(y1, m1, d1, y2, m2, d2) * STRIKES_IN_ONE_DAY_BELL1;
    *b2 = NumOfDaysBetweenDates(y1, m1, d1, y2, m2, d2) * STRIKES_IN_ONE_DAY_BELL2;

    if ((h1 * 60) + i1 < (h2 * 60) + i2)
    {
        // If second time is after the first, simply count between them
        *b1 += countStrikesBetweenTimesb1(h1, i1, h2, i2);
    }

    else
    {
        // Else if the second time is earlier then first (overlaps to next day)

        // Subrract 1 full day, we're going to add only portion of it
        *b1 -= STRIKES_IN_ONE_DAY_BELL1;
        *b1 -= STRIKES_IN_ONE_DAY_BELL2;

        // Count from h1:i1 to 23:59

        *b1 += countStrikesBetweenTimesb1(h1, i1, 23, 59);
        *b2 += countStrikesBetweenTimesb2(h1, i1, 23);
    }
    printf("bell1: %lld\nbell2:%lld\n", *b1, *b2);
    return 1;
}

#ifndef __PROGTEST__
int main(int argc, char *argv[])
{
    long long int b1, b2;

    assert(bells(2022, 10, 1, 13, 15,
                 2022, 10, 1, 18, 45, &b1, &b2) == 1 &&
           b1 == 56 && b2 == 20);
    assert(bells(2022, 10, 3, 13, 15,
                 2022, 10, 4, 11, 20, &b1, &b2) == 1 &&
           b1 == 221 && b2 == 143);
    assert(bells(2022, 10, 1, 13, 15,
                 2022, 10, 2, 11, 20, &b1, &b2) == 1 &&
           b1 == 106 && b2 == 65);
    assert(bells(2022, 10, 2, 13, 15,
                 2022, 10, 3, 11, 20, &b1, &b2) == 1 &&
           b1 == 115 && b2 == 78);
    assert(bells(2022, 10, 1, 13, 15,
                 2022, 10, 3, 11, 20, &b1, &b2) == 1 &&
           b1 == 221 && b2 == 143);
    assert(bells(2022, 1, 1, 13, 15,
                 2022, 10, 5, 11, 20, &b1, &b2) == 1 &&
           b1 == 56861 && b2 == 36959);
    assert(bells(2019, 1, 1, 13, 15,
                 2019, 10, 5, 11, 20, &b1, &b2) == 1 &&
           b1 == 57101 && b2 == 37115);
    assert(bells(2024, 1, 1, 13, 15,
                 2024, 10, 5, 11, 20, &b1, &b2) == 1 &&
           b1 == 57341 && b2 == 37271);
    assert(bells(1900, 1, 1, 13, 15,
                 1900, 10, 5, 11, 20, &b1, &b2) == 1 &&
           b1 == 57101 && b2 == 37115);
    assert(bells(2022, 10, 1, 0, 0,
                 2022, 10, 1, 12, 0, &b1, &b2) == 1 &&
           b1 == 124 && b2 == 90);
    assert(bells(2022, 10, 1, 0, 15,
                 2022, 10, 1, 0, 25, &b1, &b2) == 1 &&
           b1 == 1 && b2 == 0);
    assert(bells(2022, 10, 1, 12, 0,
                 2022, 10, 1, 12, 0, &b1, &b2) == 1 &&
           b1 == 4 && b2 == 12);
    assert(bells(2022, 11, 1, 12, 0,
                 2022, 10, 1, 12, 0, &b1, &b2) == 0 &&
           b1 == 4 && b2 == 12);
    assert(bells(2022, 10, 32, 12, 0,
                 2022, 11, 10, 12, 0, &b1, &b2) == 0 &&
           b1 == 4 && b2 == 12);
    assert(bells(2100, 2, 29, 12, 0,
                 2100, 2, 29, 12, 0, &b1, &b2) == 0 &&
           b1 == 4 && b2 == 12);
    assert(bells(2000, 2, 29, 12, 0,
                 2000, 2, 29, 12, 0, &b1, &b2) == 1 &&
           b1 == 4 && b2 == 12);
    assert(bells(2004, 2, 29, 12, 0,
                 2004, 2, 29, 12, 0, &b1, &b2) == 1 &&
           b1 == 0 && b2 == 0);
    assert(bells(2089, 11, 14, 0, 20,
                 2089, 11, 14, 0, 20, &b1, &b2) == 1 &&
           b1 == 0 && b2 == 0);
    assert(bells(2100, 12, 24, 0, 0,
                 2100, 12, 29, 0, 20, &b1, &b2) == 1 &&
           b1 == 964 && b2 == 636);
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
