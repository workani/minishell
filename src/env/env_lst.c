/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:59:39 by dklepenk          #+#    #+#             */
/*   Updated: 2025/09/16 20:02:49 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*combine_key_value(t_env_lst *node)
{
	int		i;
	int		len;
	char	*result;

	if (!node->key)
		return (NULL);
	len = ft_strlen(node->key);
	if (node->value)
		len += ft_strlen(node->value) + 1;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	ft_append_str(result, &i, node->key);
	if (node->value)
	{
		ft_append_str(result, &i, "=");
		ft_append_str(result, &i, node->value);
	}
	result[i] = '\0';
	return (result);
}

char	**env_lst_to_arr(t_env_lst *head)
{
	int		i;
	int		len;
	char	**envp;

	i = 0;
	len = get_env_lst_size(head);
	envp = malloc((len + 1) * sizeof(char *));
	while (i < len && head)
	{
		if (head->key && head->value)
		{
			envp[i] = combine_key_value(head);
			i++;
		}
		head = head->next;
	}
	envp[i] = NULL;
	return (envp);
}

bool	convert_var_to_key_value_pair(char *dst[2], char *var)
{
	int	del_idx;

	del_idx = ft_cst_strchr(var, '=');
	if (del_idx == -1)
	{
		dst[0] = NULL;
		dst[1] = NULL;
		return (false);
	}
	dst[0] = ft_substr(var, 0, del_idx);
	dst[1] = ft_substr(var, del_idx + 1, ft_strlen(var) - del_idx - 1);
	return (true);
}

char	*get_env_value(const char *key, t_env_lst *head)
{
	while (head != NULL)
	{
		if (ft_strcmp(key, head->key) == 0)
			return (head->value);
		head = head->next;
	}
	return (NULL);
}

void	init_env_lst(t_env_lst **head, char **envp)
{
	int		i;
	char	*key_value[2];

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		convert_var_to_key_value_pair(key_value, envp[i]);
		add_env_node(head, key_value[0], key_value[1], false);
		free(key_value[0]);
		free(key_value[1]);
		i++;
	}
}
