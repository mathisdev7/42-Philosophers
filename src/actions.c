/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 01:23:05 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/29 01:24:57 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	philo_sleep(time_t ms)
{
	time_t	time;

	time = get_time();
	while (get_time() - time < ms)
		usleep(ms * 10);
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
	if (philo_died(p, 0) || task_done(p->simu))
		return (philo_finish_eating(p), 1);
	philo_sleep(p->simu->time_eat);
	return (philo_finish_eating(p), 0);
}
