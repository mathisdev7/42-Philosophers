/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:04:38 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/31 16:04:50 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	init_forks(pthread_mutex_t **fork, int nb_philo)
{
	int	i;

	*fork = malloc(sizeof(pthread_mutex_t) * ((size_t)nb_philo));
	if (*fork == NULL)
		return (1);
	i = 0;
	while (i < nb_philo)
		pthread_mutex_init(&(*fork)[i++], NULL);
	return (0);
}
