/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:22:35 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/15 17:48:48 by dklepenk         ###   ########.fr       */
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
		full_cmd = ft_strjoin(paths[i], cmd);
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