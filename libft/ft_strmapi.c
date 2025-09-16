/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:09:38 by dklepenk          #+#    #+#             */
/*   Updated: 2025/06/23 14:20:51 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		s_len;
	char	*result;

	i = 0;
	s_len = ft_strlen(s);
	result = malloc(s_len + 1);
	if (result == NULL)
		return (NULL);
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

// char lower(unsigned int index, char c)
// {
//     if (c >= 'A' && c <= 'Z')
//         return (c + 32);
//     return (c);
// }

// int main()
// {
//     char src[] = "KODING";
//     char *str = ft_strmapi(src, lower);
//     printf("res: %s", str);
// }