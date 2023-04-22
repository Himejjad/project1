#include "minishell.h"


int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\r' || c == '\f')
		return (1);
	return (0);
}

int	ft_strisspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (!ft_isspace(str[i++]))
			return (0);
	return (1);
}

int	ft_readline(char **line)
{
	*line = readline("[minishell]~> ");
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
void check_leaks();

void	ft_signal_handler(int sig)
{
	if (sig == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
}

void	init_data(t_data *data)
{
	data->exit_status = 0;
	data->last_exit_status = 0;
}


int main(int ac, char **av, char **env)
{
	int status;
	char **s = NULL;

    char *line = NULL;
    init_data(&g_data);
    signal(SIGINT, handle_signals);
    signal(SIGQUIT, handle_signals);

    int *fds = malloc(sizeof(int) * 2);
    fds[0] = dup(0);
    fds[1] = dup(1);
    while (1)
    {
        while (ft_readline(&line) != 0)
        ;
        t_smpl_cmd *cmd;
        if (!check_nb_quotes(line))
        {
            t_token *head = lexer(line);
            if (!syntax_error(head))
            {
                t_ast    *ast = create_ast(&head);
                execute_piped_command(ast->pipe_line, env);
            }
        }
        dup2(fds[0], 0);
        dup2(fds[1], 1);
    }

}

// int main(int ac, char **av, char **env)
// {
// 	char *line = NULL;
// 	init_data(&g_data);
// 	signal(SIGINT, handle_signals);
// 	signal(SIGQUIT, handle_signals);

// 	// ft_readline(&line);
// 	while (1)
// 	{
// 		while (ft_readline(&line) != 0)
// 		;
//     	t_smpl_cmd *cmd;
// 		if (!check_nb_quotes(line))
// 		{
//     		t_token *head = lexer(line);
// 			if (!syntax_error(head))
// 			{
// 				t_ast	*ast = create_ast(&head);
// 				execute_piped_command(ast->pipe_line, env);
// 			}
// 		}
// 	}
	
	/////////
	// t_token *head = lexer(line);
    // t_token *current = head;
	// while(current)
	// {
	// 	printf("token value : '%s',   token type : '%d'\n", current->value, current->type);
	// 	current = current->next;
	// }

	//////////////////////////////////////////
	////////////////////////////////////////

	// cmd = create_smpl_cmd(head);
	// t_smpl_cmd *comd = cmd;
	
	// printf ("cmd : '%s'\n", comd->command);
    // while (comd->arg) {
    //     printf("args: '%s'\n", comd->arg->args);
    //     comd->arg = comd->arg->next;
    // }
	// while (comd->red) {
    //     printf("reds: '%s',    type: '%d'\n", comd->red->filename, comd->red->type);
    //     comd->red = comd->red->next;
	//}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

// 	t_pipe_line *pipe_line = create_pipe_line(&head);

// int i = 0;
// 		while (pipe_line->smpl_cmd)
// 		{
// 			printf ("cmd : '%s'\n", pipe_line->smpl_cmd->command);
// 			while (pipe_line->smpl_cmd->arg)
// 			{
// 				printf ("arg : '%s'\n", pipe_line->smpl_cmd->arg->args);
// 				pipe_line->smpl_cmd->arg = pipe_line->smpl_cmd->arg->next;
// 			}
// 			while (pipe_line->smpl_cmd->red)
// 			{
// 				printf ("red : '%s'\n", pipe_line->smpl_cmd->red->filename);
// 				pipe_line->smpl_cmd->red = pipe_line->smpl_cmd->red->next;
// 			}
// 			// printf("nb == %d\n", pipe_line->nb_smpl_cmds);
// 			pipe_line->smpl_cmd = pipe_line->smpl_cmd->next;
// 		}

// /////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////


	// while (ast->pipe_line)
	// {
	// 	printf("\n      -----  pipeline  -------\n");
	// 	while (ast->pipe_line->smpl_cmd)
	// 	{
	// 		printf ("\ncmd : '%s'     | ", ast->pipe_line->smpl_cmd->command);
	// 		while (ast->pipe_line->smpl_cmd->arg)
	// 		{
	// 			printf ("arg : '%s'     | ", ast->pipe_line->smpl_cmd->arg->args);
	// 			ast->pipe_line->smpl_cmd->arg = ast->pipe_line->smpl_cmd->arg -> next;
	// 		}
	// 		free(ast->pipe_line->smpl_cmd->arg);
	// 		while (ast->pipe_line->smpl_cmd->red)
	// 		{
	// 			printf ("red_filename : '%s'     |", ast->pipe_line->smpl_cmd->red->filename);
	// 			ast->pipe_line->smpl_cmd->red = ast->pipe_line->smpl_cmd->red->next;
	// 		}
	// 		free(ast->pipe_line->smpl_cmd->red);
	// 		free(ast->pipe_line->smpl_cmd);
	// 		ast->pipe_line->smpl_cmd = ast->pipe_line->smpl_cmd->next;
	// 	}
	// 	free(ast->pipe_line);
	// 	ast->pipe_line = ast->pipe_line->next;
	// }
	// free (ast);
	// check_leaks();

// }