#include <stdio.h>
#include <stdlib.h>


int is_prime(int nbr)
{
    int i = 2;
    while (i < nbr)
    {
        if (nbr % i == 0)
            return 0;
        i++;
    }
    return 1;
}

int next_prime(int nbr)
{
    int i = 1;
    while (!is_prime(nbr + i))
        i++;
    return (nbr + i);
}

int main(int ac, char **av)
{
    int val = 1;
    int nbr1;
    int nbr;
    int prime = 2;
    if (ac == 2)
    {
        nbr1 = atoi(av[1]);
        if(is_prime(nbr1) || nbr1 <= 1)
        {
            printf("%d\n", nbr1);
            return 1;
        }
        else 
        {
            nbr = nbr1;
            while (val != nbr1)
            {
                if(nbr % prime == 0)
                {
                    nbr = nbr / prime;
                    val = val * prime;
                    printf("%d", prime);
                    if (val == nbr)
                        return 0;
                    printf("*");
                }
                else
                    prime = next_prime(prime);
            }
        }
    }
    printf("\n");
}