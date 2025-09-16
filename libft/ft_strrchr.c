/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:08:05 by dklepenk          #+#    #+#             */
/*   Updated: 2025/06/13 16:02:11 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*occurrence;

	i = 0;
	c = c % 128;
	occurrence = NULL;
	while (s[i])
	{
		if (s[i] == c)
			occurrence = (char *)s + i;
		i++;
	}
	if (c == '\0')
		occurrence = (char *)s + i;
	return ((char *)occurrence);
}

// int main()
// {
//     char *str = "hello";
//     printf("result: %c\n", *ft_strchr(str, 'e'));
// }