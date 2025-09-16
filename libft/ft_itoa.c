/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:12:50 by dklepenk          #+#    #+#             */
/*   Updated: 2025/06/23 14:22:10 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_int_len(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*result;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	i = 0;
	result = (char *)malloc(12 * sizeof(char));
	if (result == NULL)
		return (NULL);
	if (n < 0)
	{
		n = -n;
		result[0] = '-';
		i++;
	}
	i += ft_get_int_len(n);
	result[i] = '\0';
	while (i--)
	{
		if (result[i] != '-')
			result[i] = (n % 10) + '0';
		n /= 10;
	}
	return (result);
}
// int main()
// {
//     printf("res: %s\n", ft_itoa(1234));
//     // printf("res: %s\n", ft_itoa(1234423434));
//     // printf("res: %s\n", ft_itoa(-1234));
//     // printf("res: %s\n", ft_itoa(0));
//     // printf("res: %s\n", ft_itoa(-2147483648));
// }