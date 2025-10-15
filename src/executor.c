/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:22:56 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/15 14:00:52 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_cmd(char **args, int (*pipes)[2], int cmd_count, char **env, int idx)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (idx == 0)
		{
			dup2(pipes[0][1], STDOUT_FILENO);
			close_unused_pipes(pipes, cmd_count - 1, pipes[0][1], DISCARD);
		}
		else if (idx == cmd_count - 1)
		{
			dup2(pipes[idx - 1][0], STDIN_FILENO);
			close_unused_pipes(pipes, cmd_count - 1, pipes[idx - 1][0], DISCARD);
		}
		else
		{
			dup2(pipes[idx - 1][0], STDIN_FILENO);
			dup2(pipes[idx][1], STDOUT_FILENO);
			close_unused_pipes(pipes, cmd_count - 1, pipes[idx - 1][0], pipes[idx][1]);
		}
		execv(get_cmd(args[0], env), args);
	}
}

void execute(t_node *node, int (*pipes)[2], int cmd_count, char **env, int *idx)
{
	if (!node)
		return;
	if (node->type == NODE_PIPE)
	{
		execute(node->as.pipe.left, pipes, cmd_count, env, idx);
		execute(node->as.pipe.right, pipes, cmd_count,env, idx);
	}
	if (node->type == NODE_CMD)
	{
		execute_cmd(node->as.cmd.args, pipes, cmd_count, env, *idx);
		(*idx)++;	
	}
}
