/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:41:36 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/28 17:43:34 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_fd(int fd, const char *str, ...)
{
	int		i;
	int		count;
	va_list	args;

	i = 0;
	count = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			count += print_placeholder(str[i + 1], &args, fd);
			i++;
		}
		else
			count += ft_putchar_fd(str[i], fd);
		i++;
	}
	return (count);
}
