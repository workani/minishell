/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:40:00 by dklepenk          #+#    #+#             */
/*   Updated: 2025/11/05 17:40:00 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home_dir(t_env_lst *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, "HOME") == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static int	set_path_and_check_errors(
		char **args,
		t_env_lst *env,
		char **path)
{
	if (!args[1])
	{
		*path = get_home_dir(env);
		if (!(*path))
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (FAILURE);
		}
	}
	else if (args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (FAILURE);
	}
	else
		*path = args[1];
	return (SUCCESS);
}

int	builtin_cd(char **args, t_env_lst **env)
{
	int			exit_status;
	char		*path;
	char		old_pwd[PATH_MAX];
	char		new_pwd[PATH_MAX];

	exit_status = set_path_and_check_errors(args, *env, &path);
	if (exit_status == FAILURE)
		return (FAILURE);
	getcwd(old_pwd, PATH_MAX);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		perror(path);
		exit_status = FAILURE;
	}
	add_or_update_env(env, "OLDPWD", old_pwd, false);
	if (getcwd(new_pwd, PATH_MAX))
		add_or_update_env(env, "PWD", new_pwd, false);
	return (exit_status);
}
