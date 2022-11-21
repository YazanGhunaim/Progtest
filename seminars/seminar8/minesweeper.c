/*
Enter game board:
.....*....
..****....
..*..*..*.
..***..*.*
..*.***...
..***.*...
Filled board:
.1234*2...
.2****3111
.3*76*32*2
.3***54*3*
.3*8***321
.2***5*2..
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char *readFirstLine(int maxSize, int *col)
{
    char symbol;
    char *tmp = NULL;
    char *line = (char *)malloc(maxSize * sizeof(char));

    while (true)
    {
        if (*col > maxSize)
        {
            // line bigger than expected -> increase buffer

            maxSize *= 2;

            tmp = (char *)realloc(line, maxSize * sizeof(char));
            line = tmp;
        }

        symbol = getchar();

        if (*col == 1 && symbol == EOF) // board with zero width
        {
            printf("Invalid input.\n");
            free(line);
            return NULL;
        }

        if (symbol == '\n') // end of line
        {
            *col -= 1;
            return line;
        }

        if (symbol != '*' && symbol != '.')
        {
            printf("Invalid input.\n");
            free(line);
            return NULL;
        }

        line[*col - 1] = symbol;
        *col += 1;
    }
}

char *readLine(int col, bool *eof)
{
    char *line = (char *)malloc(col * sizeof(char));
    char symbol;

    for (int j = 0; j < col; j++)
    {
        symbol = getchar();

        if (j == 0 && symbol == EOF) // No further data
        {
            *eof = true;
            free(line);
            return NULL;
        }

        if (symbol == '\n') // shorter line than expected
        {
            printf("Invalid input.\n");
            free(line);
            return NULL;
        }

        if (symbol != '.' && symbol != '*')
        {
            printf("Invalid input.\n");
            free(line);
            return NULL;
        }

        line[j] = symbol;
    }

    // last element has to be a new line otherwise the line is longer than expected

    if (getchar() != '\n')
    {
        printf("Invalid input.\n");
        free(line);
        return NULL;
    }

    return line;
}

char **buildBoard(int maxSize, int *row, int *col)
{
    char **tmp = NULL;
    char **board = (char **)malloc(maxSize * sizeof(char *));

    // first line will determine the size of columns

    board[0] = readFirstLine(maxSize, col);
    if (board[0] == NULL)
    {
        free(board);
        return NULL;
    }

    bool eof = false;
    // read following lines until eof

    while (!eof)
    {
        if (*row >= maxSize)
        {
            // more rows than expected.. increase buffer
            maxSize *= 2;
            tmp = (char **)realloc(board, maxSize * sizeof(char *));

            board = tmp;
        }

        *row += 1;
        board[*row - 1] = readLine(*col, &eof);

        if (board[*row - 1] == NULL && !eof) // invalud input, destroy board
        {
            for (int i = *row - 1; i >= 0; i--)
            {
                free(board[i]);
            }

            free(board);
            return NULL;
        }
    }

    // removing row count from EOF

    *row -= 1;
    return board;
}

void fillBoard(char **result, char **board, int row, int col)
{
    int index[3] = {-1, 0, 1};

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; i < col; j++)
        {
            if (board[i][j] == '*')
            {
                result[i][j] == '*';
            }
            else
            {
                int bombs = 0;
                int s1 = 0;
                int s2 = 0; // pointers to index
                int e1 = 2;
                int e2 = 2;

                // check boundaries, paying attention to corners
                if (i == 0)
                {
                    s1 = 1; // remove i - 1
                }
                if (i == row - 1)
                {
                    e1 = 1; // remove i +1
                }
                if (j == 0)
                {
                    s2 = 1; // remove j -1
                }
                if (j == col - 1)
                {
                    e2 = 1; // remove j+1
                }

                for (int k = s1; k <= e1; ++k)
                {
                    for (int m = s2; m <= e2; ++m)
                    {
                        if (board[i + index[k]][j + index[m]] == '*')
                        {
                            bombs++;
                        }
                    }

                    // update result

                    if (bombs == 0)
                    {
                        result[i][j] == '.';
                    }
                    else
                    {
                        result[i][j] = bombs + '0'; // max bombs is 8, no need to fix ascii table
                    }
                }
            }
        }
    }
    return;
}

int main()
{

    int maxSize = 100;
    int col = 1;
    int row = 1;
    char **board;

    printf("Enter game board:\n");
    board = buildBoard(maxSize, &row, &col);
    if (board == NULL)
    {
        free(board);
        return 1;
    }

    // Building result board

    char **result = (char **)malloc(row * sizeof(char));
    for (int i = 0; i < row; i++)
    {
        result[i] = (char *)malloc(col * sizeof(char));
    }

    fillBoard(result, board, row, col);

    printf("Filled Board:\n");
}