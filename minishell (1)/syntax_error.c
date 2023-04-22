#include "minishell.h"


int	ft_perror(char *msg, char *utils, char *s)
{
    write(STDERR_FILENO, "minishell: ", 12);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	if (utils)
		write(STDERR_FILENO, utils, ft_strlen(utils));
	if (s)
		write(STDERR_FILENO, s, ft_strlen(s));
	write(STDERR_FILENO, ".\n", 2);
	return (EXIT_FAILURE);
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
        else if (input[i] == '"' && (i == 0 || input[i - 1] != '\\') && nb_sq == 0)
            nb_dq = (nb_dq + 1) % 2;
        i++;
    }
    if (nb_sq != 0 || nb_dq != 0)
        return (ft_perror("error : unclosed quotes", NULL, NULL));
    return (0);
}

int syntax_error(t_token *token)
{
    t_token *tmp;
    
    if (token->type == PIPE || token->type == SEMI)
        return (ft_perror("parse error near '", tmp->value, "'"));
    tmp = token;
    while (tmp->next != NULL)
    {
        if (tmp->type == REDIN || tmp->type == REDOUT || tmp->type == REDAP || tmp->type == HERDOC)
        {
            if (tmp->next->type != WORD)
                return (ft_perror(" parse error near '", tmp->value, "'"));
        }
        else if (tmp->type == PIPE || tmp->type == SEMI)
        {
            if (tmp->next->type == SEMI || tmp->next->type == PIPE)
                return (ft_perror("parse error near '", tmp->value, "'"));
        }
        else if (tmp->next->type == N_LINE && strchr("><\\|&", tmp->value[ft_strlen(tmp->value) - 1]))
        {
            return (ft_perror("parse error near N_LINE", NULL, NULL));
        }
        tmp = tmp->next;
    }
    return (0);
}

