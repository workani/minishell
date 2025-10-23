/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbondare <mbondare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:22:56 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/21 12:21:51 by mbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_builtin(char *cmd, char **args, t_env_lst **env,
							bool is_in_pipe)
{
	int	status;

	status = 0;
	if (ft_strcmp(cmd, "echo") == 0)
		status = builtin_echo(args);
	else if (ft_strcmp(cmd, "env") == 0)
		status = builtin_env(*env); // Pass the single pointer
	else if (ft_strcmp(cmd, "exit") == 0)
		status = builtin_exit(args);
	else if (ft_strcmp(cmd, "pwd") == 0)
		status = builtin_pwd();
	else if (ft_strcmp(cmd, "cd") == 0)
		status = builtin_cd(args, env);
	else if (ft_strcmp(cmd, "unset") == 0)
		status = builtin_unset(args, env);
	else if (ft_strcmp(cmd, "export") == 0)
		status = builtin_export(args, env);
	if (is_in_pipe)
		exit(status);
	g_signal_received = status;
}

static void	child_process(t_cmd_node *node, int pipes[][2], 
						int cmd_count, t_env_lst **env, int idx)
{
	char	**envp;
	char	*cmd_path;

	setup_child_signals();
	if (cmd_count > 1)
		setup_pipes(pipes, cmd_count - 1, idx);
	setup_redirections(node->redirections);
	if (is_builtin(node->args[0]))
	{
		execute_builtin(node->args[0], node->args, env, true);
	}
	else
	{
		envp = env_lst_to_arr(*env);
		cmd_path = get_cmd(node->args[0], envp);
		if (cmd_path)
			execve(cmd_path, node->args, envp);
		else
			execve(node->args[0], node->args, envp);
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd(node->args[0], 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
}

void	execute_cmd(t_cmd_node *node, int pipes[][2], int cmd_count,
				t_env_lst **env, int idx)
{
	pid_t	pid;

	if (!node->args || !node->args[0])
		return;
	
	expand_variables(node, *env);

	if (is_builtin(node->args[0]) && cmd_count == 1 && node->redirections == NULL)
	{
		execute_builtin(node->args[0], node->args, env, false);
		return;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		g_signal_received = 1;
		return;
	}
	if (pid == 0)
		child_process(node, pipes, cmd_count, env, idx);
}

void	execute(t_node *node, int pipes[][2], int cmd_count,
			t_env_lst **env, int *idx)
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