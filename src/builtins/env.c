/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbondare <mbondare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:50:14 by mbondare          #+#    #+#             */
/*   Updated: 2025/10/14 13:50:14 by mbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_env_lst *env)
{
	if (!env)
		return (SUCCESS);
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (SUCCESS);
}