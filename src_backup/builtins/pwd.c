/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:50:35 by mbondare          #+#    #+#             */
/*   Updated: 2025/10/24 15:21:21 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(void)
{
	char	*cwd;

	cwd = malloc(PATH_MAX);
	if (!cwd)
	{
		perror("pwd:error");
		return (FAILURE);
	}
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		perror("pwd:error");
		free(cwd);
		return (FAILURE);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (SUCCESS);
}
