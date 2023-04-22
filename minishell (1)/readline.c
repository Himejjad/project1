#include "minishell.h"

int	ft_readline(char **line)
{
	*line = readline("[minishell][:)]~> ");
	if (!*line)
	{
		printf("exit\n");
		exit(1);
	}
	if (strcmp(*line, "") == 0 || ft_strisspace(*line))
		return (1);
	if (ft_strlen(*line) > 0)
		add_history(*line);
	return (0);
}