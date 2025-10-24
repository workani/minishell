#include "minishell.h"

static void	run_redirection(t_token_type redir_type, char *filename)
{
	if (redir_type == TOKEN_REDIR_IN)
		redir_in(filename);
	if (redir_type == TOKEN_REDIR_OUT)
		redir_out(filename);
	if (redir_type == TOKEN_REDIR_APPEND)
		redir_append(filename);
	if (redir_type == TOKEN_HEREDOC)
		redir_heredoc(filename);
}

void	setup_redirections(t_redir *node)
{
	if (!node)
		return ;
	while (node != NULL)
	{
		run_redirection(node->type, node->filename);
		node = node->next;
	}
}