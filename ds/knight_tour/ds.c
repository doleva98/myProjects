#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#define N 8

int solveKTUtil(int x, int y, int movei, int sol[N][N],
                int xMove[], int yMove[]);
int isSafe(int x, int y, int sol[N][N]);
void printSolution(int sol[N][N]);
int solveKT();
int solveKTUtil(int x, int y, int movei, int sol[N][N],
                int xMove[N], int yMove[N]);
static void getNextBestCoordinates(int *x, int *y, int sol[N][N],
                                   int xMove[N], int yMove[N],
                                   int nextXMove[N], int nextYMove[N]);

/* Driver Code */
int main()
{
    solveKT();
    return 0;
}

int isSafe(int x, int y, int sol[N][N])
{
    return (x >= 0 && x < N && y >= 0 && y < N && sol[x][y] == -1);
}

void printSolution(int sol[N][N])
{
    int x = 0, y = 0;
    for (x = 0; x < N; x++)
    {
        for (y = 0; y < N; y++)
            printf(" %2d ", sol[x][y]);
        printf("\n");
    }
}

int solveKT()
{
    int sol[N][N];
    int x = 0, y = 0;

    int xMove[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int yMove[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    for (x = 0; x < N; x++)
        for (y = 0; y < N; y++)
            sol[x][y] = -1;

    srand(0);

    x = 4;
    y = 4;

    sol[x][y] = 0;

    if (solveKTUtil(x, y, 1, sol, xMove, yMove) == 0)
    {
        printf("Solution does not exist");
        return 0;
    }
    else
        printSolution(sol);

    return 1;
}

int solveKTUtil(int x, int y, int movei, int sol[N][N],
                int xMove[N], int yMove[N])
{
    int k, next_x = x, next_y = y;
    int nextXMove[8] = {0};
    int nextYMove[8] = {0};
    if (N * N == movei)
    {
        return 1;
    }

    /* Try all next moves from the current coordinate x, y
     */

    getNextBestCoordinates(&next_x, &next_y, sol, xMove, yMove, nextXMove,
                           nextYMove);
    for (k = 0; k < 8; k++)
    {
        next_x = x;
        next_y = y;
        /* next_x = x + xMove[k];
        next_y = y + yMove[k]; */
        next_x += nextXMove[k];
        next_y += nextYMove[k];

        if (isSafe(next_x, next_y, sol))
        {
            sol[next_x][next_y] = movei;
            if (solveKTUtil(next_x, next_y, movei + 1, sol,
                            xMove, yMove) == 1)
            {
                return 1;
            }
            else
            {
                sol[next_x][next_y] = -1; /* backtracking*/
            }
        }
    }

    return 0;
}

static void getNextBestCoordinates(int *x, int *y, int sol[N][N],
                                   int xMove[N], int yMove[N],
                                   int *nextXMove, int *nextYMove)
{
    int coordinates[N] = {0};
    int i = 0, j = 0;
    int min;
    int save_min_index;
    for (i = 0; i < N; ++i)
    {
        for (j = 0; j < N; ++j)
        {
            if (isSafe(*x + xMove[i] + xMove[j], *y + yMove[i] + xMove[j], sol))
            {
                ++coordinates[i];
            }
        }
    }
    for (i = 0; i < N; ++i)
    {
        save_min_index = i;
        min = INT_MAX - 1;

        for (j = 0; j < N; ++j)
        {
            if (min > coordinates[j])
            {
                save_min_index = j;
                min = coordinates[j];
            }
        }
        if (INT_MAX - 1 == min)
        {
            continue;
        }
        nextXMove[i] = xMove[save_min_index];
        nextYMove[i] = yMove[save_min_index];
        coordinates[save_min_index] = INT_MAX;
    }
}