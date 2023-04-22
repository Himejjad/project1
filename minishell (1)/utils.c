#include "minishell.h"

int ft_isspace(char c)
{
    if (c == ' ' || c == '\t')
        return 1;
    return 0;
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

int check_nb_quotes(char   *input)
{
    int nb_sq;
    int nb_dq;
    int i;

    nb_dq = 0;
    nb_sq = 0;
    i = 0;
    while (input[i])
    {
        if (input[i] == '\'' && nb_dq == 0)
            nb_sq = (nb_sq + 1) % 2;
        else if (input[i] = '"' && input[i - 1] != '\\' && nb_sq == 0)
            nb_dq = (nb_dq + 1) % 2;
        i++;
    }
    if (nb_sq != 0 || nb_dq != 0)
        ft_error();
}