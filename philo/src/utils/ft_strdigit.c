/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:35:33 by dangonza          #+#    #+#             */
/*   Updated: 2022/05/03 18:35:45 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ft_strdigit(char *s)
{
	int	i;

	i = 0;
	while (*(s + i))
	{
		if (!ft_isdigit(*(s + i)))
			return (0);
		i++;
	}
	return (1);
}
