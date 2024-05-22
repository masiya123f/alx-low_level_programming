/*
 * File: 100-jump.c
 * Auth: Brennan D Baraban
 */

#include "search_algos.h"
#include <math.h>

/**
  * jump_search - Searches for a value in a sorted array
  * of ints using jump search.
  * @array: A pointer
  * @size: Size the array.
  * @value: The value to search for.
  *
  * Return: If the value is not present or the array is NULL, -1
  */
int jump_search(int *array, size_t size, int value)
{
	size_t i, step;

	if (array == NULL || size == 0)
		return (-1);

	step = sqrt(size);
	for (i = 0; i < size && array[i] < value; i++)
	{
		printf("Value checked array[%ld] = [%d]\n", i, array[i]);
		i = i + step;
	}

	printf("Value found between indexes [%ld] and [%ld]\n", i, i + step);
	for (i = 0; i <= (i + step) && i < size; i++)
	{
		printf("Value checked array[%ld] = [%d]\n", i, array[i]);
		if (array[i] == value)
		{
			return (i);
		}
	}
	return (-1);
}
