/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 22:33:25 by dklepenk          #+#    #+#             */
/*   Updated: 2025/06/18 15:28:09 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_itostr(char dst[], int src)
{
	int	i;

	i = 0;
	while (true)
	{
		dst[i] = src % 10 + '0';
		src /= 10;
		i++;
		if (src == 0)
			break ;
	}
	return (i);
}

int	ft_putnbr_fd(int n, int fd)
{
	int		i;
	int		count;
	char	nbr[10];

	count = 0;
	if (n == -2147483648)
	{
		count += ft_putchar_fd('-', fd);
		count += ft_putchar_fd('2', fd);
		n = 147483648;
	}
	if (n < 0)
	{
		count += ft_putchar_fd('-', fd);
		n = n * -1;
	}
	i = ft_itostr(nbr, n);
	while (i--)
		count += ft_putchar_fd(nbr[i], fd);
	return (count);
}

// int main()
// {
//     // ft_putnbr_fd(2147483647, 1);
//     // ft_putchar_fd('\n', 1);
//     // ft_putnbr_fd(1234, 1);
//     // ft_putchar_fd('\n', 1);
//     // ft_putnbr_fd(-1234, 1);
//     // ft_putnbr_fd(-1234, 1);
// }