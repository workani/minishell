/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:36:50 by mbondare          #+#    #+#             */
/*   Updated: 2025/10/28 16:43:55 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node	*parse_command(t_token **tokens);
static bool		parse_redirection(t_token **tokens, t_cmd_node *cmd_node);
static char		**add_arg_to_array(char **args, char *new_arg);

t_node	*parse(t_token *tokens)
{
	t_node	*left;
	t_node	*right;
	t_token	*current_token;

	if (!tokens)
		return (NULL);
	current_token = tokens;
	left = parse_command(&current_token);
	if (!left)
		return (NULL);
	while (current_token && current_token->type == TOKEN_PIPE)
	{
		current_token = current_token->next;
		if (!current_token)
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			free_ast(left);
			return (NULL);
		}
		right = parse(current_token);
		if (!right)
		{
			free_ast(left);
			return (NULL);
		}
		left = new_pipe_node(left, right);
		break ;
	}
	return (left);
}

static t_node	*parse_command(t_token **tokens)
{
	t_node		*node;
	t_cmd_node	*cmd_node;

	node = new_cmd_node();
	cmd_node = &node->as.cmd;
	while (*tokens && (*tokens)->type != TOKEN_PIPE)
	{
		if ((*tokens)->type == TOKEN_WORD)
		{
			cmd_node->args = add_arg_to_array(cmd_node->args,
					ft_strdup((*tokens)->value));
		}
		else if ((*tokens)->type >= TOKEN_REDIR_IN
			&& (*tokens)->type <= TOKEN_HEREDOC)
		{
			if (!parse_redirection(tokens, cmd_node))
			{
				free_ast(node);
				return (NULL);
			}
		}
		*tokens = (*tokens)->next;
	}
	return (node);
}

static bool	parse_redirection(t_token **tokens, t_cmd_node *cmd_node)
{
	t_redir	*redir;
	t_redir	*current;

	if (!(*tokens)->next || (*tokens)->next->type != TOKEN_WORD)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (false);
	}
	redir = malloc(sizeof(t_redir));
	redir->type = (*tokens)->type;
	redir->filename = ft_strdup((*tokens)->next->value);
	redir->next = NULL;
	if (!cmd_node->redirections)
		cmd_node->redirections = redir;
	else
	{
		current = cmd_node->redirections;
		while (current->next)
			current = current->next;
		current->next = redir;
	}
	*tokens = (*tokens)->next;
	return (true);
}

static char	**add_arg_to_array(char **args, char *new_arg)
{
	int size;
	char **new_args;

	size = 0;
	if (args)
	{
		while (args[size])
			size++;
	}
	new_args = malloc(sizeof(char *) * (size + 2));
	if (!new_args)
		return (NULL);
	size = 0;
	if (args)
	{
		while (args[size])
		{
			new_args[size] = args[size];
			size++;
		}
	}
	new_args[size] = new_arg;
	new_args[size + 1] = NULL;
	free(args);
	return (new_args);
}