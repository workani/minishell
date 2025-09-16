/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putuint.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:59:04 by dklepenk          #+#    #+#             */
/*   Updated: 2025/06/23 14:30:28 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	uitostr(char dst[], unsigned long u_src)
{
	int	i;

	i = 0;
	while (u_src > 0)
	{
		dst[i] = (u_src % 10) + '0';
		u_src /= 10;
		i++;
	}
	return (i);
}

int	putuint(unsigned long n)
{
	int		i;
	int		count;
	char	nbr_str[10];

	count = 0;
	if (n == 0)
		return (ft_putchar_fd('0', 1));
	i = uitostr(nbr_str, n);
	while (i--)
		count += ft_putchar_fd(nbr_str[i], 1);
	return (count);
}
