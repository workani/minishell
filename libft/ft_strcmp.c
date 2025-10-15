/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:32:56 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/15 16:36:55 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*uchar_s1;
	unsigned char	*uchar_s2;

	i = 0;
	uchar_s1 = (unsigned char *)s1;
	uchar_s2 = (unsigned char *)s2;
	while (uchar_s1[i] && uchar_s2[i])
	{
		if (uchar_s1[i] != uchar_s2[i])
			return (uchar_s1[i] - uchar_s2[i]);
		i++;
	}
	return (uchar_s1[i] - uchar_s2[i]);
}
