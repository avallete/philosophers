#ifndef FT_PHILO_H
#define FT_PHILO_H
#include <pthread.h>
#include "libft.h"
#include "ft_printf.h"
#define EAT 1
#define REST 2
#define THINK 3
#define MAX_LIFE 10
#define EAT_T 1
#define REST_T 1
#define THINK_T 1
#define TIMEOUT 60
#define NUMBERPHILO 7
#define IN_SEC(x) ((x * 100000))

typedef struct		s_philo
{
	int				id;
	char 			*history;
	char 			state;
	unsigned int	life;
	pthread_t		thread;
	pthread_mutex_t lock;
}					t_philo;

void				check_constant_errors(void);
#endif