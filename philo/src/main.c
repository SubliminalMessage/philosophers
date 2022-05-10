/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:27:12 by dangonza          #+#    #+#             */
/*   Updated: 2022/05/10 14:19:08 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	clean_exit(t_config *config)
{
	int	i;

	i = 0;
	if (config != NULL)
	{
		while (i < config->n_philo)
		{
			pthread_mutex_destroy(config->philos[i]->anyone_mutex);
			pthread_mutex_destroy(config->philos[i]->loops_mutex);
			pthread_mutex_destroy(config->philos[i]->ate_mutex);
			free(config->philos[i]->ate_mutex);
			free(config->philos[i]->loops_mutex);
			free(config->philos[i]);
			pthread_mutex_destroy(&config->forks[i]);
			pthread_detach(config->threads[i]);
			i++;
		}
		free_stuff(config);
	}
}

void	free_stuff(t_config *config)
{
	free(config->threads);
	free(config->philos);
	free(config->forks);
	pthread_mutex_destroy(config->print_mutex);
	free(config->print_mutex);
	free(config->anyone_dead);
	free(config->anyone_mutex);
	free(config);
}

int	main(int argc, char **argv)
{
	t_config	*config;
	int			i;
	long		timestamp;

	config = NULL;
	if (argc != 5 && argc != 6)
		printf("Not enough arguments or too many of them!\n");
	else
	{
		config = parse_configuration(argc, argv);
		if (config != NULL)
		{
			i = -1;
			timestamp = get_time(0);
			while (++i < config->n_philo)
			{
				config->philos[i] = create_philo(config, i + 1, timestamp);
				pthread_create(&config->threads[i], NULL,
					run_philo, config->philos[i]);
			}
			check_threads(&config);
			wait_philos(&config);
		}
	}
	clean_exit(config);
}

void	wait_philos(t_config **config)
{
	int	i;

	i = -1;
	while (++i < (*config)->n_philo)
		pthread_join((*config)->threads[i], NULL);
}
