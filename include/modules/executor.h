/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:06:44 by workani           #+#    #+#             */
/*   Updated: 2025/11/03 18:38:17 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "types.h"

// Main execution
void	execute(t_node *node, int (*pipes)[2], int cmd_count, \
				t_env_lst **env, int *idx);
void	execute_cmd(t_cmd_node *node, int pipes[][2], int cmd_count, \
				t_env_lst **env, int idx);

// Pipe management
void	close_unused_pipes(int pipes[][2], int len, int exception_one,\
	int exception_two);
void	close_pipes_and_wait(int pipes[][2], int cmd_count);
void	setup_pipes(int pipes[][2], int pipe_count, int idx);

// Redirection functions
void	setup_redirections(t_redir *node, t_env_lst *env);
void	redir_in(char *filename);
void	redir_out(char *filename);
void	redir_append(char *filename);
void	redir_heredoc(char *del, char *content);
void	collect_all_heredocs(t_node *ast, t_env_lst *env);

// Signal handling
void	setup_interactive_signals(void);
void	setup_child_signals(void);
void	setup_parent_exec_signals(void);
void	setup_heredoc_signals(void);

// Handlers
void	handle_child_status(int status);
void	handle_exec_errors(char *cmd, int exec_errno);
void	handle_redirs_with_no_cmd(t_cmd_node *node, t_env_lst *env);

// Fd helpers
void	backup_fds(int dest[3]);
void	restore_fds(int src[3]);

#endif
