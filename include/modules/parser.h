/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:06:17 by workani           #+#    #+#             */
/*   Updated: 2025/11/03 17:07:41 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "types.h"

// Tokenizer functions
t_token	*tokenize(char *input);
int		handle_word(char *input, int i, t_token **token_list);
int		handle_metachar(char *input, int i, t_token **token_list);
int		handle_quotes(char *input, int i, t_token **token_list);

// Token management
t_token	*new_token(char *value, t_token_type type);
void	add_token_to_list(t_token **list_head, t_token *new);
void	free_tokens(t_token *tokens);
void	print_tokens(t_token *tokens);

// AST functions
t_node	*new_cmd_node(void);
t_node	*new_pipe_node(t_node *left, t_node *right);
t_node	*parse(t_token *tokens);
void	free_ast(t_node *node);
int		get_cmd_count(t_node *node);
void	print_ast(t_node *node, int level);

// Expander str utils
void	append_char(t_buffer *buf, char c);
void	append_str(t_buffer *buf, const char *str);
int		get_var_len(char *str);

void	process_double_quote(char **line, t_buffer *buf, t_env_lst *env);
char	**filter_empty_args(char **args);
void	init_buffer(t_buffer *buf, size_t initial_capacity);

#endif
