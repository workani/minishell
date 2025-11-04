/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: workani <workani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:21:43 by dklepenk          #+#    #+#             */
/*   Updated: 2025/11/05 00:57:05 by workani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error(char *var)
{
	ft_printf_fd(STDERR_FILENO,
		"minishell: export: `%s': not a valid identifier\n", var);
	return (FAILURE);
}

static void	print_env(t_env_lst *head)
{
	sort_env_list(head);
	while (head != NULL)
	{
		if (head->has_no_eq)
			printf("declare -x %s\n", head->key);
		else if (head->value)
			printf("declare -x %s=\"%s\"\n", head->key, head->value);
		else
			printf("declare -x %s=\"\"\n", head->key);
		head = head->next;
	}
}

static int	handle_var(t_env_lst **env, char *var)
{
	char	*key_value[2];
	char	*eq_pos;

	if (ft_strcmp(var, "=") == 0)
		return (print_error("="));
	eq_pos = ft_strchr(var, '=');
	if (!eq_pos)
	{
		if (!is_valid_var_name(var))
			return (print_error(var));
		add_or_update_env_var(env, var, NULL, true);
		return (SUCCESS);
	}
	if (!convert_var_to_key_value_pair(key_value, var))
		return (print_error(var));
	if (!is_valid_var_name(key_value[0]) || key_value[0][0] == '\0')
	{
		free(key_value[0]);
		free(key_value[1]);
		return (print_error(var));
	}
	add_or_update_env_var(env, key_value[0], key_value[1], false);
	free(key_value[0]);
	free(key_value[1]);
	return (SUCCESS);
}

int	builtin_export(char **args, t_env_lst **env)
{
	int	i;
	int	exit_status;

	if (!args || !args[1])
	{
		print_env(*env);
		return (SUCCESS);
	}
	i = 1;
	exit_status = SUCCESS;
	while (args[i])
	{
		if (handle_var(env, args[i]) == FAILURE)
			exit_status = FAILURE;
		i++;
	}
	return (exit_status);
}
