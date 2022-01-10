#include <stdio.h>
#include <stdlib.h>
#include "bit_array.h"

void KnightTour();
static int KnightTourHelper(bitarray_t board, int x, int y, size_t num_of_strides,
							int xMove[8], int yMove[8], int sol[8][8]);
static int IsValidPosition(bitarray_t board, size_t x, size_t y);

void KnightTour()
{
	bitarray_t board = BitArrayResetAll();
	size_t i = 0, j = 0;
	/* next add to move for x and y coordinates */
	int xMove[8] = {2, 1, -1, -2, -2, -1, 1, 2};
	int yMove[8] = {1, 2, 2, 1, -1, -2, -2, -1};
	int x = rand() % 8;
	int y = rand() % 8;
	int sol[8][8];

	for (i = 0; i < 8; ++i)
	{
		for (j = 0; j < 8; ++j)
		{
			sol[i][j] = -1;
		}
	}

	board = BitArraySetOn(board, y * 8 + x);
	sol[x][y] = 0;

	srand(0);

	if (0 == KnightTourHelper(board, x, y, 1, xMove, yMove, sol))
	{
		printf("didnt work");
	}
	else
	{
		for (i = 0; i < 8; ++i)
		{
			for (j = 0; j < 8; ++j)
			{
				printf(" %d ", sol[i][j]);
			}
			printf("\n");
		}
	}
}

static int KnightTourHelper(bitarray_t board, int x, int y, size_t num_of_strides,
							int xMove[8], int yMove[8], int sol[8][8])
{
	size_t i = 0;
	int next_x = 0, next_y = 0;

	if (64 == num_of_strides)
	{
		return 1;
	}

	for (i = 0; i < 8; ++i)
	{
		if ((int)(x + xMove[i]) < 0)
		{
			continue;
		}
		next_x = ((int)x + xMove[i]);

		if ((int)(y + yMove[i]) < 0)
		{
			continue;
		}
		next_y = ((int)y + yMove[i]);


		if (IsValidPosition(board, next_x, next_y))
		{
			board = BitArraySetOn(board, next_y * 8 + next_x);
			sol[next_x][next_y] = num_of_strides;
			if (KnightTourHelper(board, next_x, next_y, num_of_strides + 1, xMove, yMove, sol))
			{
				return 1;
			}
			else
			{
				board = BitArraySetOff(board, next_y * 8 + next_x);
			}
		}
	}
	return 0;
}

static int IsValidPosition(bitarray_t board, size_t x, size_t y)
{
	return x <= 7 && y <= 7 && BitArrayGetValue(board, y * 8 + x) == 0;
}

int main()
{
	KnightTour();
	return 0;
}
