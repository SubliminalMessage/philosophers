#include <philo.h>

void    clean_exit(char *msg)
{
	if (msg != NULL)
		printf("%s\n", msg);
	exit(0);
}

/*
number_of_philosophers time_to_die
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
*/
int main(int argc, char **argv)
{
    // Parse Args
    if (argc != 5 && argc != 6)
        clean_exit("Not enough arguments or too many of them!\n");

    // Execute Philos
    // Clean exit i guess

    (void) argv;
}
