/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:21:00 by mbondare          #+#    #+#             */
/*   Updated: 2025/11/03 16:29:12 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

static t_token_type	get_meta_type(char *input, int i, int *len)
{
	if (input[i] == '|')
		return (TOKEN_PIPE);
	if (input[i] == '<')
	{
		if (input[i + 1] == '<')
		{
			*len = 2;
			return (TOKEN_HEREDOC);
		}
		return (TOKEN_REDIR_IN);
	}
	if (input[i + 1] == '>')
	{
		*len = 2;
		return (TOKEN_REDIR_APPEND);
	}
	return (TOKEN_REDIR_OUT);
}

int	handle_metachar(char *input, int i, t_token **token_list)
{
	t_token_type	type;
	char			*val;
	int				len;

	len = 1;
	type = get_meta_type(input, i, &len);
	val = ft_substr(input, i, len);
	add_token_to_list(token_list, new_token(val, type));
	return (i + len);
}

int	handle_word(char *input, int i, t_token **token_list)
{
	int		start;
	char	*val;
	char	quote;

	start = i;
	quote = 0;
	while (input[i])
	{
		if (quote && input[i] == quote)
			quote = 0;
		else if (!quote && (input[i] == '\'' || input[i] == '"'))
			quote = input[i];
		else if (!quote && (is_whitespace(input[i]) || is_metachar(input[i])))
			break ;
		i++;
	}
	val = ft_substr(input, start, i - start);
	add_token_to_list(token_list, new_token(val, TOKEN_WORD));
	return (i);
}
