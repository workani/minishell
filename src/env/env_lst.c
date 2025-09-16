/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:59:39 by dklepenk          #+#    #+#             */
/*   Updated: 2025/09/16 20:02:49 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_env_lst_size(t_env_lst *head)
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

char **env_lst_to_arr(t_env_lst *head)
{
	int i;
	int len;
	char **env;

	i = 0;
	len = get_env_lst_size(head);
	env = malloc(len + 1);
	while (i < len && head)
	{
		env[i] = head->value;
		head = head->next;
		i++;
	}
	return (env);
}

void print_env_lst(t_env_lst *head)
{
	while (head)
	{
		printf("value: %s\n", head->value);
		head = head->next;
	}
}

static void add_node(t_env_lst **head, char *value)
{
	t_env_lst *node;

	node = malloc(sizeof(t_env_lst));
	if (!node)
		return;
	node->value = value;
	node->next = *head;
	*head = node;
}

void init_env_lst(t_env_lst **head, char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		add_node(head, env[i]);
		i++;
	}
}