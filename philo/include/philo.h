#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h> /* <?? */
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stddef.h>

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
    int total_loops;
    int current_loops;
    int fork_index; // 0 or 1, to then % 2 for sync-ing
    t_mutex *forks[2];
    t_mutex **print_mutex;
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
} t_config;

#endif