/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:22:56 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/30 19:47:44 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void execute_builtin(char *cmd, char **args, t_env_lst **env, bool is_child)
{
	int status;

	if (ft_strcmp("echo", cmd) == 0)
		status = builtin_echo(args);
	else if (ft_strcmp("env", cmd) == 0)
		status = builtin_env(*env);
	else if (ft_strcmp("exit", cmd) == 0)
		status = builtin_exit(args);
	else if (ft_strcmp("pwd", cmd) == 0)
		status = builtin_pwd();
	else if (ft_strcmp("cd", cmd) == 0)
		status = builtin_cd(args, env);
	else if (ft_strcmp("unset", cmd) == 0)
		status = builtin_unset(args, env);
	else if (ft_strcmp("export", cmd) == 0)
		status = builtin_export(args, env);
	if (is_child)
		exit(status);
	g_signal_received = status;
}

static int handle_exec_errors(char *cmd, int exec_errno)
{
	int exit_code;

	if (cmd && (exec_errno == EACCES || exec_errno == EISDIR))
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: %s\n", cmd, strerror(exec_errno));
		exit_code = 126;
	}
	else
	{
		ft_printf_fd(STDERR_FILENO, "minishell: command not found: %s\n", cmd);
		exit_code = 127;
	}
	return (exit_code);
}

static void child_process(t_cmd_node *node, int pipes[][2], int cmd_count,
						  t_env_lst **env, int idx)
{
	int exec_errno;
	int exit_code;
	char *full_cmd;
	char **envp;

	setup_child_signals();
	if (cmd_count > 1)
		setup_pipes(pipes, cmd_count - 1, idx);
	if (is_builtin(node->args[0]))
		return (execute_builtin(node->args[0], node->args, env, true));
	envp = env_lst_to_arr(*env);
	full_cmd = set_cmd(node->args[0], envp);
	if (full_cmd)
		execve(full_cmd, node->args, envp);
	exec_errno = errno;
	exit_code = handle_exec_errors(node->args[0], exec_errno);
	free(full_cmd);
	free_string_array(envp);
	exit(exit_code);
}

void execute_cmd(t_cmd_node *node, int pipes[][2], int cmd_count, t_env_lst **env, int idx)
{
	pid_t pid;

	expand_variables(node, *env);
	if (!node->args || !node->args[0])
		return;
	if (is_builtin(node->args[0]) && cmd_count == 1)
		return (execute_builtin(node->args[0], node->args, env, false));
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