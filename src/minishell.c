/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:15:39 by dklepenk          #+#    #+#             */
/*   Updated: 2025/11/05 18:37:24 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

static void	create_pipes(t_executor_ctx *ctx, int pipes_count)
{
	int	i;
	int	(*pipes)[2];

	i = 0;
	pipes = malloc(sizeof(*pipes) * pipes_count);
	while (i < pipes_count)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(1);
		}
		i++;
	}
	ctx->pipes = pipes;
}

static void	execute_ast(t_node *ast, int cmd_count, t_env_lst **env)
{
	t_executor_ctx	ctx;

	if (cmd_count <= 0)
		return ;
	ctx.idx = 0;
	ctx.env = env;
	ctx.pipes = NULL;
	ctx.last_pid = 0;
	ctx.cmd_count = cmd_count;
	if (cmd_count > 1)
		create_pipes(&ctx, cmd_count - 1);
	execute(ast, &ctx);
	close_pipes_and_wait(&ctx);
	free(ctx.pipes);
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
	t_env_lst	*env;

	(void)argc;
	(void)argv;
	env = NULL;
	init_env_lst(&env, envp);
	shell_loop(&env);
	return (g_signal_received);
}
