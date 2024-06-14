#include <unistd.h>

int	main(int argc, char **argv)
{
	int length = 0;
	if (argc == 2)
	{
		while (argv[1][length])
			length++;
		while (length != 0)
			write(1, &argv[1][--length], 1);
	}
	write(1, "\n", 1);
}