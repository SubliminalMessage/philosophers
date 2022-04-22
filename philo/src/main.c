#include <philo.h>

void    clean_exit(t_config *config)
{
	int i;

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
        free(config->threads);
        free(config->philos);
        free(config->forks);
        pthread_mutex_destroy(config->print_mutex);
        free(config->print_mutex);
        free(config->anyone_dead);
        free(config->anyone_mutex);
        free(config);
    }
}

void check_threads(t_config *config)
{
    t_philo *philo;
    int any_dead;
    int count;
    int i;

    any_dead = 0;
    count = 0;
    while (!any_dead && (config->total_loops == -1 || count < config->n_philo))
    {
        i = 0;
        count = 0;
        while (i < config->n_philo)
        {
            philo = config->philos[i];
            if (read_last_ate(&philo) == 0)
                continue ;
            long now = get_time(0);
            if (read_last_ate(&philo) + philo->time_die <= now)
            {
                any_dead = 1;
                set_anyone_dead(&philo, 1);
                philo_die(&philo);
                //printf("(%d died because %ld + %d <= %ld)\n", i+1, philo->last_ate, philo->time_die, now);
                break ;
            }
            if (read_total_loops(&philo) >= config->total_loops)
                count++;
            i++;
        }
    }
    set_anyone_dead(&config->philos[0], 1);
}

/*
void leaks(void)
{
    system("leaks -q philo");
}*/

int main(int argc, char **argv)
{
    t_config    *config;
    int         i;
    long        timestamp;

    config = NULL;
    if (argc != 5 && argc != 6)
        printf("Not enough arguments or too many of them!");
    else
    {
        config = parse_configuration(argc, argv);
        if (config != NULL)
        {
            i = -1;
            timestamp = get_time(0);
            while (++i < config->n_philo)
            {
                config->philos[i] = create_philo(config, i + 1);
                config->philos[i]->time_start = timestamp;
                pthread_create(&config->threads[i], NULL, run_philo, config->philos[i]);
            }
            check_threads(config);
            i = -1;
            while (++i < config->n_philo)
                pthread_join(config->threads[i], NULL);
            printf("Finished!\n");
        }
    }
    clean_exit(config);
    //system("leaks -q philo");
}
