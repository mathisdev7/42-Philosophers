/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:53:27 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/27 01:17:09 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	init_philosophers(char **argv, t_simulation *simulation)
{
	t_thread_info	info;
	int				nb_philosophers;

	nb_philosophers = ft_atoi(argv[1]);
	if (nb_philosophers <= 0)
		return (ft_error("Invalid number of philosophers."));
	if (!allocate_resources(nb_philosophers, &info.philosophers, &info.threads,
			&simulation->forks))
		return (0);
	simulation->is_running = 1;
	simulation->start_time = get_current_time();
	simulation->forks = simulation->forks;
	init_mutexes(simulation->forks, nb_philosophers, simulation);
	info.nb_philosophers = nb_philosophers;
	info.argv = argv;
	info.simulation = simulation;
	create_and_join_threads(&info);
	cleanup_resources(info.philosophers, info.threads, simulation->forks,
		nb_philosophers);
	return (1);
}

int	main(int argc, char **argv)
{
	t_simulation	simulation;

	if (argc != 5 && argc != 6)
		return (ft_error("You need to send at least 4 arguments."));
	if (!parse_args(argv))
		return (1);
	if (!init_philosophers(argv, &simulation))
		return (1);
	return (0);
}
