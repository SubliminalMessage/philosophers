#include <philo.h>

int philo_take_fork(t_philo **philo_ptr, int fork_index)
{
    long    timestamp;
    t_philo *philo;

    philo = *philo_ptr;

    if (fork_index == 0 && philo->forks[0] == philo->forks[1])
    {
        sleep_for(philo->time_die);
        philo_die(philo_ptr);
        return (1);
    }
    pthread_mutex_lock(philo->forks[fork_index]);
    pthread_mutex_lock(philo->print_mutex);
    if (is_anyone_dead(philo))
    {
        pthread_mutex_unlock(philo->print_mutex);
        pthread_mutex_unlock(philo->forks[fork_index]);
        return (1);
    }
    timestamp = get_time(philo->time_start);
    printf("\033[0;33m[\033[0;0m%ld\033[0;33m] ", timestamp);
    printf("Philosopher %d has taken a fork\033[0;0m\n", philo->index);
    pthread_mutex_unlock(philo->print_mutex);
    return (0);
}

int philo_eat(t_philo **philo_ptr)
{
    long    timestamp;
    t_philo *philo;

    philo = *philo_ptr;
    pthread_mutex_lock(philo->print_mutex);
    if (is_anyone_dead(philo))
    {
        pthread_mutex_unlock(philo->print_mutex);
        return (1);
    }
    timestamp = get_time(philo->time_start);
    printf("\033[0;32m[\033[0;0m%ld\033[0;32m] ", timestamp);
    printf("Philosopher %d is eating\033[0;0m\n", philo->index);
    philo->last_ate = get_time(0);
    philo->total_loops++;
    pthread_mutex_unlock(philo->print_mutex);
    sleep_for(philo->time_eat);
    pthread_mutex_unlock(philo->forks[0]);
    pthread_mutex_unlock(philo->forks[1]);
    return (0);
}

int philo_sleep(t_philo **philo_ptr)
{
    long    timestamp;
    t_philo *philo;

    philo = *philo_ptr;
    pthread_mutex_lock(philo->print_mutex);
    if (is_anyone_dead(philo))
    {
        pthread_mutex_unlock(philo->print_mutex);
        return (1);
    }
    timestamp = get_time(philo->time_start);
    printf("\033[0;35m[\033[0;0m%ld\033[0;35m] ", timestamp);
    printf("Philosopher %d is sleeping\033[0;0m\n", philo->index);
    pthread_mutex_unlock(philo->print_mutex);
    sleep_for(philo->time_eat);
    return (0);
}

int philo_think(t_philo **philo_ptr)
{
    long    timestamp;
    t_philo *philo;

    philo = *philo_ptr;
    if (is_anyone_dead(philo))
        return (1);
    pthread_mutex_lock(philo->print_mutex);
    if (is_anyone_dead(philo))
    {
        pthread_mutex_unlock(philo->print_mutex);
        return (1);
    }
    timestamp = get_time(philo->time_start);
    printf("\033[0;34m[\033[0;0m%ld\033[0;34m] ", timestamp);
    printf("Philosopher %d is thinking\033[0;0m\n", philo->index);
    pthread_mutex_unlock(philo->print_mutex);
    sleep_for(philo->time_eat);
    return (0);
}

void philo_die(t_philo **philo_ptr)
{
    long    timestamp;
    t_philo *philo;

    philo = *philo_ptr;
    //printf("Trying to lock print mutex\n");
    //pthread_mutex_lock(philo->print_mutex); // Already locked before calling this function
    //printf("Locked\n");
    if (*(*(philo->anyone_dead)) == 1)
        return ;
    *(*(philo->anyone_dead)) = 1;
    timestamp = get_time(philo->time_start);
    printf("\033[0;31m[\033[0;0m%ld\033[0;31m] ", timestamp);
    printf("Philosopher %d died\033[0;0m\n", philo->index);
    pthread_mutex_unlock(philo->print_mutex);
    //printf("Unlocked\n");
}