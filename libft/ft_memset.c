/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:51:36 by dklepenk          #+#    #+#             */
/*   Updated: 2025/06/13 16:01:01 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	uc;
	unsigned char	*str;

	uc = (unsigned char)c;
	str = (unsigned char *)s;
	while (n--)
		*str++ = uc;
	return (s);
}

// int main()
// {
//     char str[] = "Hello world!";
//     printf("before: %s\n", str);

//     ft_memset(str, '$', 5);
//     printf("after: %s\n", str);
// }