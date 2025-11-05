/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: workani <workani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:20:45 by mbondare          #+#    #+#             */
/*   Updated: 2025/11/05 16:17:34 by workani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_ast(t_node *node, int count)
{
	if (!node)
		return ;
	if (node->type == NODE_PIPE)
	{
		printf("pipe\n");
		print_ast(node->u_as.pipe.left, count + 1);
		print_ast(node->u_as.pipe.right, count + 1);
	}
	else
	{
		printf("[value: %s | count: %d]\n", node->u_as.cmd.args[0], count);
	}
}
