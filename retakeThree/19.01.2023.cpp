#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INVALID "Invalid input.\n"

typedef struct dictionary
{
    char word[31];
    int size;
} DICTIONARY;

typedef struct checked
{
    char word[31];
    int size;
} CHECKED;

typedef struct all
{
    DICTIONARY *book;
    int bookLen;
    CHECKED *text;
    int textLen;
} ALL;

int cmp(DICTIONARY *a, DICTIONARY *b)
{
    return ((*b).size < (*a).size) - ((*a).size < (*b).size);
}

int readDictionary(ALL *x)
{
    DICTIONARY read;
    int initialSize = 3;
    printf("Dictionary:\n");
    while (69420)
    {
        if (scanf("%30s", read.word) != 1)
        {
            return 0;
        }
        read.size = strlen(read.word);
        if (strcmp(read.word, "*****") == 0)
        {
            return 1;
        }
        if (x->bookLen == initialSize)
        {
            initialSize = initialSize * 2 + 1;
            x->book = (DICTIONARY *)realloc(x->book, initialSize * sizeof(DICTIONARY));
        }
        x->book[x->bookLen] = read;
        (x->bookLen)++;
    }
    if (!feof(stdin))
    {
        return 0;
    }
    return 1;
}

void readText(ALL *x)
{
    int rowSize = 0;
    int initialSize = 3;
    CHECKED read;
    printf("Text:\n");
    while (69420)
    {
        if (scanf("%30s", read.word) != 1)
        {
            return;
        }
        read.size = strlen(read.word);
        if (x->textLen == initialSize)
        {
            initialSize = initialSize * 2 + 1;
            x->text = (CHECKED *)realloc(x->text, initialSize * sizeof(CHECKED));
        }
        x->text[x->textLen] = read;
        // ---//
        int found = 0;
        for (int i = 0; i < x->bookLen; ++i)
        {
            if (x->text[x->textLen].size == x->book[i].size)
            {
                if (strcasecmp(x->text[x->textLen].word, x->book[i].word) == 0)
                {
                    found = 1;
                    break;
                }
            }
        }
        if (found)
        {
            if (x->textLen == 0)
            {
                printf("%s", x->text[x->textLen].word);
                rowSize = x->text[x->textLen].size;
            }
            else if ((rowSize + x->text[x->textLen].size + 1) > 80)
            {
                printf("\n%s", x->text[x->textLen].word);
                rowSize = x->text[x->textLen].size;
            }
            else
            {
                printf(" %s", x->text[x->textLen].word);
                rowSize += x->text[x->textLen].size + 1;
            }
        }
        if (!found)
        {
            if (x->textLen == 0)
            {
                printf("<err>%s</err>", x->text[x->textLen].word);
                rowSize = x->text[x->textLen].size + 11;
            }
            else if ((rowSize + x->text[x->textLen].size + 12) > 80)
            {
                printf("\n<err>%s</err>", x->text[x->textLen].word);
                rowSize = x->text[x->textLen].size + 11;
            }
            else
            {
                printf(" <err>%s</err>", x->text[x->textLen].word);
                rowSize += x->text[x->textLen].size + 12;
            }
        }
        (x->textLen)++;
    }
}
int main()
{
    ALL x;
    x.book = (DICTIONARY *)malloc(3 * sizeof(DICTIONARY));
    x.bookLen = 0;
    if (!readDictionary(&x))
    {
        printf(INVALID);
        free(x.book);
        return 1;
    }
    //--//
    qsort((void *)x.book, x.bookLen, sizeof(x.book[0]), (int (*)(const void *, const void *))cmp);
    x.text = (CHECKED *)malloc(3 * sizeof(CHECKED));
    x.textLen = 0;
    readText(&x);
    printf("\n");
    //--//
    free(x.book);
    free(x.text);
    return 0;
}
