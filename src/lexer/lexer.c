/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbondare <mbondare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:35:03 by mbondare          #+#    #+#             */
/*   Updated: 2025/10/01 14:47:24 by mbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *tokenize(char *input)
{
    t_token *token_list;
    int i; 
    int new_i; 
    
    token_list = NULL; 
    i = 0; 
    while(input[i])
    {
        if (input[i] == ' ' || input[i] == '\t')
        {
            i++;
            continue ; 
        }
        else if (input[i] == '|' | input[i] == '<' || input[i] == '>')
            new_i = handle_metachar(input, i, &token_list);
        else if (input[i] == '\'' || input[i] == '\"')
            new_i = handle_quotes(input, i, &token_list);
        else
            new_i = handle_word(input, i, &token_list);
        if (new_i == -1)
            return (NULL); 
        i = new_i;
    }
    return (token_list);
}