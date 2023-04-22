#include "minishell.h"

int ft_is_digit(char c)
{
    if (c >='0' && c <='9')
        return(1);
    return (0);
}

int     ft_isalpha(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (1);
    return (0);
}

int ft_is_special(char c)
{
    char a = c;
    if (strchr(" ><|;", c))
        return (1);
    return (0);
}

int ft_is_redirection(t_token *token)
{
    if (token->value[0] != '<' && token->value[0] != '>')
        return (0);
    return (1);
}
int	in_charset(char c)
{
    if (strchr("\'\"><|;$\n\0= ", c))
	    return (1);
    return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}