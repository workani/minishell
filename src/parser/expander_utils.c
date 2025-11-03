#include "minishell.h"

static int	count_non_empty(char **args)
{
	int	i;
	int	count;

	if (!args)
		return (0);
	i = 0;
	count = 0;
	while (args[i])
	{
		if (args[i][0] != '\0')
			count++;
		i++;
	}
	return (count);
}

static void	copy_non_empty(char **args, char **new_args)
{
	int	i;
	int	j;

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
}

char	**filter_empty_args(char **args)
{
	char	**new_args;
	int		count;

	if (!args)
		return (NULL);
	count = count_non_empty(args);
	if (count == 0)
		return (free(args), NULL);
	new_args = malloc(sizeof(char *) * (count + 1));
	if (!new_args)
		return (NULL);
	copy_non_empty(args, new_args);
	free(args);
	return (new_args);
}

void	process_double_quote(char **line, t_buffer *buf, t_env_lst *env)
{
	(*line)++;
	while (**line && **line != '"')
	{
		if (**line == '$')
			expand_variable(line, buf, env);
		else
		{
			append_char(buf, **line);
			(*line)++;
		}
	}
	if (**line == '"')
		(*line)++;
}

void	init_buffer(t_buffer *buf, size_t initial_capacity)
{
	buf->data = malloc(initial_capacity);
	if (!buf->data)
		exit(EXIT_FAILURE);
	buf->data[0] = '\0';
	buf->len = 0;
	buf->capacity = initial_capacity;
}
