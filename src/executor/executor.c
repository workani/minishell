/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:22:56 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/28 19:02:35 by dklepenk         ###   ########.fr       */
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
		status = builtin_env(*env);
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

static int	has_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static void	child_process(t_cmd_node *node, int pipes[][2], int cmd_count,
		t_env_lst **env, int idx)
{	
	char	**envp;
	char	*cmd_path;
	int		exec_errno;

	setup_child_signals();
	if (cmd_count > 1)
		setup_pipes(pipes, cmd_count - 1, idx);
	setup_redirections(node->redirections, *env);
	if (is_builtin(node->args[0]))
		return (execute_builtin(node->args[0], node->args, env, true));
	envp = env_lst_to_arr(*env);
	if (has_slash(node->args[0]))
		cmd_path = ft_strdup(node->args[0]);
	else
		cmd_path = get_cmd(node->args[0], envp);
	if (cmd_path)
		execve(cmd_path, node->args, envp);
	exec_errno = errno;
	if (has_slash(node->args[0]) && 
		(exec_errno == EACCES || exec_errno == EISDIR))
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: %s\n", 
			node->args[0], strerror(exec_errno));
		exit(126);
	}
	ft_printf_fd(STDERR_FILENO, "minishell: command not found: %s\n", 
		node->args[0]);
	exit(127);	
}

void	execute_cmd(t_cmd_node *node, int pipes[][2], int cmd_count,
		t_env_lst **env, int idx)
{
	pid_t	pid;

	expand_variables(node, *env);
	if (!node->args || !node->args[0])
	{
		if (node->redirections)
		{
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				g_signal_received = 1;
				return;
			}
			if (pid == 0)
			{
				setup_child_signals();
				setup_redirections(node->redirections, *env);
				exit(0);
			}
		}
		return;
	}
	if (is_builtin(node->args[0]) && cmd_count == 1
		&& node->redirections == NULL)
	{
		execute_builtin(node->args[0], node->args, env, false);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		g_signal_received = 1;
		return ;
	}
	if (pid == 0)
		child_process(node, pipes, cmd_count, env, idx);
}

void	execute(t_node *node, int pipes[][2], int cmd_count, t_env_lst **env,
		int *idx)
{
	if (!node)
		return ;
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