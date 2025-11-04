/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:51:53 by mbondare          #+#    #+#             */
/*   Updated: 2025/11/04 15:33:24 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

static void	handle_sigint_interactive(int sig)
{
	(void)sig;
	g_signal_received = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_sigquit_interactive(int sig)
{
	(void)sig;
	if (rl_line_buffer && rl_end > 0)
	{
		write(STDOUT_FILENO, "\nexit\n", 6);
		exit(131);
	}
}

static void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_signal_received = 130;
	write(STDOUT_FILENO, "\n", 1);
}

void	setup_interactive_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = handle_sigint_interactive;
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = handle_sigquit_interactive;
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	setup_child_signals(void)
{
	struct sigaction	sa_default;

	sigemptyset(&sa_default.sa_mask);
	sa_default.sa_handler = SIG_DFL;
	sa_default.sa_flags = 0;
	sigaction(SIGINT, &sa_default, NULL);
	sigaction(SIGPIPE, &sa_default, NULL);
	sigaction(SIGQUIT, &sa_default, NULL);
}

void	setup_parent_exec_signals(void)
{
	struct sigaction	sa_ignore;

	sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_handler = SIG_IGN;
	sa_ignore.sa_flags = 0;
	sigaction(SIGINT, &sa_ignore, NULL);
	sigaction(SIGPIPE, &sa_ignore, NULL);
	sigaction(SIGQUIT, &sa_ignore, NULL);
}

void	setup_heredoc_signals(void)
{
	struct sigaction sa_heredoc;
	struct sigaction sa_quit;

	sigemptyset(&sa_heredoc.sa_mask);
	sa_heredoc.sa_handler = handle_sigint_heredoc;
	sa_heredoc.sa_flags = 0;
	sigaction(SIGINT, &sa_heredoc, NULL);
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}