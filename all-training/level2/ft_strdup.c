#include <stdlib.h>

char    *ft_strdup(char *src)
{
	int i = 0;
	int len = 0;
	char *copy;

	if (!src)
		return (NULL);
	while (src[len])
		len++;
	copy = malloc(sizeof(*copy) * (len + 1));
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