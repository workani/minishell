/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:48:57 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/08 16:06:08 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_env_lst
{
	char *value;
	struct s_env_lst *next;
} t_env_lst;

typedef enum e_token_type
{
    TOKEN_WORD, 
    TOKEN_PIPE,
    TOKEN_REDIR_IN,
    TOKEN_REDIR_OUT,
    TOKEN_REDIR_APPEND,
    TOKEN_HEREDOC,
}   t_token_type;

//token structs
typedef struct s_token
{
    t_token_type type;
    char *value;
    struct s_token *next;
} t_token;

typedef t_token_type    t_redir_type; //enum for redirection

//enum for node types
typedef enum e_node_type
{
    NODE_CMD,
    NODE_PIPE
} t_node_type;

//redirection
typedef struct s_redir 
{
    t_redir_type type; 
    char *filename;
    struct s_redir *next;
} t_redir;

//node for simple commands
typedef struct s_cmd_node
{
    char **args;
    t_redir *redirections; 
} t_cmd_node;

//node for pipes
typedef struct s_pipe_node
{
    struct s_node *left;
    struct s_node *right;
} t_pipe_node;

//generic ast node
typedef struct s_node
{
    t_node_type type;
    union 
    {
        t_cmd_node cmd;
        t_pipe_node pipe;
    } as;
} t_node;

#endif