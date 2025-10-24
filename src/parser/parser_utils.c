/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:20:45 by mbondare          #+#    #+#             */
/*   Updated: 2025/10/21 16:43:58 by dklepenk         ###   ########.fr       */
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
		print_ast(node->as.pipe.left, count + 1);
		print_ast(node->as.pipe.right, count + 1);
	}
	else
	{
		printf("[value: %s | count: %d]\n", node->as.cmd.args[0], count);
	}
}