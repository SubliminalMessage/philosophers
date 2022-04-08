#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h> /* <?? */
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

// Util Functions
int		ft_atoi(const char *str);
char	**ft_split(const char *s, char c);
int		ft_isdigit(int c);
char	*ft_substr(const char *s, unsigned int start, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	ft_strlen(const char *s);

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