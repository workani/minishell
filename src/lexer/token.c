/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:12:30 by mbondare          #+#    #+#             */
/*   Updated: 2025/11/03 16:29:39 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// create new token
t_token	*new_token(char *value, t_token_type type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	return (token);
}

// add t to end of list
void	add_token_to_list(t_token **list_head, t_token *new)
{
	t_token	*current;

	if (!list_head || !new)
		return ;
	if (!*list_head)
	{
		*list_head = new;
		return ;
	}
	current = *list_head;
	while (current->next)
		current = current->next;
	current->next = new;
}

// free token list
void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}

// print tokens for debugging
void	print_tokens(t_token *tokens)
{
	printf("TOKENS\n");
	while (tokens)
	{
		printf("type: %d, Value: [%s]\n", tokens->type, tokens->value);
		tokens = tokens->next;
	}
	printf("---\n");
}
