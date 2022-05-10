/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:12:44 by dangonza          #+#    #+#             */
/*   Updated: 2022/05/10 14:20:00 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	check_threads(t_config **config)
{
	int		aux;
	int		any_dead;
	int		count;
	int		i;

	any_dead = 0;
	count = 0;
	while (!any_dead && ((*config)->total_loops == -1
			|| count < (*config)->n_philo))
	{
		i = -1;
		count = 0;
		while (++i < (*config)->n_philo)
		{
			aux = check_single_thread(config, i, &any_dead);
			if (aux == 1)
				continue ;
			else if (aux == 2)
				break ;
			else if (aux == 3)
				count++;
		}
	}
	set_anyone_dead(&(*config)->philos[0], 1);
}

/*
	Returns 1 if it needs to execute 'continue'
	Returns 2 if it needs to execute 'break'
	Return 3 if it needs to execute 'count++'
	Returns 0 if it doesn't need to execute anything
*/
int	check_single_thread(t_config **config, int index, int *any_dead)
{
	t_philo	*philo;

	philo = (*config)->philos[index];
	if (read_last_ate(&philo) == 0)
		return (1);
	if (read_last_ate(&philo) + philo->time_die <= get_time(0))
	{
		*any_dead = 1;
		set_anyone_dead(&philo, 1);
		philo_die(&philo);
		return (2);
	}
	if (read_total_loops(&philo) >= (*config)->total_loops)
		return (3);
	return (0);
}
