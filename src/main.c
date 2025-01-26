/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:53:27 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/26 19:53:28 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

void	log_state(t_philosopher *philosopher, const char *state)
{
	pthread_mutex_lock(&philosopher->mutex_print);
	printf("%lld %d %s\n", get_current_time(), philosopher->id + 1, state);
	pthread_mutex_unlock(&philosopher->mutex_print);
}

void	*thread_routine(void *data)
{
	t_philosopher	*philosopher;
	int				left_fork;
	int				right_fork;

	philosopher = (t_philosopher *)data;
	left_fork = philosopher->id;
	right_fork = (philosopher->id + 1) % philosopher->nb_philosophers;
	while (philosopher->nb_times_each_philosopher_has_eaten < philosopher->nb_times_each_philosopher_must_eat)
	{
		log_state(philosopher, "is thinking");
		if (philosopher->id % 2 == 0)
		{
			pthread_mutex_lock(&philosopher->forks[left_fork]);
			log_state(philosopher, "has taken a fork");
			pthread_mutex_lock(&philosopher->forks[right_fork]);
			log_state(philosopher, "has taken a fork");
		}
		else
		{
			pthread_mutex_lock(&philosopher->forks[right_fork]);
			log_state(philosopher, "has taken a fork");
			pthread_mutex_lock(&philosopher->forks[left_fork]);
			log_state(philosopher, "has taken a fork");
		}
		log_state(philosopher, "is eating");
		philosopher->last_meal = get_current_time();
		philosopher->nb_times_each_philosopher_has_eaten++;
		usleep(philosopher->time_to_eat * 1000);
		pthread_mutex_unlock(&philosopher->forks[left_fork]);
		pthread_mutex_unlock(&philosopher->forks[right_fork]);
		log_state(philosopher, "is sleeping");
		usleep(philosopher->time_to_sleep * 1000);
		if (get_current_time()
			- philosopher->last_meal > philosopher->time_to_die)
		{
			log_state(philosopher, "died");
			break ;
		}
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
		philosophers[i].time_to_die = ft_atoi(argv[2]);
		philosophers[i].time_to_eat = ft_atoi(argv[3]);
		philosophers[i].time_to_sleep = ft_atoi(argv[4]);
		philosophers[i].last_meal = get_current_time();
		philosophers[i].nb_times_each_philosopher_must_eat = argv[5] ? ft_atoi(argv[5]) :
			-1;
		philosophers[i].nb_times_each_philosopher_has_eaten = 0;
	}
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
