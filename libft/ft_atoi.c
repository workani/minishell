/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:46:35 by dklepenk          #+#    #+#             */
/*   Updated: 2025/08/27 20:00:42 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (true);
	if (c == '\v' || c == '\r' || c == '\f')
		return (true);
	return (false);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = (sign * -1);
		i++;
	}
	while ((nptr[i] >= '0' && nptr[i] <= '9') && nptr[i])
	{
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

// int main()
// {
//     printf("res: %d\n", ft_atoi("        84343"));
//     printf("res: %d\n", ft_atoi("        -84343"));
//     printf("res: %d\n", ft_atoi("        +84343"));
//     printf("res: %d\n", ft_atoi("---84343"));
// }