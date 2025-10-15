/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:22:56 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/15 17:58:29 by dklepenk         ###   ########.fr       */
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
	if (is_builtin(args[0]))
		return (execute_builtin(args[0], args, envp));
	if (fork() == 0)
	{
		setup_pipes(pipes, cmd_count - 1, idx);
		execv(get_cmd(args[0], envp), args);
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
