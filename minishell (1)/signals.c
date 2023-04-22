#include "minishell.h"

void	handle_signals(int signo)
{
	// if (g_pid)
	// 	return ;
	if (signo == SIGINT)
	{
		int status;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		WTERMSIG(status);
		g_data.exit_status = status;

	}
	else if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}
