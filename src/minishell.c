/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbondare <mbondare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:15:39 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/21 12:10:29 by mbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status = 0; 

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
        setup_interactive_signals(); 
        line = readline("minihell$ ");
        if(!line)
        {
            write(STDOUT_FILENO, "exit\n", 5);
            exit(g_exit_status); 
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
                    free_ast(ast); 
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

    shell_loop(&env); 

    return (g_exit_status);
} 


//int main (int argc, char **argv, char **envp)
//{
//    (void) argc; 
//    (void) argv;
//    t_env_lst *env = NULL;

//    init_env_lst(&env, envp);
//    char **new_envp = env_lst_to_arr(env);
//    (void) new_envp;
//    int i = 0;
//    while (new_envp[i] != NULL)
//    {
//        if (new_envp[i])
//            printf("%s\n", new_envp[i]);
//        i++;
//    }
    
//    return (0);
//} 
        