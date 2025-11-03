/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_str_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:01:10 by dklepenk          #+#    #+#             */
/*   Updated: 2025/11/03 17:03:38 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_char(t_buffer *buf, char c)
{
	if (buf->len + 1 >= buf->capacity)
	{
		buf->capacity *= 2;
		buf->data = realloc(buf->data, buf->capacity);
		if (!buf->data)
			exit(EXIT_FAILURE);
	}
	buf->data[buf->len++] = c;
	buf->data[buf->len] = '\0';
}

void	append_str(t_buffer *buf, const char *str)
{
	if (!str)
		return ;
	while (*str)
		append_char(buf, *str++);
}

int	get_var_len(char *str)
{
	int	len;

	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	return (len);
}
