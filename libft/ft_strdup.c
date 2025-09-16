/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:49:22 by dklepenk          #+#    #+#             */
/*   Updated: 2025/06/23 14:21:04 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		s_len;
	char	*result;

	i = 0;
	s_len = ft_strlen(s);
	result = malloc(s_len + 1);
	if (result == NULL)
		return (NULL);
	while (i <= s_len)
	{
		result[i] = s[i];
		i++;
	}
	return (result);
}

// int main()
// {
//     char str[] = "Now I Am Become Death, the Destroyer of Worlds.";
//     printf("res: %s", ft_strdup(str));
// }