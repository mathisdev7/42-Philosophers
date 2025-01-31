/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:13:23 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/31 16:02:22 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

void	ft_print(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->simu->mutex[M_PRINT]);
	if (strcmp(status, DIED) != 0 && philo_died(philo, 0))
	{
		pthread_mutex_unlock(&philo->simu->mutex[M_PRINT]);
		return ;
	}
	printf("%ldms %d %s\n", get_time() - philo->simu->time_start, philo->id,
		status);
	pthread_mutex_unlock(&philo->simu->mutex[M_PRINT]);
}

time_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		printf("Error: gettimeofday()");
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	philo_died(t_philo *philo, int nb)
{
	pthread_mutex_lock(&philo->simu->mutex[M_DIED]);
	if (nb)
		philo->simu->died = 1;
	if (philo->simu->died)
	{
		pthread_mutex_unlock(&philo->simu->mutex[M_DIED]);
		return (1);
	}
	pthread_mutex_unlock(&philo->simu->mutex[M_DIED]);
	return (0);
}

void	destroy_all_mutexes(t_philo *philo, t_simu *simu)
{
	int	i;

	i = 0;
	while (i < philo->simu->nb_philo)
		pthread_mutex_destroy(&philo->fork[i++]);
	i = 0;
	while (i < M_NUM)
		pthread_mutex_destroy(&simu->mutex[i++]);
}

int	ft_atoi(const char *str)
{
	int	neg;
	int	i;
	int	num;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * neg);
}
