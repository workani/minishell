/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:34:02 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/21 19:09:18 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_env_node(t_env_lst **head, char *key, char *value)
{
	t_env_lst *node;

	node = malloc(sizeof(t_env_lst));
	if (!node)
		return;
	node->key = key;
	node->value = value;
	node->next = *head;
	*head = node;
}

void delete_env_node(t_env_lst **head, t_env_lst *target)
{
	if (!head)
		return;
	if ((*head) == target)
	{
		//free(*head);
		*head = NULL;
	}
	if ((*head)->next == target)
	{
		(*head)->next = target->next;
		//free(target);
		return ;	
	}
}

int get_env_lst_size(t_env_lst *head)
{
	int size;

	size = 0;
	while (head)
	{
		if (head->value)
			size++;
		head = head->next;
	}
	return (size);
}

void print_env_lst(t_env_lst *head)
{
	while (head)
	{
		printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
}