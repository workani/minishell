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

char *combine_key_value(t_env_lst *node)
{
	int i;
	int len;
	char *result;

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

char **env_lst_to_arr(t_env_lst *head)
{
	int i;
	int len;
	char **envp;

	i = 0;
	len = get_env_lst_size(head);
	envp = malloc((len + 1) * sizeof(char *));
	while (i < len && head)
	{
		if (head->key)
		{
			envp[i] = combine_key_value(head);
			i++;
		}
		head = head->next;
	}
	envp[i] = NULL;
	return (envp);
}


void init_env_lst(t_env_lst **head, char **envp)
{
	int		i;
	int		del_idx;
	char	*key;
	char	*value;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		del_idx = ft_cst_strchr(envp[i], '=');
		key = ft_substr(envp[i], 0, del_idx);
		value = ft_substr(envp[i], del_idx + 1, ft_strlen(envp[i]) - del_idx - 1);
		add_env_node(head, key, value);
		i++;
	}
}
