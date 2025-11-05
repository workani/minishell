/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:27:34 by dklepenk          #+#    #+#             */
/*   Updated: 2025/11/05 17:43:00 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_paths(char **envp)
{
	int		i;
	size_t	len;
	char	*trimmed;
	char	**result;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], PATH_PREFIX, PATH_PREFIX_LEN))
		{
			len = ft_strlen(envp[i]) - PATH_PREFIX_LEN;
			trimmed = ft_substr(envp[i], PATH_PREFIX_LEN, len);
			if (!trimmed)
				return (NULL);
			result = ft_split(trimmed, ':');
			free(trimmed);
			return (result);
		}
		i++;
	}
	return (NULL);
}

static char	*compose_full_cmd(char *path, char *cmd)
{
	int		i;
	size_t	len;
	char	*full_cmd;

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

char	*set_cmd(char *cmd, char **envp)
{
	if (has_slash(cmd))
		return (cmd);
	return (get_cmd(cmd, envp));
}

char	*get_cmd(char *cmd, char **envp)
{
	int		i;
	char	*full_cmd;
	char	**paths;

	paths = get_paths(envp);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_cmd = compose_full_cmd(paths[i], cmd);
		if (full_cmd && access(full_cmd, R_OK | X_OK) != -1)
		{
			free_string_array(paths);
			return (full_cmd);
		}
		free(full_cmd);
		i++;
	}
	free_string_array(paths);
	return (NULL);
}
