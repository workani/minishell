/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: workani <workani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:25:44 by dklepenk          #+#    #+#             */
/*   Updated: 2025/11/05 16:28:09 by workani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *cmd)
{
	int	i;

	i = 0;
	while (BUILTINS[i] != NULL)
	{
		if (ft_strcmp(cmd, BUILTINS[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

bool	is_valid_var_name(const char *var)
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