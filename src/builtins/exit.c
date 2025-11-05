/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:50:28 by mbondare          #+#    #+#             */
/*   Updated: 2025/11/05 17:42:00 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_number(char *str)
{
	int	i;

	if (!str || !str[0])
		return (false);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

static void	cleanup_and_exit(t_env_lst **env, int status)
{
	free_env_lst(env);
	exit(status);
}

static void	exit_with_numeric_error(char *arg, t_env_lst **env)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	cleanup_and_exit(env, 2);
}

int	builtin_exit(char **args, t_env_lst **env)
{
	long long	num;

	write(STDOUT_FILENO, "exit\n", 5);
	if (!args[1])
		cleanup_and_exit(env, g_signal_received);
	if (!is_number(args[1]))
		exit_with_numeric_error(args[1], env);
	if (args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (FAILURE);
	}
	num = ft_atoi(args[1]);
	cleanup_and_exit(env, (int)num);
	return (SUCCESS);
}
