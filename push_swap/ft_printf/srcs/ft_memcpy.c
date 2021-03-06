/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 13:18:10 by ffahey            #+#    #+#             */
/*   Updated: 2019/01/14 17:00:18 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (dst != src)
	{
		i = -1;
		while (++i < n)
			*((unsigned char*)dst + i) = *((unsigned char*)src + i);
	}
	return (dst);
}
