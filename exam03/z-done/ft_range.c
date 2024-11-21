#include <stdlib.h>
#include <stdio.h>

int     *ft_range(int start, int end)
{
	int size = 0;
	int i = 0;
	int *array;

	if (start <= end)
		size = end - start + 1;
	else
		size = start - end + 1;
	printf("size: %i\n", size);
	array = malloc(sizeof(int) * (size));
	if (!array)
		return (NULL);
	while (size--)
	{
		array[i] = start;
		if (start >= end)
			start--;
		else
			start++;
		i++;
	}
	array[i] = '\0';
	return (array);
}

int	main()
{
	int *array;
	array = ft_range(0, 0);
	int size = 1;
	int i = 0;
	while (i < size)
	{
		printf("array[%i]: %i\n", i, array[i]);
		i++;
	}
}