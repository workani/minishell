/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: workani <workani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:22:35 by dklepenk          #+#    #+#             */
/*   Updated: 2025/11/05 00:56:18 by workani          ###   ########.fr       */
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
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (true);
		i++;
	}
	return (false);
}

static void	swap_env_nodes(t_env_lst *a, t_env_lst *b)
{
	char	*tmp_key;
	char	*tmp_val;
	bool	tmp_no_eq;

	tmp_key = a->key;
	tmp_val = a->value;
	tmp_no_eq = a->has_no_eq;
	a->key = b->key;
	a->value = b->value;
	a->has_no_eq = b->has_no_eq;
	b->key = tmp_key;
	b->value = tmp_val;
	b->has_no_eq = tmp_no_eq;
}

void	sort_env_list(t_env_lst *env)
{
	t_env_lst	*cur;

	if (!env)
		return ;
	cur = env;
	while (cur->next)
	{
		if (ft_strcmp(cur->key, cur->next->key) > 0)
		{
			swap_env_nodes(cur, cur->next);
			cur = env;
			continue ;
		}
		cur = cur->next;
	}
}
