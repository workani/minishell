/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:15:39 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/21 19:53:23 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void execute_ast(t_node *ast, int cmd_count, t_env_lst **env)
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
    execute(ast, pipes, cmd_count, env, &idx);
    close_pipes_and_wait(pipes, cmd_count);
}


void shell_loop(t_env_lst **env)
{
    char *line; 
    t_token *tokens;
    t_node *ast;

    while (1)
    {
        line = readline(PROMPT);
        if(!line)
        {
            write(STDOUT_FILENO, "exit\n", 5);
            break;
        }
        if (*line)
        {
            add_history(line);
            tokens = tokenize(line);
            if(tokens)
            {
                ast = parse (tokens); 
                if (ast)
                {
                    int count = get_cmd_count(ast);
                    execute_ast(ast, count, env);
                }
                free_tokens(tokens);
            }
        }
        free(line);
    }
}

int main (int argc, char **argv, char **envp)
{
    (void) argc; 
    (void) argv;
    t_env_lst *env;

    
    env = NULL;
    init_env_lst(&env, envp);
    shell_loop(&env); 

    return (0);
} 


//int main (int argc, char **argv, char **envp)
//{
//    (void) argc; 
//    (void) argv;
//    t_env_lst *env = NULL;

//    init_env_lst(&env, envp);
//    char **new_envp = env
    
//    return (0);
//} 
        