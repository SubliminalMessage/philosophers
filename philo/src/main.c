#include <philo.h>

void    clean_exit(char *msg)
{
	if (msg != NULL)
		printf("%s\n", msg);
	exit(0);
}

t_config    *parse_configuration(int argc, char **argv)
{
    t_config *config;

    config = malloc(sizeof(t_config));
    config->n_philo = ft_atoi(argv[1]);
    config->time_die = ft_atoi(argv[2]);
    config->time_eat = ft_atoi(argv[3]);
    config->time_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        config->total_loops = ft_atoi(argv[5]);
    else
        config->total_loops = -1;

    /* Print result */
    printf("Config file:\n");
    printf("Nº Philos:    \t%d\n", config->n_philo);
    printf("Time to die:  \t%dms\n", config->time_die);
    printf("Time to eat:  \t%dms\n", config->time_eat);
    printf("Time to sleep:\t%dms\n", config->time_sleep);
    printf("Total loops:  \t%d\n", config->total_loops);

    return (config);
}

/*
number_of_philosophers time_to_die
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
*/
int main(int argc, char **argv)
{
    t_config *config;
    // Parse Args
    if (argc != 5 && argc != 6)
        clean_exit("Not enough arguments or too many of them!\n");
    config = parse_configuration(argc, argv);
    // Execute Philos
    // Clean exit i guess

    (void) argv;
}
