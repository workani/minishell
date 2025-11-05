/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:57:56 by dklepenk          #+#    #+#             */
/*   Updated: 2025/11/03 17:08:48 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_single_quote(char **line, t_buffer *buf)
{
	(*line)++;
	while (**line && **line != '\'')
	{
		append_char(buf, **line);
		(*line)++;
	}
	if (**line == '\'')
		(*line)++;
}

static void	expand_exit_status(char **line, t_buffer *buf)
{
	char	*status_str;

	status_str = ft_itoa(g_signal_received);
	append_str(buf, status_str);
	free(status_str);
	(*line) += 1;
}

void	expand_variable(char **line, t_buffer *buf, t_env_lst *env)
{
	char		*var_name;
	char		*var_value;
	int			len;

	(*line)++;
	if (**line == '?')
		return (expand_exit_status(line, buf));
	len = get_var_len(*line);
	if (len == 0)
	{
		append_char(buf, '$');
		return ;
	}
	var_name = ft_substr(*line, 0, len);
	var_value = get_env_value(var_name, env);
	if (var_value)
		append_str(buf, var_value);
	free(var_name);
	(*line) += len;
}

void	expand_variables(t_cmd_node *cmd_node, t_env_lst *env)
{
	int		i;
	char	*expanded;
	t_redir	*redir;

	if (cmd_node->args)
	{
		i = 0;
		while (cmd_node->args[i])
		{
			expanded = expand_line(cmd_node->args[i], env);
			free(cmd_node->args[i]);
			cmd_node->args[i] = expanded;
			i++;
		}
		cmd_node->args = filter_empty_args(cmd_node->args);
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

char	*expand_line(char *line, t_env_lst *env)
{
	t_buffer	buf;

	init_buffer(&buf, ft_strlen(line) + 128);
	while (*line)
	{
		if (*line == '\'')
			process_single_quote(&line, &buf);
		else if (*line == '"')
			process_double_quote(&line, &buf, env);
		else if (*line == '$')
			expand_variable(&line, &buf, env);
		else
		{
			append_char(&buf, *line);
			line++;
		}
	}
	return (buf.data);
}
