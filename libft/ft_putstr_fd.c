/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:28:59 by dklepenk          #+#    #+#             */
/*   Updated: 2025/06/18 15:47:35 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_putstr_fd(char *s, int fd)
{
	int	count;

	count = 0;
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		count++;
		s++;
	}
	return (count);
}
// int main()
// {
//     ft_putstr_fd("kkkkkkodddding", 1);
// }