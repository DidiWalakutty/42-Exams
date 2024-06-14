#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	if (argc == 4)
	{
		if (argv[2][0] == '*')
		printf("%i", (atoi(argv[1]) * (atoi(argv[3]))));
	}
	write(1, "\n", 1);
}