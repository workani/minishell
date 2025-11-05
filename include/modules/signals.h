/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:22:56 by dklepenk          #+#    #+#             */
/*   Updated: 2025/11/05 16:55:22 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

/* Setup signals */
void	setup_interactive_signals(void);
void	setup_child_signals(void);
void	setup_parent_exec_signals(void);
void	setup_heredoc_signals(void);

/* Handle signals */
void	handle_sigint_interactive(int sig);
void	handle_sigint_heredoc(int sig);

#endif
