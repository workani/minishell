#include "minishell.h"

static char *get_env_value(const char *var_name, t_env_lst *env);

static char *handle_dollar(char **arg_ptr, t_env_lst *env)
{
    char *var_name;
    char *var_value;
    int i; 
    char *temp;

    (*arg_ptr)++;
    if(**arg_ptr == '?')
    {
        (*arg_ptr)++;
    return (ft_itoa(g_signal_received));
    }
    i = 0; 
    while(ft_isalnum((*arg_ptr)[i]) || (*arg_ptr)[i] == '_')
        i++;
    var_name = ft_substr(*arg_ptr, 0, i);
    *arg_ptr += i;
    var_value = get_env_value(var_name, env);
    free(var_name);
    if(!var_value)
        return (ft_strdup(""));
    temp = ft_strdup(var_value);
    return (temp);
}

static char	*expand_argument(char *arg, t_env_lst *env)
{
	char	*new_arg;
	char	*temp;
	char	*dollar_part;

	new_arg = ft_strdup("");
	while (*arg)
	{
		if (*arg == '$')
		{
			dollar_part = handle_dollar(&arg, env);
			temp = ft_strjoin(new_arg, dollar_part);
			free(new_arg);
			free(dollar_part);
			new_arg = temp;
		}
		else
		{
			temp = ft_strjoin(new_arg, (char[]){*arg, 0});
			free(new_arg);
			new_arg = temp;
			arg++;
		}
	}
	return (new_arg);
}

void	expand_variables(t_cmd_node *cmd_node, t_env_lst *env)
{
	int		i;
	char	*original_arg;

	i = 0;
	if (!cmd_node->args)
		return ;
	while (cmd_node->args[i])
	{
		if (ft_strchr(cmd_node->args[i], '$'))
		{
			original_arg = cmd_node->args[i];
			cmd_node->args[i] = expand_argument(original_arg, env);
			free(original_arg);
		}
		i++;
	}
}

static char	*get_env_value(const char *var_name, t_env_lst *env)
{
	int	len;

	len = ft_strlen(var_name);
	while (env)
	{
		if (ft_strncmp(env->value, var_name, len) == 0)
		{
			if (env->value[len] == '=')
				return (env->value + len + 1);
		}
		env = env->next;
	}
	return (NULL);
}