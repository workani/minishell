/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:22:56 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/14 19:21:23 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_cmd(char **args, int (*pipes)[2], int cmd_count, int idx)
{
	printf("[cmd: %s | count: %d]\n", args[0], idx);
}

void execute(t_node *node, int (*pipes)[2], int cmd_count, int *idx)
{
	if (!node)
		return;
	if (node->type == NODE_PIPE)
	{
		execute(node->as.pipe.left, pipes, cmd_count, idx);
		execute(node->as.pipe.right, pipes, cmd_count, idx);
	}
	if (node->type == NODE_CMD)
	{
		(*idx)++;
		execute_cmd(node->as.cmd.args, pipes, cmd_count, *idx);	
	}
}