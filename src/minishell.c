/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:15:39 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/31 20:56:46 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

static void	create_pipes(int pipes[][2], int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(1);
		}
		i++;
	}
}

static void	execute_ast(t_node *ast, int cmd_count, t_env_lst **env)
{
	int	idx;
	int	pipes[cmd_count - 1][2];

	if (cmd_count <= 0)
		return ;
	idx = 0;
	if (cmd_count > 1)
		create_pipes(pipes, cmd_count);
	execute(ast, pipes, cmd_count, env, &idx);
	close_pipes_and_wait(pipes, cmd_count);
}

static void	process_line(char *line, t_env_lst **env)
{
	t_token	*tokens;
	t_node	*ast;
	int		count;

	tokens = tokenize(line);
	if (tokens)
	{
		ast = parse(tokens);
		if (ast)
		{
			collect_all_heredocs(ast, *env);
			if (g_signal_received != 130)
			{
				count = get_cmd_count(ast);
				execute_ast(ast, count, env);
			}
			free_ast(ast);
		}
		free_tokens(tokens);
	}
}

static void	shell_loop(t_env_lst **env)
{
	char	*line;

	while (1)
	{
		setup_interactive_signals();
		if (g_signal_received == 130)
			g_signal_received = 1;      

		line = readline(PROMPT);
		if (!line)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			free_env_lst(env);
			exit(g_signal_received);
		}
		if (*line)
		{
			add_history(line);
			process_line(line, env);
			if (g_signal_received == 130)
				g_signal_received = 1;
		}
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env_lst *env;

	(void)argc;
	(void)argv;
	env = NULL;
	init_env_lst(&env, envp);
	shell_loop(&env);
	return (g_signal_received);
}