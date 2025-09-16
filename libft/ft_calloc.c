/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:37:21 by dklepenk          #+#    #+#             */
/*   Updated: 2025/06/23 14:22:19 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	int				i;
	int				len;
	unsigned char	*result;

	i = 0;
	len = nmemb * size;
	result = malloc(len);
	if (len == 0 || result == NULL)
		return (result);
	while (i < len)
	{
		result[i] = 0;
		i++;
	}
	return (result);
}
