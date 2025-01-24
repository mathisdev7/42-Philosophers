/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:23:19 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/24 21:12:37 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*thread_routine_thinker(void *data)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)data;
	while (philosopher->nb_times_each_philosopher_has_eaten < philosopher->nb_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&philosopher->mutex_print);
		printf("Philosopher [%d]: is thinking.\n", philosopher->id);
		pthread_mutex_unlock(&philosopher->mutex_print);
		usleep(100000);
	}
	return (NULL);
}

void	*thread_routine_eater(void *data)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)data;
	while (philosopher->nb_times_each_philosopher_has_eaten < philosopher->nb_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&philosopher->mutex_print);
		printf("Philosopher [%d]: is eating.\n", philosopher->id);
		pthread_mutex_unlock(&philosopher->mutex_print);
		usleep(200000);
		pthread_mutex_lock(&philosopher->mutex_print);
		philosopher->nb_times_each_philosopher_has_eaten++;
		pthread_mutex_unlock(&philosopher->mutex_print);
	}
	return (NULL);
}

void	*thread_routine_sleeper(void *data)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)data;
	while (philosopher->nb_times_each_philosopher_has_eaten < philosopher->nb_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&philosopher->mutex_print);
		printf("Philosopher [%d]: is sleeping.\n", philosopher->id);
		pthread_mutex_unlock(&philosopher->mutex_print);
		usleep(150000);
	}
	return (NULL);
}

int	init_philosophers(char **argv)
{
	int				nb_philosophers;
	t_philosopher	*philosophers;
	pthread_t		*threads;
	int				i;

	nb_philosophers = ft_atoi(argv[1]);
	if (nb_philosophers <= 0)
		return (ft_error("Invalid number of philosophers."));
	printf("nb_philosophers: %d\n", nb_philosophers);
	philosophers = malloc(sizeof(t_philosopher) * nb_philosophers);
	threads = malloc(sizeof(pthread_t) * nb_philosophers);
	if (!philosophers || !threads)
		return (ft_error("Memory allocation failed."));
	for (i = 0; i < nb_philosophers; i++)
	{
		philosophers[i].id = i;
		philosophers[i].left = (i + nb_philosophers - 1) % nb_philosophers;
		philosophers[i].right = (i + 1) % nb_philosophers;
		philosophers[i].mutex_print = (pthread_mutex_t){0};
		philosophers[i].mutex_fork = (pthread_mutex_t){0};
		philosophers[i].mutex_eat = (pthread_mutex_t){0};
		philosophers[i].mutex_sleep = (pthread_mutex_t){0};
		philosophers[i].mutex_think = (pthread_mutex_t){0};
		philosophers[i].mutex_die = (pthread_mutex_t){0};
		printf("philosophers[%d].id: %d\n", i, philosophers[i].id);
		printf("philosophers[%d].left: %d\n", i, philosophers[i].left);
		printf("philosophers[%d].right: %d\n-----\n", i, philosophers[i].right);
		pthread_mutex_init(&philosophers[i].mutex_print, NULL);
		pthread_mutex_init(&philosophers[i].mutex_fork, NULL);
		pthread_mutex_init(&philosophers[i].mutex_eat, NULL);
		pthread_mutex_init(&philosophers[i].mutex_sleep, NULL);
		pthread_mutex_init(&philosophers[i].mutex_think, NULL);
		pthread_mutex_init(&philosophers[i].mutex_die, NULL);
		philosophers[i].nb_times_each_philosopher_must_eat = ft_atoi(argv[4]);
		philosophers[i].nb_times_each_philosopher_has_eaten = 0;
	}
	printf("Philosophers initialized successfully.\n");
	for (i = 0; i < nb_philosophers; i++)
	{
		pthread_create(&threads[i], NULL, thread_routine_eater,
			&philosophers[i]);
		pthread_create(&threads[i], NULL, thread_routine_thinker,
			&philosophers[i]);
		pthread_create(&threads[i], NULL, thread_routine_sleeper,
			&philosophers[i]);
	}
	for (i = 0; i < nb_philosophers; i++)
	{
		pthread_join(threads[i], NULL);
	}
	free(threads);
	free(philosophers);
	return (1);
}

int	main(int argc, char **argv)
{
	pthread_t	tid1;
	pthread_t	tid2;

	if (argc != 5 && argc != 6)
		return (ft_error("You need to send at least 4 arguments."));
	parse_args(argv);
	init_philosophers(argv);
}
