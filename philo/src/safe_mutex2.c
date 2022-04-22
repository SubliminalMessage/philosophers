/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mutex2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:40:30 by dangonza          #+#    #+#             */
/*   Updated: 2022/04/21 13:17:13 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long read_last_ate(t_philo **philo_ptr)
{
	t_philo *philo;
	long value;

	philo = *philo_ptr;
	//printf("Read about to lock\n");
	pthread_mutex_lock(philo->ate_mutex);
	//printf("Read locked\n");
	value = philo->last_ate;
	pthread_mutex_unlock(philo->ate_mutex);
	//printf("Read unlocked\n");
	return (value);
}

void set_last_ate(t_philo **philo_ptr, long value)
{
	t_philo *philo;

	philo = *philo_ptr;
	//printf("about to lock %p\n", philo->ate_mutex);
	pthread_mutex_lock(philo->ate_mutex);
	//printf("locked\n");
	philo->last_ate = value;
	pthread_mutex_unlock(philo->ate_mutex);
}