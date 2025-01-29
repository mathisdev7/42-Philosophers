/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:12:06 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/29 01:27:45 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	task_done(t_simu *simu)
{
	int	i;
	int	done;
	int	time_ate;

	if (simu->must_eat == -1)
		return (0);
	i = -1;
	done = -1;
	while (++i < simu->nb_philo)
	{
		pthread_mutex_lock(&simu->mutex[M_MEAL]);
		time_ate = simu->philos[i].time_ate;
		pthread_mutex_unlock(&simu->mutex[M_MEAL]);
		if (time_ate >= simu->must_eat)
			if (++done == simu->nb_philo - 1)
				return (1);
		usleep(50);
	}
	return (0);
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
	{
		ft_print(philo, THINKING);
		philo_sleep(philo->simu->time_eat);
	}
	while (1)
	{
		if (philo_died(philo, 0))
			break ;
		if (philo_eating(philo))
			break ;
		ft_print(philo, THINKING);
		philo_sleep(philo->simu->time_thk);
	}
	return (NULL);
}

static int	philo_done(t_philo *philo, int n)
{
	pthread_mutex_lock(&philo->simu->mutex[M_DONE]);
	if (n)
		philo->simu->done = 1;
	if (philo->simu->done)
	{
		pthread_mutex_unlock(&philo->simu->mutex[M_DONE]);
		return (1);
	}
	pthread_mutex_unlock(&philo->simu->mutex[M_DONE]);
	return (0);
}

static void	routine_checker(t_philo *philo, t_simu *simu)
{
	int		i;
	time_t	last_meal;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&simu->mutex[M_MEAL]);
		last_meal = philo[i].last_meal;
		pthread_mutex_unlock(&simu->mutex[M_MEAL]);
		if (last_meal && task_done(simu))
		{
			philo_done(philo, 1);
			break ;
		}
		if (last_meal && get_time() - last_meal > simu->time_die)
		{
			philo_died(philo, 1);
			ft_print(&philo[i], DIED);
			break ;
		}
		i = (i + 1) % simu->nb_philo;
		usleep(200);
	}
	return ;
}

int	start_simulation(t_philo *philo, t_simu *simu)
{
	int			i;
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * (size_t)simu->nb_philo);
	if (threads == NULL)
		return (1);
	i = -1;
	while (++i < simu->nb_philo)
	{
		if (pthread_create(&threads[i], NULL, philo_routine, &philo[i]))
		{
			while (i--)
				pthread_join(threads[i], NULL);
			return (free(threads), 1);
		}
	}
	routine_checker(philo, simu);
	i = -1;
	while (++i < simu->nb_philo)
		if (pthread_join(threads[i], NULL))
			return (1);
	return (destroy_all_mutexes(philo, simu), free(threads), 0);
}
