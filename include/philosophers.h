/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:21:38 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/24 21:08:29 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philosopher
{
	int				id;
	int				left;
	int				right;
	pthread_t		eater;
	pthread_t		thinker;
	pthread_t		sleeper;
	pthread_t		die;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_fork;
	pthread_mutex_t	mutex_eat;
	pthread_mutex_t	mutex_sleep;
	pthread_mutex_t	mutex_think;
	pthread_mutex_t	mutex_die;
	long long		last_meal;
	int				nb_times_each_philosopher_must_eat;
	int				nb_times_each_philosopher_has_eaten;
}					t_philosopher;

int					parse_args(char **argv);
size_t				is_number(char *str);
int					ft_error(char *str);
int					ft_atoi(const char *str);

#endif
