/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:53:58 by dklepenk          #+#    #+#             */
/*   Updated: 2025/09/05 18:55:28 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	get_fraction_part(char *str, int i)
{
	double	divisor;
	double	result;

	divisor = 10.0;
	result = 0.0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result += (str[i] - '0') / divisor;
		divisor *= 10;
		i++;
	}
	return (result);
}

double	ft_atod(char *str)
{
	double	fraction_part;
	int		real_part;
	int		i;
	int		sign;

	sign = 1;
	real_part = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		real_part = (real_part * 10) + (str[i] - '0');
		i++;
	}
	fraction_part = get_fraction_part(str, i + 1);
	return ((real_part + fraction_part) * sign);
}
