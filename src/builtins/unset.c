/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:49:37 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/21 19:10:03 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool is_valid_var_name(const char *var)
{
	int i;
	
	if (!var || (!ft_isalpha(var[0]) && var[0] != '_'))
		return (false);
	i = 1;
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static void delete_var_from_env(t_env_lst **head, const char *key)
{
	t_env_lst *node;

	node = *head;
	while (node != NULL)
	{
		if (node->key && ft_strcmp(key, node->key))
		{
			delete_env_node(head, node);
			return;
		}
		node = node->next;
	}
}

int builtin_unset(t_env_lst  **env, char **args)
{
	int i;
	int exit_status;

	if (!args)
		return (SUCCESS);
	i = 0;
	exit_status = SUCCESS;
	while (args[i])
	{
		if (!is_valid_var_name(args[i]))
		{
			printf("minishell: unset: `%s': not a valid identifier\n", args[i]);
			exit_status = FAILURE;
		}
		delete_var_from_env(env, args[i]);
		i++;
	}
	return (exit_status);
}
