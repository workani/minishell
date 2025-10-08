/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:15:39 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/08 16:16:09 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "../include/minishell.h"

void execute(t_node *ast, char **env)
{
    char *command;

	command = get_cmd(ast->as.cmd.args[0], env);
    if (fork() == 0)
    {
        execv(command, ast->as.cmd.args);
    }
    wait(NULL);
}

void shell_loop(char **env)
{
    char *line; 
    t_token *tokens;
    t_node *ast;

    while (1)
    {
        line = readline("minishell$ ");
        if(!line)
        {
            write(STDOUT_FILENO, "exit\n", 5);
            break;
        }
        if (*line) //to handle empty input
        {
            add_history(line);
            tokens = tokenize(line);
            if(tokens)
            {
                ast = parse (tokens); 
                if (ast)
                {
                    //print_ast(ast, 0);
                    execute(ast, env);
                    free_ast(ast); 
                }
                free_tokens(tokens);
            }
            //stuff to add
        }
        free(line); //free memory allocated by readline
    }
}

int main (int argc, char **argv, char **env)
{
    (void) argc; 
    (void) argv;


    shell_loop(env); 

    return (0);
} 