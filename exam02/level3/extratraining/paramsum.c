#include <unistd.h>

void	print_argc(int argc)
{
	char str[] = "0123456789";
	while (argc > 9)
		print_argc(argc / 10);
	write(1, &str[argc % 10], 1);
}

int	main(int argc, char **argv)
{
	(void)argv;
	print_argc(argc - 1);
	write(1, "\n", 1);
}