#include <stdio.h>
#define N 8

int solveKTUtil(int x, int y, int movei, int sol[N][N],
                int xMove[], int yMove[]);
int isSafe(int x, int y, int sol[N][N]);
void printSolution(int sol[N][N]);
int solveKT();
int solveKTUtil(int x, int y, int movei, int sol[N][N],
                int xMove[N], int yMove[N]);

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

    sol[0][0] = 0;

    if (solveKTUtil(0, 0, 1, sol, xMove, yMove) == 0)
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
    int k, next_x, next_y;
    if (N * N == movei)
        return 1;

    /* Try all next moves from the current coordinate x, y
     */
    for (k = 0; k < 8; k++)
    {
        next_x = x + xMove[k];
        next_y = y + yMove[k];
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
