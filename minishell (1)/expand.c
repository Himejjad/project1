#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char	*ft_strjoin(char *str1, char *str2)
{
	int i = 0;
	int j = 0;
	char *str3;
	str3 = malloc((ft_strlen(str1) + ft_strlen(str2) + 1));
	while (str1[i])
	{
		str3[i] = str1[i];
		i++;
	}
	while (str2[j])
	{
		str3[i] = str2[j];
		j++;
		i++;
	}
	str3[i] = '\0';
	return (str3);
}

int		len(long nb)
{
	int		len;

	len = 0;
	if (nb < 0)
	{
		nb = nb * -1;
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nb)
{
	char *str;
	long	n;
	int		i;

	n = nb;
	i = len(n);
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i--] = '\0';
	if (n == 0)
	{
		str[0] = 48;
		return (str);
	}
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		str[i] = 48 + (n % 10);
		n = n / 10;
		i--;
	}
	return (str);
}

char	*exp_var_env(char	*dollar)
{
	int j = 0;
	char	*var_name;
	char	*var_value;
	char	*expanded = "";
	if (dollar[j++] == '?')
		expanded = ft_itoa(WEXITSTATUS(g_data.exit_status));
	else
	{
		while (dollar[j] && (dollar[j] == '_' || ft_is_digit(dollar[j]) || ft_isalpha(dollar[j])))
			j++;
		var_name = strndup(dollar, j);
		var_value = getenv(var_name);
		if (var_value)
			expanded = strdup(var_value);
	}
	expanded = ft_strjoin(expanded, dollar + j);
	return (expanded);
}

int ft_chrch(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char *exp_word(char *str)
{
	int sq;
	int dq;
	int	i;
	char *s1 = NULL;
	char *s2 = NULL;

	sq = 0;
	dq = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' && !dq)
			sq = (sq + 1) % 2;
		else if (str[i] == '"' && !sq && (i == 0 || str[i - 1] != '\\'))
			dq = (dq + 1) % 2;
		if (str[i] == '$' && !sq && (i == 0 || str[i - 1] != '\\'))
		{
			s1 = strndup(str, i);
			if (strcmp(str + i, "$") == 0)
				s2 = strdup(str + i);
			else
				s2 = exp_var_env(str + i + 1);
			str = ft_strjoin(s1, s2);
			return(str);
		}
	}
	return(str);
}

char *expand_dollar(char *str)
{
	int u = 0;
	int i = 0;
	while (strchr(str, '$') && ++u < 11)
		str = exp_word(str);
	return(str);
}

char *expand_quotes(char *str)
{
	int i = 0;
	int j = 0;
	char *s1 ="";
	char *s2 = "";
	char *s = "";
	while (str[i])
	{
		if (str[i] == '\'')
		{
			s1 = strndup(str + j, i - j);
			j = i + 1;
			while (str[j] && str[j] != '\'')
				j++;
			s2 = ft_strjoin(s1, strndup(str + i + 1, j - i - 1));
			s = ft_strjoin(s, s2);
			i = j;
			j++;
		}
		else if (str[i] == '"')
		{
			s1 = strndup(str + j, i - j);
			j = i + 1;
			while (str[j] && (str[j] != '"' || str[j - 1] == '\\'))
				j++;
			s2 = ft_strjoin(s1, strndup(str + i + 1, j - i - 1));
			s = ft_strjoin(s, s2);
			i = j;
			j++;
		}
		else if (str[i] != '\'' && str[i] != '"' && str[i + 1] == '\0')
		{
			s2 = strndup(str + j, i - j +1);
			s = ft_strjoin(s, s2);
		}
		i++;
	}
	return(s);
}

t_token	*ft_expand(t_token **token)
{
	t_token	*tmp;
	char *s;
	int i = 0;
	int u = 0;
	int exp;

	tmp = *token;
	while (tmp)
	{
		//to add : expand cons bksh
		if (exp)
			tmp->value = expand_dollar(tmp->value);
		if (strchr(tmp->value, '\'') || strchr(tmp->value, '"'))
		tmp->value = expand_quotes(tmp->value);
		//to add : expand bksh
		if (tmp->type == HERDOC)
			exp = 0;
		else 
			exp = 1;
		tmp = tmp->next;
	}
	return(*token);
}


