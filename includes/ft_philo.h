#ifndef FT_PHILO_H
#define FT_PHILO_H
#include <pthread.h>
#include "libft.h"
#include "ft_printf.h"
#define EAT 'E'
#define REST 'R'
#define THINK 'T'
#define MAX_LIFE 50
#define EAT_T 5
#define REST_T 5
#define THINK_T 5
#define TIMEOUT 50
#define NUMBERPHILO 7
#define IN_SEC(x) ((x * 1000000))

typedef	struct 		s_chop
{
	int				chopsticks[NUMBERPHILO];
	pthread_mutex_t	choplock[NUMBERPHILO];
}					t_chop;

typedef struct		s_philo
{
	int				id;
	int 			color;
	char 			history[TIMEOUT + 1024];
	char 			state;
	unsigned int	life;
	pthread_t		thread;
	pthread_mutex_t lock;
}					t_philo;

void				check_constant_errors(void);
#endif