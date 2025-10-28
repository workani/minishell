/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:21:00 by mbondare          #+#    #+#             */
/*   Updated: 2025/10/28 16:40:49 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_metachar(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

static int is_whitespace(char c)
{
    return (c == ' ' || c == '\t'); 
}

int handle_metachar(char *input, int i, t_token **token_list)
{
    t_token_type type; 
    char *val; 
    int len;

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


int handle_word(char *input, int i, t_token **token_list)
{
    int start;
    char *val; 

    start = i;
    while (input[i] && !is_whitespace(input[i]) && !is_metachar(input[i]))
    {
        i++;
    }
    val = ft_substr(input, start, i - start);
    add_token_to_list(token_list, new_token(val, TOKEN_WORD));
    return (i);
}