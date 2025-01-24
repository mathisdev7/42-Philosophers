/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:23:19 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/23 14:51:11 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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

int	main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (ft_error("You need to send at least 4 arguments."));
	parse_args(argv);
}
