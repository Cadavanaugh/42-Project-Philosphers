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

char	check_stop(t_philo *philosophers)
{
	unsigned long	i;
	char			is_dead;
	unsigned long	time_since_last_meal;
	unsigned long	n_of_fulls;

	n_of_fulls = 0;
	i = 0;
	while (i < philosophers->table->n_philos)
	{
		if (philosophers[i].is_full)
			n_of_fulls++;
		time_since_last_meal = gettime() - philosophers[i].last_meal_time;
		is_dead = time_since_last_meal >= philosophers->table->die_time;
		if (is_dead && !philosophers[i].is_full)
		{
			die(&philosophers[i]);
			return (1);
		}
		i++;
	}
	if (n_of_fulls == philosophers->table->n_philos)
		return (1);
	return (0);
}

static void	*waiter_routine(void *arg)
{
	t_philo	*philosophers;

	philosophers = (t_philo *)arg;
	wait_all_threads(philosophers->table);
	while (!get_char(&philosophers->table->table_mutex,
			&philosophers->table->is_dinner_finished))
	{
		if (check_stop(philosophers))
			break ;
	}
	return (0);
}

void	init_waiter(t_philo *philosophers)
{
	pthread_t	waiter_thread;

	pthread_create(&waiter_thread, NULL, &waiter_routine, philosophers);
	pthread_join(waiter_thread, NULL);
}