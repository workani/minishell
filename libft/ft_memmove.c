/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:28:34 by dklepenk          #+#    #+#             */
/*   Updated: 2025/06/23 14:21:59 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int				i;
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;

	i = 0;
	tmp_dst = (unsigned char *)dst;
	tmp_src = (unsigned char *)src;
	if (src < dst)
	{
		while (len--)
			tmp_dst[len] = tmp_src[len];
	}
	else
	{
		while (len--)
		{
			tmp_dst[i] = tmp_src[i];
			i++;
		}
	}
	return (dst);
}
// int main()
// {
//     char str[100] = "Learningisfun";
//     char *first, *second;
//     first = str;
//     second = str;
//     printf("Original string :%s\n ", str);

//     // when overlap happens then it just ignore it
//     // memcpy(first + 8, first, 10);
//     // printf("memcpy overlap : %s\n ", str);

//     // when overlap it start from first position
//     memcpy(second + 8, first, 10);
//     printf("memmove overlap : %s\n ", str);

//     return (0);
// }
