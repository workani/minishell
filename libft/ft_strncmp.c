/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:17:30 by dklepenk          #+#    #+#             */
/*   Updated: 2025/06/23 14:20:31 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*uchar_s1;
	unsigned char	*uchar_s2;

	i = 0;
	uchar_s1 = (unsigned char *)s1;
	uchar_s2 = (unsigned char *)s2;
	while ((uchar_s1[i] || uchar_s2[i]) && i < n)
	{
		if (uchar_s1[i] != uchar_s2[i])
			return (uchar_s1[i] - uchar_s2[i]);
		i++;
	}
	return (0);
}

// int main()
// {
//     printf("result: %d\n", ft_strncmp("hello", "hello", 5));
//     printf("result: %d\n", ft_strncmp("zello", "horld", 5));
//     printf("result: %d\n", ft_strncmp("world", "worldddddddd", 20));
// }