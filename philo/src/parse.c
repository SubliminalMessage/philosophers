/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:26:29 by dangonza          #+#    #+#             */
/*   Updated: 2022/05/03 18:33:00 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_config	*parse_error(char *str, t_config *config)
{
	printf("%s\n", str);
	return (config);
}

t_config	*parse_configuration(int argc, char **argv)
{
	t_config	*cfg;
	int			i;

	if (!ft_strdigit(argv[1]) || !ft_strdigit(argv[2]) 
		|| !ft_strdigit(argv[3]) || !ft_strdigit(argv[4]))
			return (parse_error("Arguments can only be numbers", NULL));
	cfg = malloc(sizeof(t_config));
	i = parse_args(argc, argv, &cfg);
	if (i == -1)
	{
		free(cfg);
		return (NULL);
	}
	cfg->threads = malloc(sizeof(pthread_t) * cfg->n_philo);
	cfg->philos = malloc(sizeof(t_philo *) * cfg->n_philo);
	cfg->forks = malloc(sizeof(t_mutex) * cfg->n_philo);
	if (cfg->threads == NULL || cfg->philos == NULL || cfg->forks == NULL)
		return (parse_error("Malloc failed :(", cfg));
	i = -1;
	while (++i < cfg->n_philo)
		pthread_mutex_init(&cfg->forks[i], NULL);
	cfg->print_mutex = malloc(sizeof(t_mutex));
	pthread_mutex_init(cfg->print_mutex, NULL);
	cfg->anyone_dead = malloc(sizeof(int)); 
	*cfg->anyone_dead = 0;
	cfg->anyone_mutex = malloc(sizeof(t_mutex));
	pthread_mutex_init(cfg->anyone_mutex, NULL);
	return (cfg);
}

int parse_args(int argc, char **argv, t_config **config)
{
	t_config	*cfg;

	cfg = *config;
	cfg->n_philo = ft_atoi(argv[1]);
	cfg->time_die = ft_atoi(argv[2]);
	cfg->time_eat = ft_atoi(argv[3]);
	cfg->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		if (!ft_strdigit(argv[5]))
		{
			printf("Arguments can only be numbers\n");
			return (-1);
		}
		cfg->total_loops = ft_atoi(argv[5]);
	}
	else
		cfg->total_loops = -1;
	if (cfg->n_philo <= 0)
	{
		printf("There should be at least 1 Philosopher\n");
		return (-1);
	}
	return (0);
}