/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklepenk <dklepenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:55:31 by dklepenk          #+#    #+#             */
/*   Updated: 2025/06/23 14:30:06 by dklepenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	putptr(void *ptr)
{
	int			count;
	uintptr_t	u_ptr;

	if (!ptr)
		return (putstr("(nil)"));
	u_ptr = (uintptr_t)ptr;
	count = putstr("0x");
	count += puthex(u_ptr, false);
	return (count);
}
