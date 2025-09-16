/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:34:16 by dklepenk          #+#    #+#             */
/*   Updated: 2025/06/18 15:20:55 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_putendl_fd(char *s, int fd)
{
	int	count;

	count = 0;
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		count++;
		s++;
	}
	count += ft_putchar_fd('\n', fd);
	return (count);
}
// int main()
// {
//     ft_putendl_fd("programming", 1);
// }