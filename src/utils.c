/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:22:35 by dklepenk          #+#    #+#             */
/*   Updated: 2025/11/03 18:58:14 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_lst_size(t_env_lst *head)
{
	int	size;

	size = 0;
	while (head)
	{
		if (head->value)
			size++;
		head = head->next;
	}
	return (size);
}

void	free_string_array(char **arr)
{
	int	i;

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

bool	has_slash(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (true);
		i++;
	}
	return (false);
}

void	sort_env_list(t_env_lst *env)
{
	t_env_lst	*cur;
	char		*tmp_key;
	char		*tmp_val;

	if (!env)
		return;
	cur = env;
	while (cur->next)
	{
		if (ft_strcmp(cur->key, cur->next->key) > 0)
		{
			tmp_key = cur->key;
			tmp_val = cur->value;
			cur->key = cur->next->key;
			cur->value = cur->next->value;
			cur->next->key = tmp_key;
			cur->next->value = tmp_val;
			cur = env;
			continue;
		}
		cur = cur->next;
	}
}
