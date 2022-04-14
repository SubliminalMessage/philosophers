#include <philo.h>

void    clean_exit(char *msg, t_config *config)
{
	if (msg != NULL)
		printf("%s\n", msg);
	exit(0);

    (void) config;
}

t_config    *parse_configuration(int argc, char **argv)
{
    t_config *cfg;
    int i;

    if (!ft_strdigit(argv[1]) || !ft_strdigit(argv[2]) 
    || !ft_strdigit(argv[3]) || !ft_strdigit(argv[4]))
        clean_exit("Arguments can only be numbers", NULL);
    cfg = malloc(sizeof(t_config));
    cfg->n_philo = ft_atoi(argv[1]);
    cfg->time_die = ft_atoi(argv[2]);
    cfg->time_eat = ft_atoi(argv[3]);
    cfg->time_sleep = ft_atoi(argv[4]);
    if (argc == 6)
    {
        if (!ft_strdigit(argv[5]))
            clean_exit("Arguments can only be numbers", cfg);
        cfg->total_loops = ft_atoi(argv[5]);
    }
    else
        cfg->total_loops = -1;
    if (cfg->n_philo <= 0)
        clean_exit("There should be at least 1 Philosopher", cfg);

    cfg->threads = malloc(sizeof(pthread_t) * cfg->n_philo);
    cfg->philos = malloc(sizeof(t_philo *) * cfg->n_philo);
    cfg->forks = malloc(sizeof(t_mutex) * cfg->n_philo);

    if (cfg->threads == NULL || cfg->philos == NULL || cfg->forks == NULL)
        clean_exit("Malloc failed :(", cfg);

    i = 0;
    while (i < cfg->n_philo)
    {
        pthread_mutex_init(&cfg->forks[i], NULL);
        i++;
    }

    /* Print result */
    printf("Config args:\n");
    printf("Nº Philos:    \t%d\n", cfg->n_philo);
    printf("Time to die:  \t%dms\n", cfg->time_die);
    printf("Time to eat:  \t%dms\n", cfg->time_eat);
    printf("Time to sleep:\t%dms\n", cfg->time_sleep);
    printf("Total loops:  \t%d\n", cfg->total_loops);

    return (cfg);
}

void    *run_philo(void *arg)
{
    t_philo *philo = (t_philo *) arg;
    
    printf("Nº %d running\n", philo->index);

    while(1)
    {
        printf("Nº %d trying to grab [0]\n", philo->index);
        pthread_mutex_lock(philo->forks[0]);
        printf("Nº %d -> Locked [0]!\n", philo->index);
        printf("Nº %d trying to grab [1]\n", philo->index);
        pthread_mutex_lock(philo->forks[1]);
        printf("Nº %d -> Locked [1]!\n", philo->index);
        printf("Nº %d -> Waiting 1000ms...\n", philo->index);
        usleep(100);
        printf("Nº %d -> Dropping both forks...\n", philo->index);
        pthread_mutex_unlock(philo->forks[0]);
        pthread_mutex_unlock(philo->forks[1]);

        printf("Nº %d -> Dropped!! Restarting in 1000ms\n", philo->index);
        usleep(100);
    }

    return (NULL);
}

/*
number_of_philosophers time_to_die
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
*/

t_philo *create_philo(t_config *cfg, int index)
{
    t_philo *philo;

    philo = malloc(sizeof(t_philo));
    philo->index = index;
    philo->time_die = cfg->time_die;
    philo->time_eat = cfg->time_eat;
    philo->time_sleep = cfg->time_sleep;
    philo->total_loops = cfg->total_loops;
    philo->current_loops = 0;
    philo->fork_index = 0; // <??
    philo->forks[1] = &cfg->forks[index - 1];
    if (index == 1)
        philo->forks[0] = &cfg->forks[cfg->n_philo - 1];
    else
        philo->forks[0] = &cfg->forks[index % cfg->n_philo];

    return(philo);
}

int main(int argc, char **argv)
{
    t_config    *config;
    int         i;

    if (argc != 5 && argc != 6)
        clean_exit("Not enough arguments or too many of them!", NULL);
    config = parse_configuration(argc, argv);

    i = 0;
    while (i < config->n_philo)
    {
        config->philos[i] = create_philo(config, i + 1);
        pthread_create(&config->threads[i], NULL, run_philo, config->philos[i]);
        i++;
    }
    
    i = 0;
    while (i < config->n_philo)
    {
        pthread_join(config->threads[i], NULL);
        i++;
    }
    printf("Finished!\n");
}
