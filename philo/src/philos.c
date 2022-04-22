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

    philo->anyone_mutex = cfg->anyone_mutex;
    philo->loops_mutex = malloc(sizeof(t_mutex));
    //printf("Philo loop_mutex: %p\n", philo->loops_mutex);
    pthread_mutex_init(philo->loops_mutex, NULL);
    philo->ate_mutex = malloc(sizeof(t_mutex));
    //printf("Philo ate_mutex: %p\n", philo->ate_mutex);

    pthread_mutex_init(philo->ate_mutex, NULL);

    return(philo);
}

void    *run_philo(void *arg)
{
    t_philo *philo;
    int index;
    
    philo = (t_philo *) arg;
    index = philo->index;
    //philo->last_ate = get_time(0);
    set_last_ate(&philo, get_time(0));
    while(1)
    {
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