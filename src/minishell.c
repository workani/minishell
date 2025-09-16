/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:15:39 by dklepenk          #+#    #+#             */
/*   Updated: 2025/09/16 13:47:04 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_routine(char **args, char **env)
{
	execve(args[0], args, env);
}

void	parent_routine(void)
{
	wait(NULL);
}
char	**init_shell(int argc, char **argv, char **env)
{
	char	**args;
	char	*cmd;

	args = malloc(3 * sizeof(char *));
	cmd = get_cmd(argv[1], env);
	if (argc == 2)
	{
		args[0] = cmd;
		args[1] = NULL;
	}
	else if (argc == 3)
	{
		args[0] = cmd;
		args[1] = argv[2];
		args[2] = NULL;
	}
	return (args);
}

int	main(int argc, char **argv, char **env)
{
	pid_t	pid;
	char	**args;

	args = init_shell(argc, argv, env);
	pid = fork();
	if (pid != 0)
		parent_routine();
	else
		child_routine(args, env);
}
