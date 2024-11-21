#include <stdlib.h>

int     *ft_rrange(int start, int end)
{
	int size = 0;
	int i = 0;
	int *array;

	if (start <= end)
		size = end - start + 1;
	else
		size = start - end + 1;
	array = malloc(sizeof(int) * (size));
	if (!array)
		return (NULL);
	while (size--)
	{
		array[i] = end;
		if (start >= end)
			end++;
		else
			end--;
		i++;
	}
	array[i] = '\0';
	return (array);
}

#include <stdio.h>
int	main()
{
	int size = 0;
	int i = 0;
	int *array;

	array = ft_rrange(0, -3);
	size = 4;
	while (i < size)
	{
		printf("array[%i]: %i\n", i, array[i]);
		i++;
	}
}