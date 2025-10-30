/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:42:00 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/30 19:47:51 by dklepenk         ###   ########.fr       */
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
#include <stdbool.h>

#include "defines.h"
#include "types.h"
#include "../libft/libft.h"

// Global variable for signals
extern volatile sig_atomic_t g_signal_received;


char *get_cmd(char *cmd, char **);
char *set_cmd(char *cmd, char **envp);

// Utils
void free_string_array(char **arr);
bool	 has_slash(char *str);

// Environment list functions
int get_env_lst_size(t_env_lst *head);
char **env_lst_to_arr(t_env_lst *head);
void print_env_lst(t_env_lst *head);
void init_env_lst(t_env_lst **head, char **envp);
void add_env_node(t_env_lst **head, char *key, char *value);
void add_or_update_env_var(t_env_lst **head, char *key, char *value);
char	*get_env_value(const char *key, t_env_lst *head);
bool convert_var_to_key_value_pair(char *dst[2], char *var);
void delete_env_node(t_env_lst **head, char *key);

// Tokenizer functions
t_token *tokenize (char *input);
int handle_word(char *input, int i, t_token **token_list);
int handle_metachar(char *input, int i, t_token **token_list);
int handle_quotes(char *input, int i, t_token **token_list);
char *expand_line(char *line, t_env_lst *env);

// Token functions
t_token *new_token(char *value, t_token_type type);
void add_token_to_list(t_token **list_head, t_token *new);
void free_tokens(t_token *tokens);
void print_tokens(t_token *tokens);

// AST functions
t_node *new_cmd_node(void);
t_node *new_pipe_node(t_node *left, t_node *right);
t_node *parse(t_token *tokens);
void free_ast(t_node *node);
int get_cmd_count(t_node *node);
void print_ast(t_node *node, int level);

// Pipe functions
void close_unused_pipes(int pipes[][2], int len, int exception_one, int exception_two);
void close_pipes_and_wait(int pipes[][2], int cmd_count);
void setup_pipes(int pipes[][2], int pipe_count, int idx);

// Executor functions
void execute(t_node *node, int (*pipes)[2], int cmd_count, t_env_lst **env, int *idx);
void execute_cmd(t_cmd_node *node, int pipes[][2], int cmd_count, t_env_lst **env, int idx);

// Builtin functions
bool is_builtin(char *cmd);
bool is_valid_var_name(const char *var);

int builtin_echo(char **args);
int builtin_env(t_env_lst *env);
int builtin_unset(char **args, t_env_lst **env);
int builtin_export(char **args, t_env_lst **env);
int builtin_exit(char **args);
int builtin_pwd(void);
int builtin_cd(char **args, t_env_lst **env);
void expand_variables(t_cmd_node *cmd_node, t_env_lst *env);


// Redirection functions
void setup_redirections(t_redir *node);
void redir_in(char *filename);
void redir_out(char *filename);
void redir_append(char *filename);
void redir_heredoc(char *del);

// Signal functions
void setup_interactive_signals(void);
void setup_child_signals(void);
void setup_parent_exec_signals(void);
void setup_heredoc_signals(void);

#endif
