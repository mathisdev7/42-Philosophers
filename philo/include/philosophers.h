/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:21:38 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/31 16:05:25 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define THINKING "is thinking"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define DIED "died"
# define FORK "has taken a fork"

typedef enum e_mutexes
{
	M_PRINT,
	M_MEAL,
	M_DONE,
	M_DIED,
	M_NUM
}					t_mutex;

struct	s_philo;

typedef struct s_simu
{
	int				nb_philo;
	time_t			time_die;
	time_t			time_eat;
	time_t			time_slp;
	int				must_eat;
	time_t			time_thk;
	time_t			time_start;
	int				done;
	int				died;
	pthread_mutex_t	*mutex;
	struct s_philo	*philos;
}					t_simu;

typedef struct s_philo
{
	int				id;
	time_t			last_meal;
	int				time_ate;
	int				f[2];
	pthread_mutex_t	*fork;
	t_simu			*simu;
}					t_philo;

int					init(t_philo **philo, t_simu **simu, int ac, char **av);
void				ft_print(t_philo *philo, char *status);
int					ft_atoi(const char *str);
int					start_simulation(t_philo *philo, t_simu *simu);
time_t				get_time(void);
int					philo_died(t_philo *philo, int nb);
void				philo_sleep(time_t ms);
int					grab_fork(char s, int a, int b);
void				philo_finish_eating(t_philo *p);
int					philo_eating(t_philo *p);
void				destroy_all_mutexes(t_philo *philo, t_simu *simu);
int					philo_died(t_philo *philo, int nb);
int					task_done(t_simu *simu);
int					init_forks(pthread_mutex_t **fork, int nb_philo);

#endif
