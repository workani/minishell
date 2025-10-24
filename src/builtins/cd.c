
#include "minishell.h"

static char	*get_home_dir(t_env_lst *env)
{
	while (env)
	{
		if (ft_strncmp(env->value, "HOME=", 5) == 0)
			return (env->value + 5);
		env = env->next;
	}
	return (NULL);
}

int	builtin_cd(char **args, t_env_lst **env)
{
	char	*path;

	if (!args[1])
	{
		path = get_home_dir(*env);
		if (!path)
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
		path = args[1];
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		perror(path);
		return (FAILURE);
	}
	return (SUCCESS);
}