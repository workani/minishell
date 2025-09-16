/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 23:01:00 by dklepenk          #+#    #+#             */
/*   Updated: 2025/06/23 14:20:25 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_contains(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (true);
		i++;
	}
	return (false);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	start_idx;
	int	end_idx;

	i = 0;
	start_idx = 0;
	end_idx = 0;
	while (ft_contains(set, s1[i]))
		i++;
	start_idx = i;
	while (s1[i])
	{
		if (!ft_contains(set, s1[i]))
			end_idx = i + 1;
		i++;
	}
	return (ft_substr(s1, start_idx, end_idx - start_idx));
}
// int main()
// {
//     char *str = ft_strtrim("", "cdef");
//     printf("%s", str);
// }