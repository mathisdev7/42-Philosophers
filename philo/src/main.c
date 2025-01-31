/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:53:27 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/31 16:02:18 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	free_philo_mutex(t_philo *philo, t_simu *simu)
{
	if (simu && simu->mutex)
		free(simu->mutex);
	if (simu)
		free(simu);
	if (philo && philo->fork)
		free(philo->fork);
	if (philo)
		free(philo);
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_args(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (i == 1)
		{
			if (is_number(argv[i]) == 0 || ft_atoi(argv[i]) < 1)
				return (0);
		}
		else if (i == 2 || i == 3 || i == 4)
		{
			if (is_number(argv[i]) == 0 || ft_atoi(argv[i]) < 1)
				return (0);
		}
		else if (i == 5)
		{
			if (is_number(argv[i]) == 0 || ft_atoi(argv[i]) < 1)
				return (0);
		}
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_simu	*simu;

	if (ac < 5 || ac > 6 || check_args(av) != 1)
	{
		printf("Error: invalid arguments\nUsage: ./philo ");
		printf("[nb_philo] [time_die] [time_eat] [time_sleep] ?[nb_meal]\n");
		return (EXIT_FAILURE);
	}
	if (init(&philo, &simu, ac, av))
		return (free_philo_mutex(philo, simu), EXIT_FAILURE);
	if (start_simulation(philo, simu))
		return (free_philo_mutex(philo, simu), EXIT_SUCCESS);
	free_philo_mutex(philo, simu);
	return (EXIT_SUCCESS);
}
