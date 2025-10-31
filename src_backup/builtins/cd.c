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

static int set_path_and_check_errors(char **args, t_env_lst *env, char **path)
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
	char *path;
	char old_pwd[PATH_MAX];
	char new_pwd[PATH_MAX];

	if (set_path_and_check_errors(args, *env, &path) == FAILURE)
		return (FAILURE);
	if (!getcwd(old_pwd, PATH_MAX))
		old_pwd[0] = '\0';
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (FAILURE);
	}
	if (old_pwd[0])
		add_or_update_env_var(env, ft_strdup("OLDPWD"), ft_strdup(old_pwd));
	if (getcwd(new_pwd, PATH_MAX))
		add_or_update_env_var(env, ft_strdup("PWD"), ft_strdup(new_pwd));
	return (SUCCESS);
}