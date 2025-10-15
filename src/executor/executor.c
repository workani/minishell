/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:22:56 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/15 18:32:36 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_builtin(char *cmd, char **args, char **envp)
{
	if (ft_strcmp(cmd, "echo") == 0)
		builtin_echo(args, envp);
	if (ft_strcmp(cmd, "envp") == 0)
		builtin_envp(envp);
	if (ft_strcmp(cmd, "exit") == 0)
		builtin_exit(args);
	if (ft_strcmp(cmd, "pwd") == 0)
		builtin_pwd();
}
void execute_cmd(char **args, int pipes[][2], int cmd_count, char **envp, int idx)
{
	if (is_builtin(args[0]) && cmd_count == 1)
		return (execute_builtin(args[0], args, envp));
	if (fork() == 0)
	{
		setup_pipes(pipes, cmd_count - 1, idx);
		if (is_builtin(args[0]))
		{
			execute_builtin(args[0], args, envp);
			exit(0);
		}
		else
			execve(get_cmd(args[0], envp), args, envp);
	}
}

void execute(t_node *node, int (*pipes)[2], int cmd_count, char **envp, int *idx)
{
	if (!node)
		return;
	if (node->type == NODE_PIPE)
	{
		execute(node->as.pipe.left, pipes, cmd_count, envp, idx);
		execute(node->as.pipe.right, pipes, cmd_count,envp, idx);
	}
	if (node->type == NODE_CMD)
	{
		execute_cmd(node->as.cmd.args, pipes, cmd_count, envp, *idx);
		(*idx)++;	
	}
}
