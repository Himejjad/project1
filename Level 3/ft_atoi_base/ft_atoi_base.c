int    ft_check(char c, int base)
{
    char con[17] = "0123456789abcdef";
    char con_u[17] = "0123456789ABCDEF";
    int i = 0;
    while (i < base)
    {
        if(c == con[i] || c == con_u[i])
            return 0;
        i++;
    }
    return 1;
}

int ft_index(char c)
{
    char con[17] = "0123456789abcdef";
    char con_u[17] = "0123456789ABCDEF";
    int i = 0;
    while (con[i])
    {
        if(con[i] == c || c == con_u[i])
            return i;
        i++;
    }
    return i;
}

int    ft_atoi_base(const char *str, int str_base)
{
    int power;
    int i = 0;
    int sign = 1;
    int ret = 0;
    
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' || str[i] == '\n'
        || str[i] == '\r' || str[i] == '\f')
        i++;
    if(str[i] == '+' || str[i] == '-')
    {
        if(str[i] == '-')
            sign = -1;
        i++;
    }
    
    while (!ft_check(str[i], str_base))
    {
        ret = ret * str_base + ft_index(str[i]);
        i++;
    }
    return (ret * sign);
}

#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    if(ac > 1)
    {
        int base = atoi(av[2]);
        printf("%d\n", ft_atoi_base(av[1], base));
    }
    return 0;
}