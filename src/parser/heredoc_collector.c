#include "minishell.h"

static char	*read_heredoc_input(char *delimiter, t_env_lst *env)
{
	char	*line;
	char	*content;
	char	*temp;
	char	*expanded;

	content = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (g_signal_received == 130 || !line)
		{
			free(content);
			if (line)
				free(line);
			return (NULL);
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		expanded = expand_line(line, env);
		temp = content;
		content = ft_strjoin(content, expanded);
		free(temp);
		temp = content;
		content = ft_strjoin(content, "\n");
		free(temp);
		free(line);
		free(expanded);
	}
	return (content);
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