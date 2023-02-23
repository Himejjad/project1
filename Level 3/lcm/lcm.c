unsigned int gcd(unsigned int a, unsigned int b)
{
    unsigned int temp;

    while (b != 0)
    {
        temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

unsigned int lcm(unsigned int a, unsigned int b)
{
    int tmp = a;
    int tmp2 = b;

    if (tmp <= 0 || tmp2 <= 0)
        return 0;
    return (a * b) / gcd(a, b);
}

#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    if (ac > 2)
    {
        unsigned int a = (unsigned int) atoi(av[1]);
        unsigned int b = (unsigned int) atoi(av[2]);
        printf("%d\n", lcm(a, b));
    }
}