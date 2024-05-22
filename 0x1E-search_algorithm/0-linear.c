#include "search_algos.h"
#include <math.h>

/**
  * linear_search - Searches values in an array
  * of ints using linear search.
  * @array: A pointer
  * @size: Size of the array.
  * @value: The value to search for.
  *
  * Return: -1 if array is NULL
  */
int linear_search(int *array, size_t size, int value)
{
	unsigned int i;

	if (array == NULL)
		return (-1);

	for (i = 0; i < size; i++)
	{
		printf("Value checked array[%d] = [%d]\n", i, array[i]);
		if (array[i] == value)
			return (i);
	}

	return (-1);
}
