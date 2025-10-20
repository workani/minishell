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
		if (head->value)
		{
			envp[i] = ft_strdup(head->value);
			i++;
		}
		head = head->next;
	}
	envp[i] = NULL;
	return (envp);
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

void init_env_lst(t_env_lst **head, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		add_node(head, envp[i]);
		i++;
	}
}