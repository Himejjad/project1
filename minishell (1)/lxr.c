#include "minishell.h"

t_token *ft_new_token(char *str, int type)
{
    t_token *node;
    int i;
    node = NULL;
    if (!str)
        return (NULL);
    i = ft_strlen(str);
    node = (t_token *)malloc(sizeof(t_token));
    if (!node)
        return (NULL);
    node->value = malloc((i + 1) * sizeof(char));
    if (!node->value)
        return (NULL);
    i = -1;
    while (str[++i])
        node->value[i] = str[i];
    node->value[i] = '\0';
    node->type = type;
    node->next = NULL;
    return (node);
}

void	create_new_token(t_token **head, int len, char *input, t_token **current, e_type type)
{
	if (!*head) 
        {
            *head = ft_new_token(strndup(input, len), type);
            (*current) = (*head);
        }
        else
        {
            (*current)->next = ft_new_token(strndup(input, len), type);
            (*current) = (*current)->next;
        }
}

// void       handle_single_quote(t_token **head, t_var *var, char *input, t_token **current)
// {
//      if (var->i > var->start && input[var->i +1] == '$')
//     {
//         if (!*head) 
//         {
//             *head = ft_new_token(strndup(input + var->start, var->i - var->start), WORD);
//             (*current) = (*head);
//         } 
//         else if (var->i - var->start > 0)
//         {
//             (*current)->next = ft_new_token(strndup(input + var->start, var->i - var->start), WORD);
//             (*current) = (*current)->next;
//         }
//          var->start = var->i + 1;
//     }
 
//     var->i++;
//     while (input[var->i] && input[var->i] != '\'')
//         var->i++;
//     while (!ft_is_special(input[var->i]) && input[var->i] != '$')
//         var->i++;
//     if (!*head) 
//     {
//         *head = ft_new_token(strndup(input + var->start, var->i - var->start - 1), SQ_WORD);
//         (*current) = (*head);
//     } 
//     else if (var->i - var->start > 0)
//     {
//         (*current)->next = ft_new_token(strndup(input + var->start, var->i - var->start - 1), SQ_WORD);
//         (*current) = (*current)->next;
//     }
//     // if (input[var->i] == '$')
//         var->start = var->i;
//     // else
//     //     var->start = var->i + 1;

// }

// void    handle_double_quotes(t_token **head, t_var *var, char *input, t_token **current)
// {
//     if (var->i > var->start)
//     {
//         if (!*head) 
//         {
//             *head = ft_new_token(strndup(input + var->start, var->i - var->start), WORD);
//             (*current) = (*head);
//         } 
//         else if (var->i - var->start > 0)
//         {
//             (*current)->next = ft_new_token(strndup(input + var->start, var->i - var->start), WORD);
//             (*current) = (*current)->next;
//         }
//     }
//     var->start = var->i + 1;
//     var->i++;
//     while (input[var->i] && (input[var->i] != '"' || input[var->i - 1] == '\\'))
//         var->i++;
//     if (!*head) 
//     {
//         *head = ft_new_token(strndup(input + var->start, var->i - var->start), DQ_WORD);
//         (*current) = (*head);
//     } 
//     else if (var->i - var->start > 0)
//     {
//         (*current)->next = ft_new_token(strndup(input + var->start, var->i - var->start), DQ_WORD);
//         (*current) = (*current)->next;
//     }
//     var->start = var->i + 1;
// }

// void	handle_quotes(t_token **head, t_var *var, char *input, t_token **current)
// {
// 	if (input[var->i] == '\'')
// 		handle_single_quote(head, var, input, current);
// 	else
// 		handle_double_quotes(head, var, input, current);
// }

void    handle_delimiters(t_token **head, t_var *var, char *input, t_token **current)
{

    if (!*head)
    {
        *head = ft_new_token(strndup(input + var->start, var->i - var->start), WORD);
        (*current) = (*head);
    } 
    else if (var->i - var->start > 0)
    {
        (*current)->next = ft_new_token(strndup(input + var->start, var->i - var->start), WORD);
        (*current) = (*current)->next;
    }
    while (input[var->i + 1] && input[var->i] == ' ' && input[var->i + 1] == ' ')
        var->i++;
    var->start = var->i + 1;
}

void    handle_reds(t_token **head, t_var *var, char *input, t_token **current)
{
	if (input[var->i] == '<')
	{
    	if (input[var->i + 1] == '<')
    	{
			create_new_token(head, 2, input + var->i, current, HERDOC);
        	var->i++;
    	}
    	else
			create_new_token(head, 1, input+ var->i, current, REDIN);
	}
	else
	{
		if (input[var->i + 1] == '>')
    	{
			create_new_token(head, 2, input + var->i, current, REDAP);
        	var->i++;
    	}
    	else 
        {
			create_new_token(head, 1, input + var->i, current, REDOUT);
        }
	}
    var->start = var->i + 1;
}



void    handle_semi_pipe(t_token **head, t_var *var, char *input, t_token **current)
{
	if (input[var->i] == ';')
		create_new_token(head, 1, input + var->i, current, SEMI);
	else
		create_new_token(head, 1, input + var->i, current, PIPE);
    var->start = var->i + 1;
}

void    handle_last_word(t_token **head, t_var *var, char *input, t_token **current)
{

    if (var->i >= var->start) 
    {
		create_new_token(head, var->i - var->start + 1, input + var->start, current, WORD);
    }
}

void       handle_new_line(t_token **head, t_var *var, char *input, t_token **current)
{
	create_new_token(head, 1, input + var->i, current, N_LINE);
}

t_token *lexer(char *input)
{
    t_token	*head = NULL;
    t_token	*current = NULL;
    t_var	var;
    int sq =0;
    int dq =0 ;

    var.i = 0;
    while (ft_isspace(input[var.i]))
        var.i++;
	var.start = var.i;
    while (input[var.i]) 
    {
        if (input[var.i] == '\'' && !dq)
            sq = (sq + 1) % 2;
        else if (input[var.i] == '"' && (var.i == 0 || input[var.i - 1] != '\\') && !sq)
            dq = (dq + 1) % 2;
        else if (ft_is_special(input[var.i]) && !sq && !dq)
            handle_delimiters(&head, &var, input, &current);
        if ((input[var.i] == '<' || input[var.i] == '>') && !sq && !dq)
            handle_reds(&head, &var, input, &current);
        if ((input[var.i] == '|' || input[var.i] == ';') && !sq && !dq)
            handle_semi_pipe(&head, &var, input, &current);
        if (input[var.i + 1] == '\0' || input[var.i + 1] == '\n')
            handle_last_word(&head, &var, input, &current);
        var.i++;
        if (input[var.i] == '\0' || input[var.i] == '\n')
            handle_new_line(&head, &var, input, &current);
    }
    return (head);
}