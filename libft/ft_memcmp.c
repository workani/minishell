/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:30:51 by dklepenk          #+#    #+#             */
/*   Updated: 2025/06/13 16:00:43 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*tmp_s1;
	unsigned char	*tmp_s2;

	i = 0;
	tmp_s1 = (unsigned char *)s1;
	tmp_s2 = (unsigned char *)s2;
	while (i < n)
	{
		if (tmp_s1[i] != tmp_s2[i])
			return (tmp_s1[i] - tmp_s2[i]);
		i++;
	}
	return (0);
}

// int main()
// {
//     int arr1[] =  {1, 2, 3};
//     int arr2[] =  {1, 2, 23};
//     printf("result: %d\n", ft_memcmp(arr1, arr2, 12));
//     printf("result: %d\n", ft_memcmp("zello", "horld", 5));
//     printf("result: %d\n", ft_memcmp("world", "worldddddddd", 20));
// }