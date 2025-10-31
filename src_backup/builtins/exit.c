/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: workani <workani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:50:28 by mbondare          #+#    #+#             */
/*   Updated: 2025/10/29 23:12:39 by workani          ###   ########.fr       */
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

int	builtin_exit(char **args)
{
	int exit_code;
	long long num;

	printf("exit\n");
	if (!args[1])
		exit(g_signal_received);
	if (!is_number(args[1]))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	if (args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (FAILURE);
	}
	num = ft_atoi(args[1]);
	exit_code = (unsigned char)num;
	exit(exit_code);
	return (SUCCESS);
}