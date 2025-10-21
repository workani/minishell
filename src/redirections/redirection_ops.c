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

extern volatile sig_atomic_t g_heredoc_interrupted; 

void redir_heredoc(char *del)
{
	char *line; 
	int fd[2]; 
	int original_stdin;

	original_stdin = dup(STDIN_FILENO);

	setup_heredoc_signals(); 

	if(pipe(fd) == -1)
	{
		perror("pipe"); 
		return; 
	}
	g_heredoc_interrupted = 0; 
	while (1)
	{
		line = readline("> "); 
		if(g_heredoc_interrupted)
		{
			if(line) free(line);
			close(fd[0]);
			clode(fd[1]); 
			dup2(original_stdin, STDIN_FILENO);
			close(original_stdin);
			exit(130);
		}
		if(!line || ft_strcmp(line, del) == 0)
		{
			if(line) free(line);
			break;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1); 
		free(line); 
	}
	close(fd[1]); 
	dup2(fd[0], STDOUT_FILENO);
	close(fd[0]); 

	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
	setup_interactive_signals();
}
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