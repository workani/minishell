/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:15:08 by dklepenk          #+#    #+#             */
/*   Updated: 2025/06/13 16:00:38 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*uchar_s;

	i = 0;
	uchar_s = (unsigned char *)s;
	while (i < n)
	{
		if (uchar_s[i] == (unsigned char)c)
			return (uchar_s + i);
		i++;
	}
	return (NULL);
}

// int main()
// {
//     char *str = "hello";
//     char *str = "hello";
//     printf("result: %c\n", *(unsigned char*) ft_memchr(str, 'e', 5));
// }