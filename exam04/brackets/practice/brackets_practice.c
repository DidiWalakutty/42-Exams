#include <unistd.h>

int	check_match(char a, char b)
{
	if ((a == '(' && b == ')') || (a == '{' && b == '}') || (a == '[' && b == ']'))
		return (0);
	return (1);
}

int	is_valid(char *str)
{
	int i = 0;
	int stack[4096];
	int top = 0;

	while (str[i])
	{
		if (str[i] == '(' || str[i] == '{' || str[i] == '[')
		{
			stack[top] = str[i];
			top++;
		}
		if (str[i] == ')' || str[i] == '}' || str[i] == ']')
		{
			if (top == 0 || check_match(stack[top - 1], str[i]) == 1)
				return (1);
			else
				top--;
		}
		i++;
	}
	if (top != 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc == 1)
		write(1, "\n", 1);
	int i = 1;
	while (argv[i])
	{
		if (is_valid(argv[i]) == 0)
			write(1, "OK\n", 3);
		else
			write(1, "Error\n", 6);
		i++;
	}
	return (0);
}