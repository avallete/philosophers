#include "ft_philo.h"

t_philo 		g_guest[NUMBERPHILO];
t_chop 			g_chop;
pthread_mutex_t g_termlock = PTHREAD_MUTEX_INITIALIZER;

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

int 	get_chopstick(int id)
{
	int i;

	i = g_chop.chopsticks[id];
	return (i);
}

int 	take_chopstick(int src, int dest)
{
	pthread_mutex_lock(&g_chop.choplock[src]);
	if (g_chop.chopsticks[src] > 0)
	{
		g_chop.chopsticks[src]--;
		g_chop.chopsticks[dest]++;
		pthread_mutex_lock(&g_termlock);
		ft_printf("\e[%dmThe Philosopher %d take chopstick\e[0m from \e[%dmPhilosophe %d\e[0m\n", g_guest[dest].color, dest, g_guest[src].color, src);
		pthread_mutex_unlock(&g_termlock);
		pthread_mutex_unlock(&g_chop.choplock[src]);
		return (1);
	}
	pthread_mutex_unlock(&g_chop.choplock[src]);
	return (0);
}

unsigned int 	get_life(int id)
{
	return (g_guest[id].life);
}

void	change_state(char newState, char *history, t_philo *p)
{
	char state[2];

	state[1] = 0;
	state[0] = newState;
	p->state = newState;
	ft_strcat(history, state);
}

void	resting(t_philo *p)
{
	int i;

	i = 0;
	pthread_mutex_unlock(&g_chop.choplock[p->id]);
	pthread_mutex_lock(&g_termlock);
	ft_printf("\e[%dmThe philosophe number: %d, begin to rest.\e[0m Time: %d\n", p->color, p->id, time(NULL));
	pthread_mutex_unlock(&g_termlock);
	change_state(REST, p->history, p);
	while (i < REST_T && p->life > 0)
	{
		p->life--;
		usleep(IN_SEC(1));
		i++;
	}
	pthread_mutex_lock(&g_termlock);
	ft_printf("\e[%dmThe philosophe number: %d, finish to rest.\e[0m Time: %d\n", p->color, p->id, time(NULL));
	pthread_mutex_unlock(&g_termlock);
}

void	eating(t_philo *p)
{	
	change_state(EAT, p->history, p);
	pthread_mutex_lock(&g_chop.choplock[p->id]);
	pthread_mutex_lock(&g_termlock);
	ft_printf("\e[%dmThe philosophe number: %d, begin to eat.\e[0m Time: %d\n", p->color, p->id, time(NULL));
	pthread_mutex_unlock(&g_termlock);
	usleep(IN_SEC(EAT_T));
	p->life = MAX_LIFE;
	pthread_mutex_lock(&g_termlock);
	ft_printf("\e[%dmThe philosophe number: %d, finished to eat.\e[0m Time: %d\n", p->color, p->id, time(NULL));
	pthread_mutex_unlock(&g_termlock);
	resting(p);
}

void	thinking(t_philo *p)
{
	int i;

	i = 0;
	change_state(THINK, p->history, p);
	pthread_mutex_lock(&g_termlock);
	ft_printf("\e[%dmThe philosophe number: %d, begin to think.\e[0m Time: %d\n", p->color, p->id, time(NULL));
	pthread_mutex_unlock(&g_termlock);
	while (i < THINK_T && p->life > 0)
	{
		p->life--;
		usleep(IN_SEC(1));
		i++;
	}
	pthread_mutex_lock(&g_termlock);
	ft_printf("\e[%dmThe philosophe number: %d, finish to think.\e[0m Time: %d\n", p->color, p->id, time(NULL));
	pthread_mutex_unlock(&g_termlock);
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

void	end_threads(void *data)
{
	int i;
	t_philo *guest;

	i = 0;
	guest = (t_philo*)data;
	while (i < NUMBERPHILO)
    {
      	pthread_detach(guest[i].thread);
      	i++;
    }
    ft_printf("Now, it is time... To DAAAAAAAANCE!!!\n");
}


void	*play(void* data)
{
	t_philo *p;

	p = (t_philo*)data;
	pthread_mutex_lock(&g_termlock);
	ft_printf("\e[%dmThe philosophe number: %d, seat to table.\e[0m Time: %d\n", p->color, p->id, time(NULL));
	pthread_mutex_unlock(&g_termlock);
	while (p->life > 0)
	{
		pthread_mutex_lock(&p->lock);
		if (p->state != EAT && get_chopstick(p->id) == 1 && get_chopstick(take_right(p->id) > 0))
				take_chopstick(take_right(p->id), p->id);
		if (p->state != EAT && get_chopstick(p->id) == 2)
			eating(p);
		else if (p->state != THINK && get_chopstick(p->id) == 1)
			thinking(p);
		else
			resting(p);
		pthread_mutex_unlock(&p->lock);
	}
	pthread_mutex_lock(&g_termlock);
	ft_printf("\e[%dmThe philosophe number: %d, is died in Red Weeding.\e[0m Time: %d\n", p->color, p->id, time(NULL));
	pthread_mutex_unlock(&g_termlock);
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
		pthread_mutex_init(&g_chop.choplock[i], NULL);
		g_chop.chopsticks[i] = 1;
		pthread_mutex_init(&(guest[i].lock), NULL);
		guest[i].id = i;
		ft_bzero(guest[i].history, TIMEOUT + 1024);
		guest[i].state = REST;
		guest[i].life = MAX_LIFE;
		guest[i].color = 30 + i;
		pthread_create(&guest[i].thread, NULL, play, &guest[i]);
		i++;
	}
}

void	print_history(void)
{
	int i;

	i = 0;
	while (i < NUMBERPHILO)
	{
		ft_printf("\e[%dmThe philosophe number: %d, history: %s\e[0m\n", g_guest[i].color, g_guest[i].id, g_guest[i].history);
		i++;
	}
}

int main()
{
	int i;

	i = 0;
    check_constant_errors();
    init_philosophe(&g_guest);
    usleep(IN_SEC(TIMEOUT));
    end_threads(&g_guest);
    wait_everyone(&g_guest);
    print_history();
    return 0; 
}