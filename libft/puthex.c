/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puthex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 22:33:25 by dklepenk          #+#    #+#             */
/*   Updated: 2025/06/23 14:30:21 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	itohex(char dst[], uintptr_t u_src, bool is_upper)
{
	int		i;
	char	hex[17];

	i = 0;
	if (is_upper)
		ft_strlcpy(hex, "0123456789ABCDEF", 17);
	else
		ft_strlcpy(hex, "0123456789abcdef", 17);
	while (u_src > 0)
	{
		dst[i] = hex[u_src % 16];
		u_src /= 16;
		i++;
	}
	return (i);
}

int	puthex(uintptr_t n, bool is_upper)
{
	int		i;
	int		count;
	char	hex_nbr[32];

	count = 0;
	if (n == 0)
		return (ft_putchar_fd('0', 1));
	i = itohex(hex_nbr, n, is_upper);
	while (i--)
		count += ft_putchar_fd(hex_nbr[i], 1);
	return (count);
}
