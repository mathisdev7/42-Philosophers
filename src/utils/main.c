/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:16:23 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/27 00:49:07 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

long long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

void	log_state(t_philosopher *philosopher, const char *state)
{
	long long	current_time;
	long long	elapsed_time;

	pthread_mutex_lock(&philosopher->mutex_print);
	if (philosopher->simulation->is_running)
	{
		current_time = get_current_time();
		elapsed_time = current_time - philosopher->simulation->start_time;
		printf("%lldms %d %s\n", elapsed_time, philosopher->id + 1, state);
	}
	pthread_mutex_unlock(&philosopher->mutex_print);
}

int	ft_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

size_t	is_number(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	parse_args(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (i == 1)
		{
			if (is_number(argv[i]) == 0 || ft_atoi(argv[i]) < 1)
				return (ft_error("You need to put at least 1 philosopher."));
		}
		else if (i == 2 || i == 3 || i == 4)
		{
			if (is_number(argv[i]) == 0 || ft_atoi(argv[i]) < 1)
				return (ft_error("You need to put a time in ms."));
		}
		i++;
	}
	return (1);
}
