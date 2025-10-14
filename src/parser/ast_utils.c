/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:36:24 by mbondare          #+#    #+#             */
/*   Updated: 2025/10/14 18:41:01 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//create new command node
t_node *new_cmd_node(void)
{
    t_cmd_node *cmd_node;
    t_node *node; 

    node = malloc(sizeof(t_node));
    if(!node)
        return (NULL); 
    node->type = NODE_CMD; 
    cmd_node = &node->as.cmd;
    cmd_node->args = NULL; 
    cmd_node->redirections = NULL; 
    return (node); 
}

//create new pipe node 
t_node *new_pipe_node(t_node *left, t_node *right)
{
    t_pipe_node *pipe_node;
    t_node *node;

    if (!left || !right)
        return (NULL);
    node = malloc(sizeof(t_node));
    if(!node)
        return (NULL); 
    node->type = NODE_PIPE; 
    pipe_node = &node->as.pipe;
    pipe_node->left = left; 
    pipe_node->right = right;
    return (node);  
}


//free redirection list
static void free_redirections(t_redir *redir)
{
    t_redir *tmp;

    while (redir)
    {
        tmp = redir->next;
        free(redir->filename); 
        free(redir); 
        redir = tmp;
    }
}

//free all ast
void free_ast(t_node *node)
{
    if (!node)
        return ; 
    if (node->type == NODE_PIPE)
    {
        free_ast(node->as.pipe.left);
        free_ast(node->as.pipe.right);
    }
    else if (node->type == NODE_CMD)
    {
        free_string_array(node->as.cmd.args);
        free_redirections(node->as.cmd.redirections); 
    }
    free (node);
}

int get_cmd_count(t_node *node)
{
    if (!node)
    {
        return (0);
    }
    if (node->type  == NODE_CMD)
        return (1);
    return get_cmd_count(node->as.pipe.left) + get_cmd_count(node->as.pipe.right);
}

//void execute(t_node *node, int pipes[][2], int total_count, int i)
//{
    
//}