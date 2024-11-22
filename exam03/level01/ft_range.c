#include <stdlib.h>

int     *ft_range(int start, int end)
{
	int	*array;
	int size;
	int i;
	if (start <= end)
		size = end - start + 1;
	else
		size = start - end + 1;
	array = malloc(sizeof(int) * (size));
	if (!array)
		return (NULL);
	i = 0;
	while (size--)
	{
		array[i] = start;
		if (start >= end)
			start--;
		else
			start++;
		i++;
	}
	return (array);
}

#include <stdio.h>
int main(void)
{
    int *range;
    int size;
	int	i;

    // Test ft_range
    range = ft_range(1, 3);
    size = 3;
	i = 0;
	printf("New input:\n");
	while (i < size)
	{
		printf("Array[%i]: %i\n", i, range[i]);
		i++;
	}
    free(range);

	// New ft_range test
	printf("\nNew input:\n");
    range = ft_range(-4, 3);
    size = 8;
	i = 0;
	while (i < size)
	{
		printf("Array[%i]: %i\n", i, range[i]);
		i++;
	}
    free(range);

    return 0;
}