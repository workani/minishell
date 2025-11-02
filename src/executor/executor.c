/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: workani <workani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:22:56 by dklepenk          #+#    #+#             */
/*   Updated: 2025/11/03 14:52:54 by workani          ###   ########.fr       */
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
		status = builtin_exit(args, env);
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

static void child_process(t_cmd_node *node, int pipes[][2], int cmd_count,
						  t_env_lst **env, int idx)
{
	int exec_errno;
	char *full_cmd;
	char **envp;

	setup_child_signals();
	if (cmd_count > 1)
		setup_pipes(pipes, cmd_count - 1, idx);
	setup_redirections(node->redirections, *env);
	if (is_builtin(node->args[0]))
		return (execute_builtin(node->args[0], node->args, env, true));
	envp = env_lst_to_arr(*env);
	full_cmd = set_cmd(node->args[0], envp);
	if (full_cmd)
		execve(full_cmd, node->args, envp);
	exec_errno = errno;
	handle_exec_errors(node->args[0], exec_errno);
}

void execute_cmd(t_cmd_node *node, int pipes[][2], int cmd_count, t_env_lst **env, int idx)
{
	pid_t pid;
	int original_fds[3];

	expand_variables(node, *env);
	if (!node->args || !node->args[0])
		return (handle_redirs_with_no_cmd(node, *env));
		
	if (is_builtin(node->args[0]) && cmd_count == 1)
	{
		backup_fds(original_fds);
		setup_redirections(node->redirections, *env);
		execute_builtin(node->args[0], node->args, env, false);
		restore_fds(original_fds);
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