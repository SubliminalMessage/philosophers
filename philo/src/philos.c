/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:27:17 by dangonza          #+#    #+#             */
/*   Updated: 2022/05/03 18:41:19 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_philo	*create_philo(t_config *cfg, int index)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	philo->index = index;
	philo->time_die = cfg->time_die;
	philo->time_eat = cfg->time_eat;
	philo->time_sleep = cfg->time_sleep;
	philo->current_loops = 0;
	philo->forks[0] = &cfg->forks[index - 1];
	philo->forks[1] = &cfg->forks[index % cfg->n_philo];
	philo->print_mutex = cfg->print_mutex;
	philo->anyone_dead = &cfg->anyone_dead;
	philo->anyone_mutex = cfg->anyone_mutex;
	philo->loops_mutex = malloc(sizeof(t_mutex));
	pthread_mutex_init(philo->loops_mutex, NULL);
	philo->ate_mutex = malloc(sizeof(t_mutex));
	pthread_mutex_init(philo->ate_mutex, NULL);
	return (philo);
}

void	*run_philo(void *arg)
{
	t_philo	*philo;
	int		index;

	philo = (t_philo *) arg;
	index = philo->index;
	set_last_ate(&philo, get_time(0));
	if (index % 2 == 0)
		sleep_for(100);
	while (1)
	{
		if (philo_take_fork(&philo, 0))
			break ;
		if (philo_take_fork(&philo, 1))
		{
			pthread_mutex_unlock(philo->forks[0]);
			break ;
		}
		if (philo_eat(&philo) || philo_sleep(&philo) || philo_think(&philo))
			break ;
	}
	return (NULL);
}
