/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:37:20 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/27 01:18:55 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	choose_condition(t_philosopher *philosopher, int *condition)
{
	if (philosopher->nb_times_each_philosopher_must_eat == -1)
		*condition = 1;
	else
		*condition = philosopher->nb_times_each_philosopher_has_eaten \
		< philosopher->nb_times_each_philosopher_must_eat;
}

void	*thread_routine(void *data)
{
	t_philosopher	*philosopher;
	int				condition;
	long long		current_time;

	philosopher = (t_philosopher *)data;
	choose_condition(philosopher, &condition);
	while (condition)
	{
		choose_condition(philosopher, &condition);
		if (!philosopher->simulation->is_running)
		{
			pthread_mutex_unlock(&philosopher->simulation->mutex);
			break ;
		}
		current_time = get_current_time();
		if (current_time - philosopher->last_meal > philosopher->time_to_die)
		{
			log_state(philosopher, "died");
			philosopher->simulation->is_running = 0;
			pthread_mutex_unlock(&philosopher->simulation->mutex);
			break ;
		}
		pthread_mutex_unlock(&philosopher->simulation->mutex);
		perform_actions(philosopher);
	}
}
