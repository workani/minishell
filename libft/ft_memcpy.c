/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:50:23 by dklepenk          #+#    #+#             */
/*   Updated: 2025/06/13 16:00:48 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;

	tmp_dst = (unsigned char *)dst;
	tmp_src = (unsigned char *)src;
	while (n--)
		*tmp_dst++ = *tmp_src++;
	return (dst);
}

// int main()
// {
//     int n = 6;
//     int dst[n];
//     int src[] = {6, 2, 5, 5, 3, 1};

//     ft_memcpy(dst, src, 24);

//     for(int i = 0; i < n; i++)
//         printf("arr[%d]: %d\n",i + 1, dst[i]);
// }