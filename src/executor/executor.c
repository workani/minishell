/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:22:56 by dklepenk          #+#    #+#             */
/*   Updated: 2025/11/04 19:17:16 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void execute_builtin(char **args, t_env_lst **env, bool is_child)
{
	char *cmd;
	int status;

	cmd = args[0];
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

static void	child_process(t_cmd_node *node, t_executor_ctx *ctx)
{
	int		exec_errno;
	char	*full_cmd;
	char	**envp;

	setup_child_signals();
	if (ctx->cmd_count > 1)
		setup_pipes(ctx->pipes, ctx->cmd_count - 1, ctx->idx);
	setup_redirections(node->redirections, *ctx->env);
	if (is_builtin(node->args[0]))
		return (execute_builtin(node->args, ctx->env, true));
	envp = env_lst_to_arr(*ctx->env);
	full_cmd = set_cmd(node->args[0], envp);
	if (full_cmd)
		execve(full_cmd, node->args, envp);
	exec_errno = errno;
	handle_exec_errors(node->args[0], exec_errno);
}

void	execute_cmd(t_cmd_node *node, t_executor_ctx *ctx)
{
	pid_t	pid;
	int		original_fds[3];

	expand_variables(node, *ctx->env);
	if (!node->args || !node->args[0])
		return (handle_redirs_with_no_cmd(node, *ctx->env));
	if (is_builtin(node->args[0]) && ctx->cmd_count == 1)
	{
		backup_fds(original_fds);
		setup_redirections(node->redirections, *ctx->env);
		execute_builtin(node->args, ctx->env, false);
		restore_fds(original_fds);
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
		child_process(node, ctx);
}

void	execute(t_node *node, t_executor_ctx *ctx)
{
	if (!node)
		return ;
	if (node->type == NODE_PIPE)
	{
		execute(node->as.pipe.left, ctx);
		execute(node->as.pipe.right, ctx);
	}
	else if (node->type == NODE_CMD)
	{
		execute_cmd(&node->as.cmd, ctx);
		ctx->idx++;
	}
}