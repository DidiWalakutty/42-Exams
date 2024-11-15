#include <stdlib.h>

int *ft_rrange(int start, int end)
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
		array[i] = end;
		if (start <= end)
			end--;
		else
			end++;
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

    // Test ft_rrange
    range = ft_rrange(1, 3);
    size = 3;
	i = 0;
	printf("New input:\n");
	while (i < size)
	{
		printf("Array[%i]: %i\n", i, range[i]);
		i++;
	}
    free(range);

	// New ft_rrange test
    range = ft_rrange(-4, 3);
    size = 8;
	i = 0;
	printf("\nNew input:\n");
	while (i < size)
	{
		printf("Array[%i]: %i\n", i, range[i]);
		i++;
	}
    free(range);

    return 0;
}