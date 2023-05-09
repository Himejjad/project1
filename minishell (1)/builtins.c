/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handle_echo_option.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 20:35:10 by himejjad           #+#    #+#             */
/*   Updated: 2023/05/09 01:27:02 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


typedef struct s_lexer
{
	char			c;
	unsigned int	index;
	int				id_cmd;
	int				id_option;
	char			*contents;
}	t_lexer;


int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90))
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isdigit(c) || ft_isalpha(c))
		return (1);
	return (0);
}


static int	ft_check_for_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && !((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

static int	boolen_n1(t_lexer *lexer)
{
	if (
		lexer->contents[lexer->index + 2] && \
		((lexer->contents[lexer->index + 2] >= 9 && \
		lexer->contents[lexer->index + 2] <= 13) || \
		lexer->contents[lexer->index + 2] == ' '))
		return (1);
	return (0);
}

static int	boolen_n2(t_lexer *lexer)
{
	if (
		lexer->contents[lexer->index + 2] && \
		ft_isalnum(lexer->contents[lexer->index + 2]) && \
		(ft_check_for_char(&lexer->contents[lexer->index + 2], 'n') == 1))
		return (1);
	return (0);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->index < ft_strlen(lexer->contents))
	{
		lexer->index += 1;
		lexer->c = lexer->contents[lexer->index];
	}
}


t_token	*lexer_collect_echo(t_lexer *lexer)
{
	while (lexer->c != '\0' && \
	(ft_check_for_char(&lexer->contents[lexer->index + 2], 'n') == 1))
	{
		lexer_skep_whitespace(lexer);
		if (lexer->c == '-' && lexer->contents[lexer->index + 1] == 'n')
		{
			if (boolen_n1(lexer))
			{
				lexer_advance(lexer);
				lexer_advance(lexer);
				lexer_advance(lexer);
			}
			else if (boolen_n2(lexer))
			{
				lexer_advance(lexer);
				while (lexer->c && lexer->c == 'n')
					lexer_advance(lexer);
			}
		}
		else
			break ;
	}
	lexer->id_option = 1;
	return (init_token(TOKEN_OPTION, lexer->contents));
}
