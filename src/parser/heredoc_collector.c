#include "minishell.h"

static int	append_line(char **content, char *line, t_env_lst *env)
{
	char	*expanded;
	char	*temp;

	expanded = expand_line(line, env);
	temp = *content;
	*content = ft_strjoin(*content, expanded);
	free(temp);
	temp = *content;
	*content = ft_strjoin(*content, "\n");
	free(temp);
	free(expanded);
	return (0);
}

static char	*read_heredoc_input(char *delimiter, t_env_lst *env)
{
	char	*line;
	char	*content;

	content = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (g_signal_received == 130 || !line)
			return (free(content), line ? free(line), NULL : NULL);
		if (ft_strcmp(line, delimiter) == 0)
			return (free(line), content);
		append_line(&content, line, env);
		free(line);
	}
}

static void	collect_cmd_heredocs(t_cmd_node *cmd, t_env_lst *env)
{
	t_redir	*redir;

	redir = cmd->redirections;
	while (redir && g_signal_received != 130)
	{
		if (redir->type == TOKEN_HEREDOC)
		{
			redir->heredoc_content = read_heredoc_input(redir->filename, env);
			if (!redir->heredoc_content)
				return ;
		}
		redir = redir->next;
	}
}

static void	collect_heredocs_recursive(t_node *node, t_env_lst *env)
{
	if (!node || g_signal_received == 130)
		return ;
	if (node->type == NODE_PIPE)
	{
		collect_heredocs_recursive(node->as.pipe.left, env);
		collect_heredocs_recursive(node->as.pipe.right, env);
	}
	else if (node->type == NODE_CMD)
	{
		collect_cmd_heredocs(&node->as.cmd, env);
	}
}

void	collect_all_heredocs(t_node *ast, t_env_lst *env)
{
	setup_heredoc_signals();
	collect_heredocs_recursive(ast, env);
	setup_interactive_signals();
}