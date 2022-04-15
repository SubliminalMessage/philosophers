#include <philo.h>

t_philo *create_philo(t_config *cfg, int index)
{
    t_philo *philo;

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

    return(philo);
}

long get_time(long offset)
{
    struct timeval  current;
    
    gettimeofday(&current, NULL);
    return ((current.tv_sec * 1000 + current.tv_usec / 1000) - offset);
}

void	sleep_for(long ms)
{
	long	start;

	start = get_time(0);
	while (get_time(start) < ms)
	;
}

void    *run_philo(void *arg)
{
    t_philo *philo;
    int index;
    
    philo = (t_philo *) arg;
    index = philo->index;
    //printf("Nº %d running\n", index);
    //philo->time_start = get_time(0);
    philo->last_ate = get_time(0);

    //printf("Start: %ld\n", philo->time_start);

    while(1)
    {
        /*if (is_anyone_dead(philo))
            break ;*/
        if (philo_take_fork(&philo, index % 2))
            break ;
        if (philo_take_fork(&philo, (index + 1) % 2))
        {
            pthread_mutex_unlock(philo->forks[index % 2]);
            break ;
        }
        if (philo_eat(&philo) ||
            philo_sleep(&philo) ||
            philo_think(&philo))
            break ;
    }

    return (NULL);
}