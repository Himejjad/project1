/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 05:21:13 by himejjad          #+#    #+#             */
/*   Updated: 2023/05/12 05:32:09 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofer.h"

int	count_word(const char *s, char c)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (s[i])
	{
		if ((s[i] != c && s[i + 1] == c) || (s[i + 1] == '\0' && s[i] != c))
			x++;
		i++;
	}
	return (x);
}

int	count_caracters(const char *s, char c, int pos)
{
	int	i;

	i = 0;
	while (s[pos] != c && s[pos] != '\0')
	{
		pos++;
		i++;
	}
	return (i);
}


char	*ft_substr(char *s1, int start, int len)
{
	int		i;
	int		x;
	char	*new;

	i = 0;
	x = 0;
	if (!s1)
		return (NULL);
	if (start >= ft_strlen(s1))
		len = 0;
	while (i < len && s1[start + i])
		i++;
	new = malloc(i + 1);
	if (!new)
		return (0);
	while (x < i)
	{
		new[x] = s1[start + x];
		x++;
	}
	new[x] = '\0';
	return (new);
}

char	**ft_split(char *s, char c)
{
	char	**new;
	int		co;
	int		i;
	int		pos;
	int		x;

	if (!s)
		return (NULL);
	i = 0;
	pos = 0;
	x = count_word(s, c);
	new = malloc(sizeof(char *) * (x + 1));
	new[x] = NULL;
	while (i < x)
	{
		while (s[pos] == c)
			pos++;
		co = count_caracters(s, c, pos);
		new[i] = ft_substr(s, pos, co);
		pos += co;
		i++;
	}
	return (new);
}
