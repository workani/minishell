/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:35:45 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/28 19:11:15 by dklepenk         ###   ########.fr       */
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
	g_signal_received = 1;
	exit(1);
}

void	redir_in(char *filename)
{
	int	fd;

	if (!filename)
		return ;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		print_redir_err_and_exit(filename);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	redir_out(char *filename)
{
	int	fd;

	if (!filename)
		return ;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		print_redir_err_and_exit(filename);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redir_append(char *filename)
{
	int	fd;

	if (!filename)
		return ;
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		print_redir_err_and_exit(filename);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redir_heredoc(char *del, char *content)
{
	int fd[2];

	if (!del)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			2);
		g_signal_received = 2;
		return ;
	}
	if (!content)
		return ;
	if (pipe(fd) == -1)
	{
		perror("pipe");
		g_signal_received = 1;
		return ;
	}
	write(fd[1], content, ft_strlen(content));
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}