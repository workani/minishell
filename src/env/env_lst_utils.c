/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: workani <workani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:34:02 by dklepenk          #+#    #+#             */
/*   Updated: 2025/11/05 16:09:46 by workani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_env_node(t_env_lst *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

void	free_env_lst(t_env_lst **head)
{
	t_env_lst	*tmp;
	t_env_lst	*cur;

	cur = *head;
	while (cur != NULL)
	{
		tmp = cur;
		cur = cur->next;
		free_env_node(tmp);
	}
	*head = NULL;
}

void	add_env_node(t_env_lst **head, char *key, char *value, bool has_no_eq)
{
	t_env_lst	*cur;
	t_env_lst	*node;

	node = malloc(sizeof(t_env_lst));
	if (!node)
		return ;
	if (key)
		node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	node->has_no_eq = has_no_eq;
	node->next = NULL;
	if (!(*head))
	{
		*head = node;
		return ;
	}
	cur = *head;
	while (cur->next != NULL)
	{
		cur = cur->next;
	}
	cur->next = node;
}

void	delete_env_node(t_env_lst **head, char *key)
{
	t_env_lst	*current;
	t_env_lst	*tmp;

	if (!(*head))
		return ;
	current = *head;
	if (current->key && ft_strcmp(key, current->key) == 0)
	{
		(*head) = (*head)->next;
		free_env_node(current);
		return ;
	}
	while (current->next != NULL)
	{
		if (current->next->key && ft_strcmp(key, current->next->key) == 0)
		{
			tmp = current->next;
			current->next = current->next->next;
			free_env_node(tmp);
			return ;
		}
		current = current->next;
	}
}

void	add_or_update_env(t_env_lst **head, char *key, char *value, bool has_no_eq)
{
	t_env_lst *cur;

	cur = *head;
	while (cur != NULL)
	{
		if (ft_strcmp(key, cur->key) == 0)
		{
			if (!has_no_eq)
			{
				if (cur->value)
					free(cur->value);
				cur->value = ft_strdup(value);
			}
			return ;
		}
		cur = cur->next;
	}
	add_env_node(head, key, value, has_no_eq);
}
