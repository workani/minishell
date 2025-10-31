/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: workani <workani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:22:35 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/24 21:19:10 by workani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(char **envp)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], PATH_PREFIX, PATH_PREFIX_LEN))
		{
			trimmed = ft_substr(envp[i], PATH_PREFIX_LEN, (ft_strlen(envp[i])
						- PATH_PREFIX_LEN));
			return (ft_split(trimmed, ':'));
		}
		i++;
	}
	return (NULL);
}

static char *compose_full_cmd(char *path, char *cmd)
{
	int i;
	int len;
	char *full_cmd;

	i = 0;
	len = ft_strlen(path) + ft_strlen(cmd) + 2;
	full_cmd = malloc(len);
	if (!full_cmd)
		return (NULL);
	ft_append_str(full_cmd, &i, path);
	ft_append_str(full_cmd, &i, "/");
	ft_append_str(full_cmd, &i, cmd);
	return (full_cmd);
}

char	*get_cmd(char *cmd, char **envp)
{
	int		i;
	char	*full_cmd;
	char	**paths;

	i = 0;
	paths = get_paths(envp);
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		full_cmd = compose_full_cmd(paths[i], cmd);
		if (access(full_cmd, R_OK | X_OK) != -1)
		{
			free(paths);
			return (full_cmd);
		}
		i++;
		free(full_cmd);
	}
	return (NULL);
}
void	free_string_array(char **arr)
{
	int i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}