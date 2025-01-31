/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:03:00 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/31 16:04:44 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	init_philo(t_philo **philo, t_simu *simu)
{
	pthread_mutex_t	*fork;
	int				i;

	if (init_forks(&fork, simu->nb_philo))
		return (1);
	i = -1;
	while (++i < simu->nb_philo)
	{
		(*philo)[i].id = i;
		(*philo)[i].last_meal = simu->time_start;
		(*philo)[i].time_ate = 0;
		if (i % 2 == 0)
		{
			(*philo)[i].f[0] = i;
			(*philo)[i].f[1] = (i + 1) % simu->nb_philo;
		}
		else
		{
			(*philo)[i].f[0] = (i + 1) % simu->nb_philo;
			(*philo)[i].f[1] = i;
		}
		(*philo)[i].fork = fork;
		(*philo)[i].simu = simu;
	}
	return (0);
}

static int	init_simulation_mutexes(t_simu **simu)
{
	int	i;

	(*simu)->mutex = malloc(sizeof(pthread_mutex_t) * ((size_t)M_NUM));
	if ((*simu)->mutex == NULL)
		return (1);
	i = 0;
	while (i < M_NUM)
		pthread_mutex_init(&(*simu)->mutex[i++], NULL);
	return (0);
}

static int	init_simulation_state(t_simu **simu)
{
	long	remaining;

	(*simu)->time_start = get_time();
	(*simu)->time_thk = 0;
	if ((*simu)->nb_philo % 2 == 1)
	{
		(*simu)->time_thk = (*simu)->time_eat;
	}
	else
	{
		remaining = (*simu)->time_die - (*simu)->time_eat - (*simu)->time_slp
			- 5;
		if (remaining > 10)
			(*simu)->time_thk = (remaining - 10) / 2;
		else if (remaining > 0)
			(*simu)->time_thk = 2;
		else
			(*simu)->time_thk = 0;
	}
	(*simu)->done = 0;
	(*simu)->died = 0;
	return (0);
}

static int	init_simulation(t_simu **simu, int ac, char **av)
{
	(*simu)->nb_philo = ft_atoi(av[1]);
	(*simu)->time_die = ft_atoi(av[2]);
	(*simu)->time_eat = ft_atoi(av[3]);
	(*simu)->time_slp = ft_atoi(av[4]);
	(*simu)->must_eat = -1;
	if (ac == 6)
		(*simu)->must_eat = ft_atoi(av[5]);
	if (init_simulation_state(simu))
		return (1);
	if (init_simulation_mutexes(simu))
		return (1);
	return (0);
}

int	init(t_philo **philo, t_simu **simu, int ac, char **av)
{
	*simu = (t_simu *)malloc(sizeof(t_simu));
	if (*simu == NULL)
		return (1);
	(*simu)->mutex = NULL;
	if (init_simulation(simu, ac, av) != 0)
		return (1);
	*philo = (t_philo *)malloc(sizeof(t_philo) * (size_t)(*simu)->nb_philo);
	if (*philo == NULL)
		return (1);
	(*philo)->fork = NULL;
	if (init_philo(philo, *simu) != 0)
		return (1);
	(*simu)->philos = *philo;
	return (0);
}
