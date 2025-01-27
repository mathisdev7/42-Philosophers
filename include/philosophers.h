/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:21:38 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/27 01:19:46 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_simulation
{
	int				is_running;
	pthread_mutex_t	mutex;
	long long		start_time;
	pthread_mutex_t	*forks;
}					t_simulation;

typedef struct s_philosopher
{
	int				id;
	int				nb_philosophers;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				nb_times_each_philosopher_must_eat;
	int				nb_times_each_philosopher_has_eaten;
	long long		last_meal;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex_print;
	t_simulation	*simulation;
}					t_philosopher;

typedef struct s_thread_info
{
	t_philosopher	*philosophers;
	pthread_t		*threads;
	int				nb_philosophers;
	char			**argv;
	t_simulation	*simulation;
}					t_thread_info;

int					parse_args(char **argv);
size_t				is_number(char *str);
int					ft_error(char *str);
void				*thread_routine(void *data);
void				perform_actions(t_philosopher *philosopher);
void				log_state(t_philosopher *philosopher, const char *state);
long long			get_current_time(void);
int					ft_atoi(const char *str);
void				eat(t_philosopher *philosopher);
void				sleep_action(t_philosopher *philosopher);
void				take_forks(t_philosopher *philosopher);
void				release_forks(t_philosopher *philosopher);
void				wait_action(t_philosopher *philosopher, long long duration);
void				perform_actions(t_philosopher *philosopher);
int					init_philosophers(char **argv, t_simulation *simulation);
int					init_mutexes(pthread_mutex_t *forks, int nb_philosophers,
						t_simulation *simulation);
int					allocate_resources(int nb_philosophers,
						t_philosopher **philosophers, pthread_t **threads,
						pthread_mutex_t **forks);
void				init_philosopher(t_philosopher *phil, char **argv, int i,
						t_simulation *simulation);
void				cleanup_resources(t_philosopher *philosophers,
						pthread_t *threads, pthread_mutex_t *forks,
						int nb_philosophers);
void				create_and_join_threads(t_thread_info *info);

#endif
