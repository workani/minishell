/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:50:25 by workani           #+#    #+#             */
/*   Updated: 2025/11/04 19:19:42 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

void	handle_child_status(int status)
{
	if (WIFEXITED(status))
		g_signal_received = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
		g_signal_received = 128 + WTERMSIG(status);
	}
}

void	handle_exec_errors(char *cmd, int exec_errno)
{
	if (cmd && (exec_errno == EACCES || exec_errno == EISDIR))
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: %s\n", cmd,
			strerror(exec_errno));
		exit(126);
	}
	else
	{
		ft_printf_fd(STDERR_FILENO, "minishell: command not found: %s\n", cmd);
		exit(127);
	}
}

void	handle_redirs_with_no_cmd(t_cmd_node *node, t_env_lst *env)
{
	pid_t	pid;

	if (node->redirections)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			g_signal_received = 1;
			return ;
		}
		if (pid == 0)
		{
			setup_child_signals();
			setup_redirections(node->redirections, env);
			exit(g_signal_received);
		}
	}
}
