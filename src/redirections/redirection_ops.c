/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbondare <mbondare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:35:45 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/21 12:32:36 by mbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_redir_err_and_exit(char *filename)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	redir_in(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		print_redir_err_and_exit(filename);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	redir_out(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		print_redir_err_and_exit(filename);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redir_append(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		print_redir_err_and_exit(filename);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	heredoc_loop(int fd[2], char *del)
{
	char	*line;

	g_signal_received = 0;
	while (1)
	{
		line = readline("> ");
		if (g_signal_received == 130 || !line)
		{
			if (line)
				free(line);
			break;
		}
		if (ft_strcmp(line, del) == 0)
		{
			free(line);
			break;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
}

void	redir_heredoc(char *del)
{
	int	fd[2];
	int	original_stdin;

	original_stdin = dup(STDIN_FILENO);
	setup_heredoc_signals();
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return;
	}
	heredoc_loop(fd, del);
	close(fd[1]);
	if (g_signal_received != 130)
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
	setup_interactive_signals();
	if (g_signal_received == 130)
		exit(130);
}