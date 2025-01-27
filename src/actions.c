/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:38:00 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/27 01:14:20 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	take_forks(t_philosopher *philosopher)
{
	int	left_fork;
	int	right_fork;

	left_fork = philosopher->id;
	right_fork = (philosopher->id + 1) % philosopher->nb_philosophers;
	if (philosopher->id % 2 == 0)
	{
		pthread_mutex_lock(&philosopher->forks[left_fork]);
		log_state(philosopher, "has taken a fork");
		pthread_mutex_lock(&philosopher->forks[right_fork]);
	}
	else
	{
		pthread_mutex_lock(&philosopher->forks[right_fork]);
		log_state(philosopher, "has taken a fork");
		pthread_mutex_lock(&philosopher->forks[left_fork]);
	}
}

void	release_forks(t_philosopher *philosopher)
{
	int	left_fork;
	int	right_fork;

	left_fork = philosopher->id;
	right_fork = (philosopher->id + 1) % philosopher->nb_philosophers;
	pthread_mutex_unlock(&philosopher->forks[left_fork]);
	pthread_mutex_unlock(&philosopher->forks[right_fork]);
}

void	wait_action(t_philosopher *philosopher, long long duration)
{
	long long	start;
	int			is_sim_running;

	start = get_current_time();
	while (get_current_time() - start < duration)
	{
		pthread_mutex_lock(&philosopher->simulation->mutex);
		is_sim_running = philosopher->simulation->is_running;
		pthread_mutex_unlock(&philosopher->simulation->mutex);
		if (!is_sim_running)
			break ;
		usleep(100);
	}
}

void	perform_actions(t_philosopher *philosopher)
{
	log_state(philosopher, "is thinking");
	eat(philosopher);
	sleep_action(philosopher);
}
