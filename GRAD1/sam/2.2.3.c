#include <stdio.h>

int main(void)
{
	int k;
	scanf("%d", &k);
	
	//printf("%d\n", i);
	unsigned long long sum, next_sum, term, n;
	next_sum = 0;
	n = 0;

	while (next_sum <= 2147483647)
	{
		sum = next_sum;
		n += 1;
		term = 1;
		for (int i = 1; i <= k; i++)
			term *= (2 * n);
		next_sum += term;
	}

	printf("%llu\n", sum);
	printf("%llu\n", n - 1);
	if (term > 2147483647)
		printf("*\n");
	else
		printf("+\n");
}
