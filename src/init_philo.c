/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 01:16:38 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/27 01:17:28 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	init_mutexes(pthread_mutex_t *forks, int nb_philosophers,
		t_simulation *simulation)
{
	int	i;

	pthread_mutex_init(&simulation->mutex, NULL);
	i = 0;
	while (i < nb_philosophers)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (1);
}

int	allocate_resources(int nb_philosophers, t_philosopher **philosophers,
		pthread_t **threads, pthread_mutex_t **forks)
{
	*philosophers = malloc(sizeof(t_philosopher) * nb_philosophers);
	*threads = malloc(sizeof(pthread_t) * nb_philosophers);
	*forks = malloc(sizeof(pthread_mutex_t) * nb_philosophers);
	if (!*philosophers || !*threads || !*forks)
	{
		free(*philosophers);
		free(*threads);
		free(*forks);
		return (ft_error("Memory allocation failed."));
	}
	return (1);
}

void	init_philosopher(t_philosopher *phil, char **argv, int i,
		t_simulation *simulation)
{
	phil->id = i;
	phil->nb_philosophers = ft_atoi(argv[1]);
	phil->forks = simulation->forks;
	pthread_mutex_init(&phil->mutex_print, NULL);
	phil->time_to_die = ft_atoi(argv[2]);
	phil->time_to_eat = ft_atoi(argv[3]);
	phil->time_to_sleep = ft_atoi(argv[4]);
	phil->last_meal = get_current_time();
	if (argv[5])
		phil->nb_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		phil->nb_times_each_philosopher_must_eat = -1;
	phil->nb_times_each_philosopher_has_eaten = 0;
	phil->simulation = simulation;
}

void	cleanup_resources(t_philosopher *philosophers, pthread_t *threads,
		pthread_mutex_t *forks, int nb_philosophers)
{
	int	i;

	i = 0;
	while (i < nb_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&philosophers[i].mutex_print);
		i++;
	}
	pthread_mutex_destroy(&philosophers[0].simulation->mutex);
	free(threads);
	free(forks);
	free(philosophers);
}

void	create_and_join_threads(t_thread_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philosophers)
	{
		init_philosopher(&info->philosophers[i], info->argv, i,
			info->simulation);
		i++;
	}
	i = 0;
	while (i < info->nb_philosophers)
	{
		pthread_create(&info->threads[i], NULL, thread_routine,
			&info->philosophers[i]);
		i++;
	}
	i = 0;
	while (i < info->nb_philosophers)
	{
		pthread_join(info->threads[i], NULL);
		i++;
	}
}
