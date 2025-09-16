/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:58:21 by dklepenk          #+#    #+#             */
/*   Updated: 2025/06/23 14:20:23 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*result;

	i = 0;
	s_len = ft_strlen(s);
	if (len > s_len)
		len = s_len;
	result = malloc(len + 1);
	if (start >= s_len)
		len = 0;
	while (i < len && s[start])
	{
		result[i] = s[start];
		i++;
		start++;
	}
	result[i] = '\0';
	return (result);
}

// int main()
// {
//     printf("res: %c", ft_substr("", 1, 1)[3]);
// }