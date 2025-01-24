/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:21:38 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/23 14:53:02 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "libft/libft.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

struct			s_philosopher
{
	int			id;
	int			left;
	int			right;
	pthread_t	eater;
	pthread_t	thinker;
}				t_philosopher;

void			*eat(void *arg);
void			*think(void *arg);

#endif
