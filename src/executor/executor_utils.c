/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: workani <workani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:33:40 by mbondare          #+#    #+#             */
/*   Updated: 2025/11/05 00:21:59 by workani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void backup_fds(int dest[3])
{
	dest[0] = dup(STDIN_FILENO);
	dest[1] = dup(STDOUT_FILENO);
	dest[2] = dup(STDERR_FILENO);
}

void restore_fds(int src[3])
{
	dup2(src[0], STDIN_FILENO);
	dup2(src[1], STDOUT_FILENO);
	dup2(src[2], STDERR_FILENO);
	close(src[0]);
	close(src[1]);
	close(src[2]);
}

void	close_unused_pipes(int pipes[][2], int len, int exception_one,
		int exception_two)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (pipes[i][0] != exception_one && pipes[i][0] != exception_two)
			close(pipes[i][0]);
		if (pipes[i][1] != exception_one && pipes[i][1] != exception_two)
			close(pipes[i][1]);
		i++;
	}
}

void	close_pipes_and_wait(t_executor_ctx *ctx)
{
	int		i;
	int		status;
	pid_t 	pid;

	if (ctx->cmd_count > 1)
		close_unused_pipes(ctx->pipes, ctx->cmd_count - 1, DISCARD, DISCARD);
	setup_parent_exec_signals();
	i = 0;
	while (i < ctx->cmd_count)
	{
		pid = wait(&status);
		if (ctx->last_pid == pid)
			handle_child_status(status);
		i++;
	}
	setup_interactive_signals();
}

void	setup_pipes(int pipes[][2], int pipe_count, int idx)
{
	if (idx == 0)
	{
		dup2(pipes[0][1], STDOUT_FILENO);
		close_unused_pipes(pipes, pipe_count, pipes[0][1], DISCARD);
	}
	else if (idx == pipe_count)
	{
		dup2(pipes[idx - 1][0], STDIN_FILENO);
		close_unused_pipes(pipes, pipe_count, pipes[idx - 1][0], DISCARD);
	}
	else
	{
		dup2(pipes[idx - 1][0], STDIN_FILENO);
		dup2(pipes[idx][1], STDOUT_FILENO);
		close_unused_pipes(pipes, pipe_count, pipes[idx - 1][0], pipes[idx][1]);
	}
}

