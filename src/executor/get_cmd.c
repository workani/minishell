/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: workani <workani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:27:34 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/31 05:21:45 by workani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_paths(char **envp)
{
	int		i;
	char	*trimmed;
	char	**result;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], PATH_PREFIX, PATH_PREFIX_LEN))
		{
			trimmed = ft_substr(envp[i], PATH_PREFIX_LEN, (ft_strlen(envp[i])
						- PATH_PREFIX_LEN));
			
			result = (ft_split(trimmed, ':'));
			free(trimmed);
			return (result);
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
	full_cmd[i] = '\0';
	return (full_cmd);
}

char *set_cmd(char *cmd, char **envp)
{
	char *full_cmd;

	if (has_slash(cmd))
		full_cmd = cmd;
	else
		full_cmd = get_cmd(cmd, envp);
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
			free_string_array(paths);
			return (full_cmd);
		}
		i++;
		free(full_cmd);
	}
	free_string_array(paths);
	return (NULL);
}