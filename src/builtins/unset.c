/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:49:37 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/20 16:06:50 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env_node(t_env_lst **env, char *var)
{
	t_env_lst	*current;
	t_env_lst	*prev;
	int			var_len;

	prev = NULL;
	current = *env;
	var_len = ft_strlen(var);
	while (current)
	{
		if (ft_strncmp(current->value, var, var_len) == 0
			&& (current->value[var_len] == '=' 
			|| current->value[var_len] == '\0'))
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	builtin_unset(char **args, t_env_lst **env)
{
	int	i;

	if (!args[1])
		return (SUCCESS);
	i = 1;
	while (args[i])
	{
		remove_env_node(env, args[i]);
		i++;
	}
	return (SUCCESS);
}