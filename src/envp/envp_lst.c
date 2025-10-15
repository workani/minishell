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

int get_envp_lst_size(t_envp_lst *head)
{
	int size;

	size = 0;
	while (head)
	{
		size++;
		head = head->next;
	}
	return (size);
}

char **envp_lst_to_arr(t_envp_lst *head)
{
	int i;
	int len;
	char **envp;

	i = 0;
	len = get_envp_lst_size(head);
	envp = malloc(len + 1);
	while (i < len && head)
	{
		envp[i] = head->value;
		head = head->next;
		i++;
	}
	return (envp);
}

void print_envp_lst(t_envp_lst *head)
{
	while (head)
	{
		printf("value: %s\n", head->value);
		head = head->next;
	}
}

static void add_node(t_envp_lst **head, char *value)
{
	t_envp_lst *node;

	node = malloc(sizeof(t_envp_lst));
	if (!node)
		return;
	node->value = value;
	node->next = *head;
	*head = node;
}

void init_envp_lst(t_envp_lst **head, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		add_node(head, envp[i]);
		i++;
	}
}