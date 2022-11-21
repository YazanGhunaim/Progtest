/*
Matrix:
1 2 3
4 5 4
3 2 1
Horizontal symmetry: no
Vertical symmetry: no
Center symmetry: yes
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Max number of rows/columns
#define MAX 100
// Store hold up to 100*100 matrix elements hence 10000
#define store 10000
#define invalid "Invalid input.\n"

int centerSymmetry(int matrix[MAX][MAX], int rows, int columns);
int verticalSymmetry(int matrix[MAX][MAX], int rows, int columns);
int horizantalSymmetry(int matrix[MAX][MAX], int rows, int columns);
void readMatrix(int array[store], int matrix[MAX][MAX], int rows, int columns);
int RowsColumns(int array[store + 1], int *rows, int *columns);

int main()
{
    int matrix[MAX][MAX];
    int storage[store];
    int rows = 0;
    int columns = 0;

    // RowsColumns(storage, &rows, &columns);

    // printf("%d", storage[0]);
    // printf("\n%d %d\n", rows, columns);

    // int length = rows * columns;

    printf("Matrix:\n");
    if (RowsColumns(storage, &rows, &columns) || rows < 0 || rows > MAX || columns > MAX)
    {
        printf(invalid);
        return EXIT_FAILURE;
    }

    readMatrix(storage, matrix, rows, columns);

    if (horizantalSymmetry(matrix, rows, columns))
    {
        printf("Horizontal symmetry: yes\n");
    }
    else
    {
        printf("Horizontal symmetry: no\n");
    }
    if (verticalSymmetry(matrix, rows, columns))
    {
        printf("Vertical symmetry: yes\n");
    }
    else
    {
        printf("Vertical symmetry: no\n");
    }
    if (centerSymmetry(matrix, rows, columns))
    {
        printf("Center symmetry: yes\n");
    }
    else
    {
        printf("Center symmetry: no\n");
    }

    return 0;
}

int RowsColumns(int array[store + 1], int *rows, int *columns)
{
    int c = 0;
    double spaces = 0;
    double newLines = 0;
    int count = 0;
    double data;
    int j = 0;
    while ((scanf("%lf", &data) == 1) && ((c = getchar()) != EOF))
    {
        if (fmod(data, 1) != 0)
        {
            return 1;
        }

        array[j] = data;
        if (c == ' ' || c == '\t')
        {
            ++spaces;
        }

        if (c == '\n')
        {
            ++newLines;
        }
        j++;
        count ++;
    }
    if (!feof(stdin))
    {
        return 1;
    }
    if (fmod(((spaces / newLines) + 1), 1) != 0)
    {
        return 1;
    }
    *rows = newLines;
    *columns = (spaces / newLines) + 1;
    return 0;
}

/*
    @brief: function takes input matrix pointer to head and ask for inputs from the user
            for each element of the initialized matrix.
*/
void readMatrix(int array[store], int matrix[MAX][MAX], int rows, int columns)
{

    int k = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
        {
            k = i * columns + j;
            matrix[i][j] = array[k];
            // if (scanf("%d", &data) != 1)
            // {
            //     return 1;
            // }
            // else
            // {
            //     matrix[i][j] = data;
            // }
        }
}

/*
@brief: function takes matrix as parameter and returns 1 if
        matrix is horizantally symmetric and 0 otherwise
*/
int horizantalSymmetry(int matrix[MAX][MAX], int rows, int columns)
{
    for (int i = 0, k = rows - 1; i < rows / 2; ++i, --k)
    {
        for (int j = 0; j < columns; ++j)
        {
            if (matrix[i][j] != matrix[k][j])
            {

                return 0;
            }
        }
    }
    return 1;
}

/*
@brief: function takes matrix as parameter and returns 1 if
        matrix is vertically symmetric and 0 otherwise
*/
int verticalSymmetry(int matrix[MAX][MAX], int rows, int columns)
{

    for (int j = 0, k = columns - 1; j < columns / 2; ++j, --k)
    {
        for (int i = 0; i < rows; ++i)
        {
            if (matrix[i][j] != matrix[i][k])
            {
                return 0;
            }
        }
    }
    return 1;
}

/*
@brief: only with n*n matrices, returns 1 if its centosymmetric else 0
*/
int centerSymmetry(int matrix[MAX][MAX], int rows,int columns)
{

    // int middleRow = 0;

    // if (rows & 1)
    //     middleRow = rows / 2 + 1;
    // else
    //     middleRow = rows / 2;

    for (int i = 0; i < rows/2 ; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (matrix[i][j] != matrix[rows - i - 1][columns - j - 1])
                return 0;
        }
    }

    return 1;
}

