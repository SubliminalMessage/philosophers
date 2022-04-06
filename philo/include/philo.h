#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_config {
    int n_philo;
    int time_die;
    int time_eat;
    int time_sleep;
    int total_loops;
    int *forks; // Change to mutex
} t_config;

typedef struct s_philo {
    int index;
    int time_die;
    int time_eat;
    int time_sleep;
    int total_loops;
}   t_philo;

#endif