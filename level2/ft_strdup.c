#include <stdlib.h>

char    *ft_strdup(char *src)
{
	char *copy;
	int i = 0;
	int length = 0;

	while (src[length])
		length++;
	copy = malloc(sizeof(*copy) * (length +1));
	if (!copy)
		return (NULL);
	while (src[i])
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}