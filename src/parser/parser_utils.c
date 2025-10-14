/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:20:45 by mbondare          #+#    #+#             */
/*   Updated: 2025/10/14 18:50:21 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static void print_indent(int level)
//{
//    int i; 
//    i = 0; 

//    while (i < level)
//    {
//        printf("  ");
//        i++;
//    }
//}

//void print_ast(t_node *node, int level)
//{
//    int i; 
//    t_redir *redir;

//    if (node == NULL)
//        return ; 
//    print_indent(level);
//    if (node->type == NODE_PIPE)
//    {
//        printf("pipe\n");
//        print_ast(node->as.pipe.left, level + 1); 
//        print_ast(node->as.pipe.right, level + 1);
//    }
//    else if (node->type == NODE_CMD)
//    {
//        printf("cmd\n"); 
//        print_indent(level + 1); 
//        printf("args: ");
//        i = 0; 
//        if (node->as.cmd.args)
//        {
//            while(node->as.cmd.args[i])
//            {
//                printf("[%s] ", node->as.cmd.args[i]);
//                i++;
//            }
//        }
//        printf("\n"); 
//        redir = node->as.cmd.redirections;
//        if (redir)
//        {
//            print_indent(level + 1); 
//            printf("redirs: ");
//            while(redir)
//            {
//                printf("(%d, %s) ", redir->type, redir->filename);
//                redir = redir->next;
//            }
//            printf("\n"); 
//        }
        
//    }
//}

void print_ast(t_node *node, int count)
{
    if (!node)
        return;
    
    if (node->type == NODE_PIPE)
    {
        printf("pipe\n");
        print_ast(node->as.pipe.left, count + 1);
        print_ast(node->as.pipe.right, count + 1);
    }
    else
    {
        
        printf("[value: %s | count: %d]\n", node->as.cmd.args[0], count);
    }
}