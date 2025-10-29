#include "minishell.h"

void	expand_variables(t_cmd_node *cmd_node, t_env_lst *env)
{
	int		i;
	char	*expanded;
	t_redir	*redir;

	i = 0;
	while (cmd_node->args && cmd_node->args[i])
	{
		expanded = expand_line(cmd_node->args[i], env);
		free(cmd_node->args[i]);
		cmd_node->args[i] = expanded;
		i++;
	}
	redir = cmd_node->redirections;
	while (redir)
	{
		expanded = expand_line(redir->filename, env);
		free(redir->filename);
		redir->filename = expanded;
		redir = redir->next;
	}
}