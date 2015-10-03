#include "ft_philo.h"

int 			g_chopstiks[NUMBERPHILO];
t_philo 		g_guest[NUMBERPHILO];
pthread_mutex_t g_printlock = PTHREAD_MUTEX_INITIALIZER;

void check_constant_errors(void)
{
    if (MAX_LIFE < 1 || EAT_T < 1 || THINK_T < 1 || TIMEOUT < 1)
    {
        ft_puterrdl("The constants variables must be greater than 0");
        exit(-1);
    }
}

int 	take_right(int current)
{
	return (((current + 1) % NUMBERPHILO));
}

int 	take_left(int current)
{
	return (((current - 1) % NUMBERPHILO) == -1 ? NUMBERPHILO - 1 : ((current - 1) % NUMBERPHILO));
}

void	*play(void* data)
{
	t_philo *p;
	int 	sides[3];

	p = (t_philo*)data;
	sides[0] = g_chopstiks[p->id];
	sides[1] = g_chopstiks[((p->id + 1) % NUMBERPHILO)];
	sides[2] = g_chopstiks[((p->id - 1) % NUMBERPHILO)];
	pthread_mutex_lock(&g_printlock);
	ft_printf("The philosophe number: %d, seat to table.\n", p->id);
	ft_printf("Philosophe %d have: %d, r: %d, l: %d\n", p->id, sides[0], sides[1], sides[2]);
	pthread_mutex_lock(&g_guest[((p->id + 1) % NUMBERPHILO)].lock);
	ft_printf("Philo: %d , The right philosopher is : %d, The left is %d \n", p->id, take_right(p->id), take_left(p->id));
	pthread_mutex_unlock(&g_guest[((p->id + 1) % NUMBERPHILO)].lock);
	pthread_mutex_unlock(&g_printlock);
	while (p->life > 0)
	{
		pthread_mutex_lock(&p->lock);
		p->life--;
		pthread_mutex_unlock(&p->lock);
	}
	return NULL;
}

void	init_philosophe(void *data)
{
	int i;
	t_philo *guest;

	i = 0;
	guest = (t_philo*)data;
	while (i < NUMBERPHILO)
	{
		pthread_mutex_init(&(guest[i].lock), NULL);
		guest[i].id = i;
		guest[i].history = "";
		g_chopstiks[i] = 1;
		guest[i].state = REST;
		guest[i].life = MAX_LIFE;
		pthread_create(&guest[i].thread, NULL, play, &guest[i]);
		i++;
	}
}

void	wait_everyone(void *data)
{
	int i;
	t_philo *guest;

	i = 0;
	guest = (t_philo*)data;
	while (i < NUMBERPHILO)
    {
      	pthread_join(guest[i].thread, NULL);
      	i++;
    }
}

int main()
{
	int i;

	i = 0;
    check_constant_errors();
    init_philosophe(&g_guest);
    wait_everyone(&g_guest);
    return 0; 
}