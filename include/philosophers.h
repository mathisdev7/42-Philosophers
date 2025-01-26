/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:21:38 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/26 19:35:10 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philosopher
{
	int				id;
	int				left;
	int				right;
	pthread_t		thread;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_fork;
	long long		last_meal;
	int				nb_times_each_philosopher_must_eat;
	int				nb_times_each_philosopher_has_eaten;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	pthread_mutex_t	*forks;
	int				nb_philosophers;
	int				is_dead;
}					t_philosopher;

int					parse_args(char **argv);
size_t				is_number(char *str);
int					ft_error(char *str);
int					ft_atoi(const char *str);

#endif
