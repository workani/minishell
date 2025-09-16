/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:44:30 by dklepenk          #+#    #+#             */
/*   Updated: 2025/09/16 13:13:35 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_append_str(char *dest, int *dest_idx, char *src)
{
	int	src_idx;

	src_idx = 0;
	while (src[src_idx])
	{
		dest[*dest_idx] = src[src_idx];
		src_idx++;
		*dest_idx += 1;
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		result_idx;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	result = malloc((ft_strlen(s1) + ft_strlen(s2)) + 2);
	result_idx = 0;
	if (result == NULL)
		return (NULL);
	ft_append_str(result, &result_idx, (char *)s1);
	ft_append_str(result, &result_idx, "/");
	ft_append_str(result, &result_idx, (char *)s2);
	result[result_idx] = 0;
	return (result);
}
