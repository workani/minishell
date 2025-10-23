#include "minishell.h"

static void	print_sorted_env(t_env_lst *env)
{
	t_env_lst	*current;
	t_env_lst	*min;
	t_env_lst	*iter;

	current = env;
	while (current)
	{
		min = NULL;
		iter = env;
		while (iter)
		{
			if ((!min || ft_strcmp(iter->value, min->value) < 0)
				&& ft_strcmp(iter->value, current->value) >= 0)
				min = iter;
			iter = iter->next;
		}
		if (min)
			printf("declare -x %s\n", min->value);
		current = current->next;
	}
}

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str || ft_isdigit(*str))
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	update_or_add_env(t_env_lst **env, char *var)
{
	t_env_lst	*current;
	t_env_lst	*new;
	int			var_len;

	current = *env;
	var_len = 0;
	while (var[var_len] && var[var_len] != '=')
		var_len++;
	while (current)
	{
		if (ft_strncmp(current->value, var, var_len) == 0
			&& (current->value[var_len] == '=' 
			|| current->value[var_len] == '\0'))
		{
			current->value = ft_strdup(var);
			return ;
		}
		current = current->next;
	}
	new = malloc(sizeof(t_env_lst));
	new->value = ft_strdup(var);
	new->next = *env;
	*env = new;
}

int	builtin_export(char **args, t_env_lst **env)
{
	int	i;
	int	status;

	if (!args[1])
	{
		print_sorted_env(*env);
		return (SUCCESS);
	}
	i = 1;
	status = SUCCESS;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = FAILURE;
		}
		else
			update_or_add_env(env, args[i]);
		i++;
	}
	return (status);
}
