/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:22:56 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/22 16:25:20 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void execute_builtin(char *cmd, char **args, t_env_lst **env, bool is_in_pipe)
{
	if (ft_strcmp(cmd, "echo") == 0)
		builtin_echo(args);
	if (ft_strcmp(cmd, "env") == 0)
		builtin_env(env);
	if (ft_strcmp(cmd, "exit") == 0)
		builtin_exit(args);
	if (ft_strcmp(cmd, "pwd") == 0)
		builtin_pwd();
	if (ft_strcmp(cmd, "unset") == 0)
		builtin_unset(env, args);
	if (ft_strcmp(cmd, "export") == 0)
		builtin_export(env, args);	
	if (is_in_pipe)
		exit(SUCCESS);
}
void execute_cmd(t_cmd_node *node, int pipes[][2], int cmd_count, t_env_lst **env, int idx)
{
	char **envp;
	
	if (is_builtin(node->args[0]) && cmd_count == 1)
		return (execute_builtin(node->args[0], node->args, env, false));
	if (fork() == 0)
	{
		setup_pipes(pipes, cmd_count - 1, idx);
		setup_redirections(node->redirections);
		if (is_builtin(node->args[0]))
		{
			execute_builtin(node->args[0], node->args, env, true);	
		}
		else
		{
			envp = env_lst_to_arr(*env);
			execve(get_cmd(node->args[0], envp), node->args, envp);	
		}
	}
}

void execute(t_node *node, int pipes[][2], int cmd_count, t_env_lst **env, int *idx)
{
	if (!node)
		return;
	if (node->type == NODE_PIPE)
	{
		execute(node->as.pipe.left, pipes, cmd_count, env, idx);
		execute(node->as.pipe.right, pipes, cmd_count, env, idx);
	}
	if (node->type == NODE_CMD)
	{
		execute_cmd(&node->as.cmd, pipes, cmd_count, env, *idx);
		(*idx)++;	
	}
}
