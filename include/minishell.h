/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:42:00 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/16 18:44:05 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <dirent.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <curses.h>
#include <term.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>

#include "defines.h"
#include "types.h"
#include "../libft/libft.h"

char *get_cmd(char *cmd, char **);
void free_string_array(char **arr);

int get_envp_lst_size(t_envp_lst *head);
char **_lst_to_arr(t_envp_lst *head);
void print_envp_lst(t_envp_lst *head);
void init_envp_lst(t_envp_lst **head, char **envp);

t_token *tokenize (char *input);
int handle_word(char *input, int i, t_token **token_list);
int handle_metachar(char *input, int i, t_token **token_list);
int handle_quotes(char *input, int i, t_token **token_list);


t_token *new_token(char *value, t_token_type type);
void add_token_to_list(t_token **list_head, t_token *new);
void free_tokens(t_token *tokens);
void print_tokens(t_token *tokens);

t_node *new_cmd_node(void);
t_node *new_pipe_node(t_node *left, t_node *right);
t_node *parse(t_token *tokens);
void free_ast(t_node *node);
int get_cmd_count(t_node *node);
void print_ast(t_node *node, int level);

void close_unused_pipes(int pipes[][2], int len, int exeception_one, int exeception_two);
void close_pipes_and_wait(int pipes[][2], int cmd_count);
void setup_pipes(int pipes[][2], int pipe_count, int idx);

void execute(t_node *node, int (*pipes)[2], int cmd_count, char **envp, int *idx);

bool is_builtin(char *cmd);
int builtin_echo(char **args);
int builtin_envp(char **envp);
int builtin_exit(char **args);
int builtin_pwd();

void setup_redirections(t_redir *node);
void redir_in(char *filename);
void redir_out(char *filename);
void redir_append(char *filename);
void redir_heredoc(char *del);

#endif

