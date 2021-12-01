#include <stdlib.h>
#include "comparisonSorts.h"

static void swap(int *a, int *b);

void BubbleSort(int *a, size_t n)
{
    size_t i;
    size_t j;
    int swapped;

    for (i = 0; i < n; ++i)
    {
        swapped = 0;
        for (j = 1; j < n - i; ++j)
        {
            if (a[j] < a[j - 1])
            {
                swap(&a[j], &a[j - 1]);
                swapped = 1;
            }
        }
        if (!swapped)
        {
            return;
        }
    }
}

void InsertionSort(int *a, size_t n)
{
    size_t i;
    size_t j;
    for (i = 1; i < n; ++i)
    {
        for (j = i; a[j] < a[j - 1] && j > 0; --j)
        {
            swap(&a[j], &a[j - 1]);
        }
    }
}

void SelectionSort(int *a, size_t n)
{
    size_t curr_index_min;
    size_t i;
    size_t j;

    for (i = 0; i < n; ++i)
    {
        curr_index_min = i;
        for (j = i; j < n; ++j)
        {
            if (a[j] < a[curr_index_min])
            {
                curr_index_min = j;
            }
        }
        swap(&a[i], &a[curr_index_min]);
    }
}

static void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}