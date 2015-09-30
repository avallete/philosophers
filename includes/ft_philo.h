#ifndef FT_PHILO_H
#define FT_PHILO_H
#include <pthread.h>
#include "libft.h"
#define EAT 1
#define REST 2
#define THINK 3
#define MAX_LIFE 500
#define EAT_T -1
#define REST_T 1
#define THINK_T 1
#define TIMEOUT 60
#define IN_SEC(x) ((x * 1000))

typedef struct		s_philo
{
	char			baguettes;
	char 			state;
	unsigned int	life;
	pthread_t		thread;
}					t_philo;

typedef struct		s_game
{
	t_philo			tab[7];
}					t_game;

void				check_constant_errors(void);
#endif