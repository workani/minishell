/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:49:37 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/22 16:48:41 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_unset(t_env_lst  **env, char **args)
{
	int i;
	int exit_status;

	if (!args || !args[1])
	{
		return (SUCCESS);
	}	
	i = 1;
	exit_status = SUCCESS;
	while (args[i])
	{
		if (!is_valid_var_name(args[i]))
		{
			printf("minishell: unset: `%s': not a valid identifier\n", args[i]);
			exit_status = FAILURE;
			i++;
			continue;
		}
		delete_env_node(env, args[i]);
		i++;
	}
	return (exit_status);
}
