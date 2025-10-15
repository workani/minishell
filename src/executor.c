/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:22:56 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/15 16:41:10 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void execute_cmd(char **args, int pipes[][2], int cmd_count, char **env, int idx)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		setup_pipes(pipes, cmd_count - 1, idx);
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
