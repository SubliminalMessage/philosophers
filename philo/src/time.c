/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:35:33 by dangonza          #+#    #+#             */
/*   Updated: 2022/04/19 15:40:52 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long get_time(long offset)
{
    struct timeval  current;
    
    gettimeofday(&current, NULL);
    return ((current.tv_sec * 1000 + current.tv_usec / 1000) - offset);
}

void	sleep_for(long ms)
{
	long	start;

	start = get_time(0);
	usleep(ms * 920);
	while (get_time(0) < start + ms)
		usleep(ms * 3);
}