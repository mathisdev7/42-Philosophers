/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 01:23:05 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/31 16:02:11 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	philo_sleep(time_t ms)
{
	time_t	start;
	time_t	elapsed;

	start = get_time();
	while (1)
	{
		elapsed = get_time() - start;
		if (elapsed >= ms)
			break ;
		usleep((ms - elapsed) * 1000);
	}
}

int	grab_fork(char s, int a, int b)
{
	if (s == 'M')
	{
		if (a > b)
			return (a);
		return (b);
	}
	else
	{
		if (a < b)
			return (a);
		return (b);
	}
}

void	philo_finish_eating(t_philo *p)
{
	pthread_mutex_unlock(&p->fork[grab_fork('M', p->f[0], p->f[1])]);
	pthread_mutex_unlock(&p->fork[grab_fork('m', p->f[0], p->f[1])]);
	ft_print(p, SLEEPING);
	philo_sleep(p->simu->time_slp);
}

int	philo_eating(t_philo *p)
{
	time_t	eat_start;

	pthread_mutex_lock(&p->fork[grab_fork('m', p->f[0], p->f[1])]);
	ft_print(p, FORK);
	if (p->f[0] == p->f[1])
	{
		pthread_mutex_unlock(&p->fork[grab_fork('m', p->f[0], p->f[1])]);
		return (1);
	}
	pthread_mutex_lock(&p->fork[grab_fork('M', p->f[0], p->f[1])]);
	ft_print(p, FORK);
	ft_print(p, EATING);
	pthread_mutex_lock(&p->simu->mutex[M_MEAL]);
	p->last_meal = get_time();
	p->time_ate++;
	pthread_mutex_unlock(&p->simu->mutex[M_MEAL]);
	eat_start = get_time();
	while (get_time() - eat_start < p->simu->time_eat)
	{
		if (philo_died(p, 0) || task_done(p->simu))
			return (philo_finish_eating(p), 1);
		usleep(1000);
	}
	return (philo_finish_eating(p), 0);
}
