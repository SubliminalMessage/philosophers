/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:20:25 by dangonza          #+#    #+#             */
/*   Updated: 2022/04/19 17:39:19 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int read_anyone_dead(t_philo **philo_ptr)
{
	t_philo *philo;
	int value;

	philo = *philo_ptr;
	pthread_mutex_lock(philo->anyone_mutex);
	value = **philo->anyone_dead;
	pthread_mutex_unlock(philo->anyone_mutex);
	return (value);
}

void set_anyone_dead(t_philo **philo_ptr, int value)
{
	t_philo *philo;

	philo = *philo_ptr;
	pthread_mutex_lock(philo->anyone_mutex);
	**philo->anyone_dead = value;
	pthread_mutex_unlock(philo->anyone_mutex);
}

int read_total_loops(t_philo **philo_ptr)
{
	t_philo *philo;
	int value;

	philo = *philo_ptr;
	pthread_mutex_lock(philo->loops_mutex);
	value = philo->current_loops;
	pthread_mutex_unlock(philo->loops_mutex);
	return (value);
}

void add_total_loops(t_philo **philo_ptr)
{
	t_philo *philo;

	philo = *philo_ptr;
	pthread_mutex_lock(philo->loops_mutex);
	philo->current_loops++;
	pthread_mutex_unlock(philo->loops_mutex);
}