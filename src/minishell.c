/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:15:39 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/14 19:20:36 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void execute(char *cmd, char **env)
//{
//    char *full_cmd = get_cmd(cmd, env);
//    if (!full_cmd)
//    {
//        printf("Incorrect command!\n");
//        exit(0);
//    }
    
//    char *args[] = {full_cmd, NULL};
//    execve(args[0], args, env);
//}

//void execute(t_node *ast, char **env)
//{
//    char *command;

//	command = get_cmd(ast->as.cmd.args[0], env);
//    if (fork() == 0)
//    {
//        execv(command, ast->as.cmd.args);
//    }
//    wait(NULL);
//}


void handle_ast(t_node *ast, int cmd_count)
{
    int i;
    int idx;
    int pipes[cmd_count - 1][2];
    
    i = 0;
    idx = 0;
    while (i < cmd_count - 1)
    {
        pipe(pipes[i]);
        i++;
    }
    execute(ast, pipes, cmd_count, &idx);
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
                    (void) env;
                    int count = get_cmd_count(ast);
                    handle_ast(ast, count);
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
