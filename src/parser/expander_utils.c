#include "minishell.h"

static int	count_non_empty(char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (args && args[i])
	{
		if (args[i][0] != '\0')
			count++;
		i++;
	}
	return (count);
}

static char	**filter_empty_args(char **args)
{
	char	**new_args;
	int		i;
	int		j;
	int		count;

	count = count_non_empty(args);
	new_args = malloc(sizeof(char *) * (count + 1));
	if (!new_args)
		return (NULL);
	i = 0;
	j = 0;
	while (args[i])
	{
		if (args[i][0] != '\0')
			new_args[j++] = args[i];
		else
			free(args[i]);
		i++;
	}
	new_args[j] = NULL;
	free(args);
	return (new_args);
}

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
	cmd_node->args = filter_empty_args(cmd_node->args);
	redir = cmd_node->redirections;
	while (redir)
	{
		expanded = expand_line(redir->filename, env);
		free(redir->filename);
		redir->filename = expanded;
		redir = redir->next;
	}
}