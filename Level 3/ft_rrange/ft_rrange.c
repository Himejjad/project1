#include <stdlib.h>

int *ft_rrange(int start, int end)
{
	int *range;
	int i = 0;
	int n = end - start ;

	if (n < 0)
		n = n * (-1);
	range = (int *)malloc(sizeof(int ) * (n + 1));
	if (range)
	{
		while (i <= n)
		{
			range[i] = end;
			end--;
			i++;
		}
	}
	return (range);
}
