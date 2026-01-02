/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 21:12:56 by jode-cas          #+#    #+#             */
/*   Updated: 2025/12/29 21:28:08 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char	check_stop(t_philo *philosophers)
{
	unsigned long	i;
	unsigned long	n_of_fulls;

	n_of_fulls = 0;
	i = -1;
	while (++i < philosophers->table->n_philos)
	{
		if (philosophers[i].is_full)
			n_of_fulls++;
		else if (is_dead(&philosophers[i]))
			return (1);
	}
	if (n_of_fulls == philosophers->table->n_philos)
		return (1);
	return (0);
}

static void	*waiter_routine(void *arg)
{
	t_philo	*philosophers;

	philosophers = (t_philo *)arg;
	while (1)
	{
		if(check_stop(philosophers))
		{
			set_char(&philosophers->table->table_mutex,
				&philosophers->table->is_dinner_finished, 1);
			break;
		}
	}
	return (0);
}

void	init_waiter(t_philo *philosophers)
{
	pthread_t	waiter_thread;

	pthread_create(&waiter_thread, NULL, &waiter_routine, philosophers);
	pthread_join(waiter_thread, NULL);
}