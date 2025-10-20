/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:35:45 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/16 20:11:26 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_redir_err_and_exit(char *filename)
{
	printf("minishell: %s: %s\n", filename, strerror(errno));
}
void redir_in(char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if(fd == -1)
		print_redir_err_and_exit(filename);
	dup2(fd, STDIN_FILENO);
	close (fd);
}

void redir_out(char *filename)
{
	int fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd == -1)
		print_redir_err_and_exit(filename);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void redir_append(char *filename)
{
	int fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if(fd == -1)
		print_redir_err_and_exit(filename);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void redir_heredoc(char *del)
{
	char *line;
	char *prompt;
	int fd[2];

	prompt = "> ";
	pipe(fd);
	line = readline(prompt);
	while (ft_strcmp(line, del) != 0)
	{
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
		line = readline(prompt);
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	free(line);
}