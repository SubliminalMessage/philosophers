/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:14:22 by dangonza          #+#    #+#             */
/*   Updated: 2022/01/24 15:06:25 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	index;

	index = 0;
	if (!dst && !src)
		return (NULL);
	while (index < n)
	{
		*((unsigned char *)(dst + index)) = *((unsigned char *)(src + index));
		index++;
	}
	return (dst);
}
