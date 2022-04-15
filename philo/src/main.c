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

    cfg->print_mutex = malloc(sizeof(t_mutex));
    pthread_mutex_init(cfg->print_mutex, NULL);

    cfg->anyone_dead = malloc(sizeof(int)); 
    *cfg->anyone_dead = 0;

    /* Print result */
    /*printf("Config args:\n");
    printf("Nº Philos:    \t%d\n", cfg->n_philo);
    printf("Time to die:  \t%dms\n", cfg->time_die);
    printf("Time to eat:  \t%dms\n", cfg->time_eat);
    printf("Time to sleep:\t%dms\n", cfg->time_sleep);
    printf("Total loops:  \t%d\n", cfg->total_loops);*/

    return (cfg);
}

/*
number_of_philosophers time_to_die
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
*/

void *check_threads(void *config_ptr)
{
    t_config *config;
    t_philo *philo;
    int any_dead;
    int count;
    int i;

    config = config_ptr;
    any_dead = 0;
    count = 0;
    while (!any_dead && (config->total_loops == -1 || count < config->n_philo))
    {
        i = 0;
        count = 0;
        while (i < config->n_philo)
        {
            philo = config->philos[i];
            if (philo->last_ate == 0)
                continue ;
            long now = get_time(0);
            if (philo->last_ate + philo->time_die <= now)
            {
                any_dead = 1;
                *(config->anyone_dead) = 1;
                philo_die(&philo);
                printf("(%d died because %ld + %d <= %ld)\n", i+1, philo->last_ate, philo->time_die, now);
                break ;
            }
            if (philo->current_loops >= config->total_loops)
                count++;
            i++;
        }
    }
    *(config->anyone_dead) = 1;
    return (NULL);
}

int main(int argc, char **argv)
{
    t_config    *config;
    int         i;

    if (argc != 5 && argc != 6)
        clean_exit("Not enough arguments or too many of them!", NULL);
    config = parse_configuration(argc, argv);

    i = 0;
    long timestamp = get_time(0);
    while (i < config->n_philo)
    {
        config->philos[i] = create_philo(config, i + 1);
        config->philos[i]->time_start = timestamp;
        pthread_create(&config->threads[i], NULL, run_philo, config->philos[i]);
        i++;
    }

    pthread_t *observer;
    observer = malloc(sizeof(pthread_t));
    pthread_create(observer, NULL, check_threads, config);
    
    i = 0;
    while (i < config->n_philo)
    {
        pthread_join(config->threads[i], NULL);
        i++;
    }
    printf("Finished!\n");
}
