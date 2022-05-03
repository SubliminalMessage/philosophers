/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mutex2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:40:30 by dangonza          #+#    #+#             */
/*   Updated: 2022/05/03 18:36:36 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long	read_last_ate(t_philo **philo_ptr)
{
	t_philo	*philo;
	long	value;

	philo = *philo_ptr;
	pthread_mutex_lock(philo->ate_mutex);
	value = philo->last_ate;
	pthread_mutex_unlock(philo->ate_mutex);
	return (value);
}

void	set_last_ate(t_philo **philo_ptr, long value)
{
	t_philo	*philo;

	philo = *philo_ptr;
	pthread_mutex_lock(philo->ate_mutex);
	philo->last_ate = value;
	pthread_mutex_unlock(philo->ate_mutex);
}
