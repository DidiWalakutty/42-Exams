#include <stdlib.h>

int	is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

char	*ft_strncpy(char *s1, char *s2, int n)
{
	int i = 0;
	while (i < n && s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

char    **ft_split(char *str)
{
	if (!str)
		return (NULL);
	int i = 0;
	int start = 0;
	int wc = 0;
	int	k = 0;
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
			i++;
		if (str[i])
			wc++;
		while (str[i] && !is_space(str[i]))
			i++;
	}
	char **out = malloc(sizeof(char *) * (wc + 1));
	if (!out)
		return (NULL);
	i = 0;
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
			i++;
		start = i;
		while (str[i] && !is_space(str[i]))
			i++;
		if (i > start)
		{
			out[k] = malloc(sizeof(char) * ((i - start) + 1));
			if (!out[k])
				return (NULL);
			ft_strncpy(out[k++], &str[start], i - start);
		}
	}
	out[k] = NULL;
	return (out);
}

#include <stdio.h>
int	main()
{
	char *str = "   It's\t as     clear\n\n as    the sunrise\t in Sedona";
	char **result;

	result = ft_split(str);
	int i = 0;
	while (result[i])
	{
		printf("Word %i: |%s|\n", i + 1, result[i]);
		i++;
	}
}