/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parce.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 04:45:55 by himejjad          #+#    #+#             */
/*   Updated: 2023/05/12 05:49:35 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofer.h"


int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	ft_error(void)
{
	write(2, "ERROR\n", 7);
	exit(1);
}

void	ft_check_numbers(char *str, int i)
{
	if ((str[i] != '\0' && (str[i] > '9' || str[i] < '1') && str[i] != ' ')
		|| (ft_strlen(str) == 0))
		ft_error();
	if ((str[i] == '-') || (str[i] == '+'))
		ft_error();
	if ((str[i] == '\0' || str[i] == ' ')
		&& (str[i - 1] == '-' || str[i - 1] == '+'))
		ft_error();
}

int	ft_atoi(char *str)
{
	long long		result;
	int				i;
	int				sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		sign *= -1;
		i++;
	}
	while (str[i] >= '1' && str[i] <= '9')
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	ft_check_numbers(str, i);
	result = result * sign;
	if (result > 2147483647 || result < -2147483648)
		ft_error();
	return (result);
}

char	*ft_strjoin(char	*s1, char	*s2)
{
	char	*join;
	int		len;
	int		x;
	int		j;
	int		i;

	x = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	join = malloc(len + 2);
	j = ft_strlen(s1);
	i = ft_strlen(s2);
	while (x < j)
	{
		join[x] = s1[x];
		x++;
	}
	free(s1);
	len = 0;
	while (len < i)
		join[x++] = s2[len++];
	join[x] = ' ';
	join[x + 1] = '\0';
	return (join);
}

char	**get_stock2(char **av)
{
	char	**stock;
	int		i;
	char	*stock1;

	stock1 = NULL;
	i = 1;
	while (av[i])
		i++;
	i = 1;
	while (av[i])
	{
		if (!av[i][0])
			ft_error();
		stock1 = ft_strjoin(stock1, av[i]);
		i++;
	}
	stock = ft_split(stock1, ' ');
	free(stock1);
	return (stock);
}

int main(int ac, char **av)
{
	if (ac == 1|| ac >= 6)
	ft_error();
	t_threads	*s_threads;
	char	**stock;
	int		i;

	stock = get_stock2(av);
	s_threads = (t_threads *)malloc(sizeof(t_threads));
	s_threads->ac = 0;
	while (stock[s_threads->ac])
		s_threads->ac++;
	s_threads->array = malloc(sizeof(int) * s_threads->ac);
	i = 0;
	while (i < s_threads->ac)
	{
		s_threads->array[i] = ft_atoi(stock[i]);
		i++;
	}
	printf("%d\n", s_threads->array[1]);

}