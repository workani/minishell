/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbondare <mbondare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:21:00 by mbondare          #+#    #+#             */
/*   Updated: 2025/10/01 14:56:35 by mbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'
		|| c == '\v');
}

int	handle_metachar(char *input, int i, t_token **token_list)
{
	t_token_type	type;
	char			*val;
	int				len;

	len = 1;
	if (input[i] == '|')
		type = TOKEN_PIPE;
	else if (input[i] == '<')
	{
		if (input[i + 1] == '<')
		{
			type = TOKEN_HEREDOC;
			len = 2;
		}
		else
			type = TOKEN_REDIR_IN;
	}
	else
	{
		if (input[i + 1] == '>')
		{
			type = TOKEN_REDIR_APPEND;
			len = 2;
		}
		else
			type = TOKEN_REDIR_OUT;
	}
	val = ft_substr(input, i, len);
	add_token_to_list(token_list, new_token(val, type));
	return (i + len);
}

// quoted strings
int	handle_quotes(char *input, int i, t_token **token_list)
{
	char	quote_char;
	int		start;
	char	*val;

	quote_char = input[i];
	start = i + 1;
	i++;
	while (input[i] && input[i] != quote_char)
		i++;
	if (input[i] != quote_char)
	{
		printf("minishell:error-unclosed quote\n");
		free_tokens(*token_list);
		*token_list = NULL;
		return (-1);
	}
	val = ft_substr(input, start, i - start);
	add_token_to_list(token_list, new_token(val, TOKEN_WORD));
	return (i + 1);
}

// words
int	handle_word(char *input, int i, t_token **token_list)
{
	int		start;
	char	*val;

	start = i;
	while (input[i] && !is_whitespace(input[i]) && !is_metachar(input[i])
		&& input[i] != '\'' && input[i] != '\"')
	{
		i++;
	}
	val = ft_substr(input, start, i - start);
	add_token_to_list(token_list, new_token(val, TOKEN_WORD));
	return (i);
}
