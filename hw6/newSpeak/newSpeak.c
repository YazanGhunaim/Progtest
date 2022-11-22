#ifndef __PROGTEST__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#endif /* __PROGTEST__ */


char *checkIfExists(const char *(*replace)[2], char *string)
{
    size_t numOfRows = 0;
    // finding the number of rows using endpoint NULL;
    for (int i = 0; *replace[i]; i++)
    {
        numOfRows++;
    }
    // printf("%zu\n", numOfRows);
    char *res;
    for (size_t i = 0; i < numOfRows; ++i)
    {
        res = strstr(string, *replace[i]);
        if (res)
        {
            break;
        }
    }
    return res;
}

char *m(const char *s)
{
    char *c = (char *)malloc(strlen(s) + 1);
    strcpy(c, s);
    return c;
}

int startWith(const char *string, const char *start)
{
    int string_length = strlen(string);
    int start_length = strlen(start);

    if (start_length > string_length)
        return 0;

    for (int i = 0; i < start_length; i++)
    {
        if (string[i] != start[i])
        {
            return 0;
        }
    }
    return 1;
}

int checkPrefix(const char *string, const char *(*replace)[2], size_t rows, size_t index)
{

    size_t lengthOfString = strlen(string);

    for (size_t i = 0; i < rows; i++)
    {
        if (i == index)
            continue;

        size_t lengthOfArrayString = strlen(*replace[i]);

        if (lengthOfString > lengthOfArrayString)
            continue;

        if (startWith((*replace[i]), string))
            return 0;
    }
    return 1;
}

int checkPrefixInArray(const char *(*replace)[2])
{

    size_t numOfRows = 0;
    // finding the number of rows using endpoint NULL;
    for (int i = 0; *replace[i]; i++)
    {
        numOfRows++;
    }

    for (size_t i = 0; i < numOfRows; ++i)
    {
        if (!checkPrefix(*replace[i], replace, numOfRows, i))
        {
            return 1;
        }
    }
    return 0;
}

char * newSpeak ( const char * text, const char * (*replace)[2] )
{
  char *res = m(text);
  
  if (checkPrefixInArray(replace))
    return NULL;
  
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  char * res;

  const char * d1 [][2] =
  {
    { "murderer", "termination specialist" },
    { "failure", "non-traditional success" },
    { "specialist", "person with certified level of knowledge" },
    { "dumb", "cerebrally challenged" },
    { "teacher", "voluntary knowledge conveyor" },
    { "evil", "nicenest deprived" },
    { "incorrect answer", "alternative answer" },
    { "student", "client" },
    { NULL, NULL }
  };


  const char * d2 [][2] =
  {
    { "fail", "suboptimal result" },
    { "failure", "non-traditional success" },
    { NULL, NULL }
  };


  res = newSpeak ( "Everybody is happy.", d1 );
  assert ( ! strcmp ( res, "Everybody is happy." ) );
  free ( res );

  res = newSpeak ( "The student answered an incorrect answer.", d1 );
  assert ( ! strcmp ( res, "The client answered an alternative answer." ) );
  free ( res );

  res = newSpeak ( "He was dumb, his failure was expected.", d1 );
  assert ( ! strcmp ( res, "He was cerebrally challenged, his non-traditional success was expected." ) );
  free ( res );

  res = newSpeak ( "The evil teacher became a murderer.", d1 );
  assert ( ! strcmp ( res, "The nicenest deprived voluntary knowledge conveyor became a termination specialist." ) );
  free ( res );

  res = newSpeak ( "Devil's advocate.", d1 );
  assert ( ! strcmp ( res, "Dnicenest deprived's advocate." ) );
  free ( res );

  res = newSpeak ( "Hello.", d2 );
  assert ( ! res );

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
