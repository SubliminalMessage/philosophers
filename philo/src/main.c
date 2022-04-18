#include <philo.h>

void    clean_exit(char *msg, t_config *config)
{
	if (msg != NULL)
		printf("%s\n", msg);
	exit(0);

    (void) config;
}

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
                //printf("(%d died because %ld + %d <= %ld)\n", i+1, philo->last_ate, philo->time_die, now);
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
