#include "minishell.h"

t_red    *create_red_node(t_red *red, t_token **token)
{
    red = (t_red *)malloc(sizeof(t_red));
    if (!red)
        return (NULL);
    red->next = NULL;
    red->type = (*token)->type;
    (*token) = (*token)->next;
    red->filename = strdup((*token)->value);
    return (red);
}

void    ft_add_red(t_smpl_cmd *cmd, t_token **token)
{
    t_red   *tmp;

    if (cmd->red ==  NULL)
        cmd->red = create_red_node(cmd->red, token);
    else
    {
        tmp = cmd->red;
        while (tmp->next)
            tmp = tmp->next;
        tmp ->next = create_red_node(tmp, token);
    }
}

t_arg	*create_arg_node(t_token **token)
{
	t_arg	*arg;

	arg = (t_arg *)malloc(sizeof(t_arg));
	arg->args = strdup((*token)->value);
	arg->next = NULL;
	return (arg);
}

void    add_args(t_smpl_cmd *smpl_cmd, t_token **token)
{
    t_arg   *tmp;

    if (smpl_cmd->arg == NULL)
        smpl_cmd->arg = create_arg_node(token);
	else
	{
		tmp = smpl_cmd->arg;
	    while (tmp->next != NULL)
		    tmp = tmp->next;
        tmp->next = create_arg_node(token);
	}
}

t_smpl_cmd	*ft_init_simple_cmd(void)
{
	t_smpl_cmd	*cmd;

	cmd = (t_smpl_cmd *)malloc(sizeof(t_smpl_cmd));
	if (!cmd)
		return (NULL);
    cmd->nb_args = 0;
    cmd->nb_reds = 0;
	cmd->arg = NULL;
	cmd->command = NULL;
	cmd->next = NULL;
	cmd->red= NULL;
	return (cmd);
}

void parse_word(t_token **token, t_smpl_cmd *smpl_cmd, t_arg *tmp)
{
	if (smpl_cmd->command == NULL)
	    smpl_cmd->command = strdup((*token)->value);
    else
	{
		if (smpl_cmd->arg == NULL)
			smpl_cmd->arg = create_arg_node(token);
		else
		{
			tmp = create_arg_node(token);
			add_args(smpl_cmd, token);
		}
        smpl_cmd->nb_args++;
	}
    (*token) = (*token)->next;
}

t_smpl_cmd  *create_smpl_cmd(t_token **token)
{
	t_smpl_cmd  *smpl_cmd;
    t_arg   *tmp;
    smpl_cmd = ft_init_simple_cmd();
    while ((*token)->type != N_LINE && (*token)->type != SEMI && (*token)->type != PIPE)
    {
        if ((*token)->type == REDIN || (*token)->type == REDOUT || (*token)->type == REDAP || (*token)->type == HERDOC)
        {
            ft_add_red(smpl_cmd, token);
            smpl_cmd->nb_reds++;
			free(*token);
            (*token) = (*token)->next;
        }
        else if ((*token)->type == WORD)
            parse_word(token, smpl_cmd, tmp);
        else
            (*token) = (*token)->next;
    }
    return (smpl_cmd);
}

t_pipe_line	*init_pipe_line(t_pipe_line *pipeline)
{
	pipeline = (t_pipe_line *)malloc(sizeof(t_pipe_line));
	pipeline->nb_smpl_cmds = 0;
	pipeline->next = NULL;
	pipeline->smpl_cmd = NULL;
	return (pipeline);
}

t_pipe_line	*create_pipe_line(t_token **token)
{
	t_pipe_line	*pipeline;
	t_smpl_cmd	*tmp;

	pipeline = init_pipe_line(pipeline);
	while ((*token)->type != N_LINE && (*token)->type != SEMI)
	{
		if (pipeline->smpl_cmd == NULL)
		{
			pipeline->smpl_cmd = create_smpl_cmd(token);
			pipeline->nb_smpl_cmds++;
		}
		else
		{
			(*token) = (*token)->next;
			tmp = pipeline->smpl_cmd;
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = create_smpl_cmd(token);
			pipeline->nb_smpl_cmds++;
		}
	}
	return (pipeline);
}

t_ast	*init_ast(t_ast *ast)
{
	ast = (t_ast *)malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->nb_pipe_lines = 0;
	ast->pipe_line = NULL;
	return (ast);
}

t_ast	*create_ast(t_token **token)
{
	syntax_error(*token);
	*token = ft_expand(token);
	t_ast	*ast;
	t_pipe_line	*tmp;

	ast = init_ast(ast);
	while ((*token)->type != N_LINE)
	{
		if (ast->pipe_line == NULL)
		{
			ast->pipe_line = create_pipe_line(token);
			ast->nb_pipe_lines++;	
		}
		else
		{
			(*token) = (*token)->next;
			tmp = ast->pipe_line;
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = create_pipe_line(token);
			ast->nb_pipe_lines++;
		}
	}
	return (ast);
}
