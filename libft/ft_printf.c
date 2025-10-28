/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:48:41 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/28 17:44:38 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_placeholder(char placeholder, va_list *args, int fd)
{
	int	count;

	count = 0;
	if (placeholder == 'c')
		count += ft_putchar_fd(va_arg(*args, int), fd);
	if (placeholder == 's')
		count += putstr(va_arg(*args, char *), fd);
	if (placeholder == 'p')
		count += putptr(va_arg(*args, void *), fd);
	if (placeholder == 'd' || placeholder == 'i')
		count += ft_putnbr_fd(va_arg(*args, int), fd);
	if (placeholder == 'u')
		count += putuint(va_arg(*args, unsigned int), fd);
	if (placeholder == 'x')
		count += puthex((unsigned int)va_arg(*args, int), false, fd);
	if (placeholder == 'X')
		count += puthex((unsigned int)va_arg(*args, int), true, fd);
	if (placeholder == '%')
		count += ft_putchar_fd(placeholder, fd);
	return (count);
}

int	ft_printf(const char *str, ...)
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
			count += print_placeholder(str[i + 1], &args, 1);
			i++;
		}
		else
			count += ft_putchar_fd(str[i], 1);
		i++;
	}
	return (count);
}
