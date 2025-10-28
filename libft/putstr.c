/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:46:49 by dklepenk          #+#    #+#             */
/*   Updated: 2025/10/28 17:45:09 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	putstr(char *str, int fd)
{
	if (!str)
		return (ft_putstr_fd("(null)", fd));
	return (ft_putstr_fd(str, fd));
}
