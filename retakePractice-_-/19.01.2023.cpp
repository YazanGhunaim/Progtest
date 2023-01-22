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

typedef struct ALL
{
    DICTIONARY *book;
    size_t booklen;
    CHECKED *text;
    size_t textlen;
} ALL;

int cmp(DICTIONARY *a, DICTIONARY *b)
{
    return ((*b).size < (*a).size) - ((*a).size < (*b).size);
}

int readDictionary(ALL *x)
{
    size_t bookMax = 105;
    printf("Dictionary:\n");
    while (69420)
    {
        if (scanf("%30s", x->book[x->booklen].word) != 1)
            return 1;
        x->book[x->booklen].size = strlen(x->book[x->booklen].word);
        if (strcmp(x->book[x->booklen].word, "*****") == 0)
            return 0;
        (x->booklen)++;
        if (x->booklen == bookMax)
        {
            bookMax = bookMax * 2 + 1;
            x->book = (DICTIONARY *)realloc(x->book, bookMax * sizeof(DICTIONARY));
        }
    }
}

void textRead(ALL *x)
{
    size_t textMax = 1000;
    int rowSize = 0;

    printf("Text:\n");
    while (69420)
    {
        char found = 0;
        if (scanf("%30s", x->text[x->textlen].word) != 1)
            return;
        x->text[x->textlen].size = strlen(x->text[x->textlen].word);
        for (size_t i = 0; i < x->booklen; ++i)
        {
            if (x->text[x->textlen].size == x->book[i].size)
            {
                if (strcasecmp(x->text[x->textlen].word, x->book[i].word) == 0)
                {
                    found = 1;
                    break;
                }
            }
        }
        if (found == 1)
        {
            if (x->textlen == 0)
            {
                printf("%s", x->text[x->textlen].word);
                rowSize = x->text[x->textlen].size;
            }
            else if ((rowSize + x->text[x->textlen].size + 1) > 80)
            {
                printf("\n%s", x->text[x->textlen].word);
                rowSize = x->text[x->textlen].size;
            }
            else
            {
                printf("%s", x->text[x->textlen].word);
                rowSize += x->text[x->textlen].size + 1;
            }
        }
        else
        {
            if (x->textlen == 0)
            {
                printf(" <err>%s</err>", x->text[x->textlen].word);
                rowSize = x->text[x->textlen].size + 11;
            }
            else if ((rowSize + x->text[x->textlen].size + 12) > 80)
            {
                printf(" \n <err>%s</err>", x->text[x->textlen].word);
                rowSize = x->text[x->textlen].size + 11;
            }
            else
            {
                printf(" <err>%s</err>", x->text[x->textlen].word);
                rowSize += x->text[x->textlen].size + 12;
            }
        }
        (x->textlen)++;

        if (x->textlen >= textMax)
        {
            textMax = textMax * 2 + 1;
            x->text = (CHECKED *)realloc(x->text, textMax * sizeof(CHECKED));
        }
    }
}
int main()
{
    ALL x;
    x.booklen = 0;
    x.book = (DICTIONARY *)malloc(105 * sizeof(DICTIONARY));

    if (readDictionary(&x))
    {
        printf(INVALID);
        free(x.book);
        return 1;
    }
    qsort((void *)x.book, x.booklen, sizeof(x.book[0]), (int (*)(const void *, const void *))cmp);

    x.text = (CHECKED *)malloc(1000 * sizeof(CHECKED));
    x.textlen = 0;

    textRead(&x);
    printf(" \n ");

    // Free on both dynamically allocated arrays
    free(x.book);
    free(x.text);
    return 0;
}
