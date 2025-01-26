/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+      */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:23:19 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/24 21:12:37 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

void	*thread_routine(void *data)
{
	t_philosopher	*philosopher;
	int				left_fork;
	int				right_fork;

	philosopher = (t_philosopher *)data;
	left_fork = philosopher->id;
	right_fork = (philosopher->id + 1) % philosopher->nb_philosophers;
	printf("nb_times_each_philosopher_has_eaten: %d\n",
		philosopher->nb_times_each_philosopher_has_eaten);
	printf("nb_times_each_philosopher_must_eat: %d\n",
		philosopher->nb_times_each_philosopher_must_eat);
	while (philosopher->nb_times_each_philosopher_has_eaten < philosopher->nb_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&philosopher->mutex_print);
		printf("Philosopher [%d]: is thinking.\n", philosopher->id);
		pthread_mutex_unlock(&philosopher->mutex_print);
		usleep(2000);
		if (philosopher->id % 2 == 0)
		{
			pthread_mutex_lock(&philosopher->forks[left_fork]);
			pthread_mutex_lock(&philosopher->forks[right_fork]);
		}
		else
		{
			pthread_mutex_lock(&philosopher->forks[right_fork]);
			pthread_mutex_lock(&philosopher->forks[left_fork]);
		}
		pthread_mutex_lock(&philosopher->mutex_print);
		printf("Philosopher [%d]: is eating.\n", philosopher->id);
		pthread_mutex_unlock(&philosopher->mutex_print);
		philosopher->last_meal = get_current_time();
		usleep(2000);
		pthread_mutex_unlock(&philosopher->forks[left_fork]);
		pthread_mutex_unlock(&philosopher->forks[right_fork]);
		philosopher->nb_times_each_philosopher_has_eaten++;
		pthread_mutex_lock(&philosopher->mutex_print);
		printf("Philosopher [%d]: finished eating.\n", philosopher->id);
		pthread_mutex_unlock(&philosopher->mutex_print);
		pthread_mutex_lock(&philosopher->mutex_print);
		printf("Philosopher [%d]: is sleeping.\n", philosopher->id);
		pthread_mutex_unlock(&philosopher->mutex_print);
		usleep(1500);
	}
	return (NULL);
}

int	init_philosophers(char **argv)
{
	int				nb_philosophers;
	t_philosopher	*philosophers;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	int				i;

	nb_philosophers = ft_atoi(argv[1]);
	if (nb_philosophers <= 0)
		return (ft_error("Invalid number of philosophers."));
	printf("nb_philosophers: %d\n", nb_philosophers);
	philosophers = malloc(sizeof(t_philosopher) * nb_philosophers);
	threads = malloc(sizeof(pthread_t) * nb_philosophers);
	forks = malloc(sizeof(pthread_mutex_t) * nb_philosophers);
	if (!philosophers || !threads || !forks)
		return (ft_error("Memory allocation failed."));
	for (i = 0; i < nb_philosophers; i++)
		pthread_mutex_init(&forks[i], NULL);
	for (i = 0; i < nb_philosophers; i++)
	{
		philosophers[i].id = i;
		philosophers[i].nb_philosophers = nb_philosophers;
		philosophers[i].forks = forks;
		pthread_mutex_init(&philosophers[i].mutex_print, NULL);
		philosophers[i].nb_times_each_philosopher_must_eat = ft_atoi(argv[5]);
		philosophers[i].nb_times_each_philosopher_has_eaten = 0;
	}
	printf("Philosophers initialized successfully.\n");
	for (i = 0; i < nb_philosophers; i++)
		pthread_create(&threads[i], NULL, thread_routine, &philosophers[i]);
	for (i = 0; i < nb_philosophers; i++)
		pthread_join(threads[i], NULL);
	free(threads);
	free(forks);
	free(philosophers);
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (ft_error("You need to send at least 4 arguments."));
	parse_args(argv);
	init_philosophers(argv);
}
