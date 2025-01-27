/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 01:13:26 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/27 01:13:36 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	eat(t_philosopher *philosopher)
{
	take_forks(philosopher);
	pthread_mutex_lock(&philosopher->simulation->mutex);
	philosopher->last_meal = get_current_time();
	philosopher->nb_times_each_philosopher_has_eaten++;
	pthread_mutex_unlock(&philosopher->simulation->mutex);
	log_state(philosopher, "is eating");
	wait_action(philosopher, philosopher->time_to_eat);
	release_forks(philosopher);
}

void	sleep_action(t_philosopher *philosopher)
{
	log_state(philosopher, "is sleeping");
	wait_action(philosopher, philosopher->time_to_sleep);
}
