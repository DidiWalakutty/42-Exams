unsigned int	lcm(unsigned int a, unsigned int b)
{
	unsigned int n = 0;

	if (a == 0 || b == 0)
		return (0);
	if (a > b)
		n = a;
	else
		n = b;
	while (1)
	{
		if (n % a == 0 && n % b == 0)
			return (n);
		++n;
	}
}

#include <stdio.h>
int	main()
{
	unsigned int a = 12;
	unsigned int b = 18;

	printf("number is %i\n", lcm(a, b));
}