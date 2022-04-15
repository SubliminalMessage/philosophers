#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h> /* <?? */
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stddef.h>

# define DIE_TYPE 1
# define TAKE_TYPE 2
# define EAT_TYPE 3
# define THINK_TYPE 4
# define SLEEP_TYPE 5


// Util Functions
int		ft_atoi(const char *str);
char	**ft_split(const char *s, char c);
int		ft_isdigit(int c);
char	*ft_substr(const char *s, unsigned int start, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	ft_strlen(const char *s);
int		ft_strdigit(char *s);

typedef pthread_mutex_t t_mutex;

typedef struct s_philo {
    int index;
    int time_die;
    int time_eat;
    int time_sleep;
    int current_loops;
    t_mutex *forks[2];
    t_mutex *print_mutex;
    long time_start;
    long last_ate;
    int     **anyone_dead;
} t_philo;

typedef struct s_config {
    int n_philo;
    int time_die;
    int time_eat;
    int time_sleep;
    int total_loops;
    pthread_t *threads; // free()
    t_philo **philos; // free()
    t_mutex *forks; // free() / destroy/()
    t_mutex *print_mutex; // free() / destroy()
    int     *anyone_dead;
} t_config;


// philos.c
void    *run_philo(void *arg);
t_philo *create_philo(t_config *cfg, int index);
void	sleep_for(long ms);
long get_time(long offset);
int is_anyone_dead(t_philo *philo);


// actions.c
int philo_take_fork(t_philo **philo_ptr, int fork_index);
int philo_eat(t_philo **philo_ptr);
int philo_sleep(t_philo **philo_ptr);
int philo_think(t_philo **philo_ptr);
void philo_die(t_philo **philo_ptr);

#endif