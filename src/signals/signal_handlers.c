/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:21:44 by dklepenk          #+#    #+#             */
/*   Updated: 2025/11/04 19:22:18 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint_interactive(int sig)
{
	(void)sig;
	g_signal_received = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit_interactive(int sig)
{
	(void)sig;
	if (rl_line_buffer && rl_end > 0)
	{
		write(STDOUT_FILENO, "\nexit\n", 6);
		exit(131);
	}
}

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_signal_received = 130;
	write(STDOUT_FILENO, "\n", 1);
}