/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:36:28 by jode-cas          #+#    #+#             */
/*   Updated: 2025/12/28 14:12:28 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	*dinner_routine(void *arg)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)arg;
	set_long(&philosopher->table->table_mutex,
		&philosopher->table->n_threads_running,
		philosopher->table->n_threads_running + 1);
	wait_all_threads(philosopher->table);
	while (!philosopher->is_full && !philosopher->table->is_dinner_finished)
	{
		if (!philosopher->has_eaten)
		{
			if (eat(philosopher))
				philosopher->has_eaten = 1;
		}
		else if (!philosopher->has_slept)
		{
			sleep(philosopher);
			philosopher->has_slept = 1;
		}
		else
		{
			philosopher->has_eaten = 0;
			philosopher->has_slept = 0;
			think(philosopher);
		}
	}
	return (0);
}

static void	init_philos_and_forks(t_table *table)
{
	unsigned long	i;

	i = 0;
	while (i < table->n_philos)
	{
		table->forks[i].id = i;
		pthread_mutex_init(&table->forks[i].fork_mutex, NULL);
		table->philosophers[i].id = i + 1;
		table->philosophers[i].is_full = 0;
		table->philosophers[i].has_eaten = 0;
		table->philosophers[i].has_slept = 0;
		table->philosophers[i].meals_made = 0;
		table->philosophers[i].last_meal_time = gettime();
		table->philosophers[i].table = table;
		table->philosophers[i].right_fork = &table->forks[i];
		if (i == 0)
			table->philosophers[i].left_fork = &table->forks[table->n_philos
				- 1];
		else
			table->philosophers[i].left_fork = &table->forks[i - 1];
		pthread_create(&table->philosophers[i].thread, NULL, &dinner_routine,
			&table->philosophers[i]);
		i++;
	}
}

static void	*waiter_routine(void *arg)
{
	t_philo	*philosophers;

	philosophers = (t_philo *)arg;
	wait_all_threads(philosophers->table);
	while (!philosophers->table->is_dinner_finished)
	{
		if (check_stop(philosophers))
			break ;
	}
	return (0);
}

static void	init_waiter(t_philo *philosophers)
{
	pthread_t	waiter_thread;

	pthread_create(&waiter_thread, NULL, &waiter_routine, philosophers);
	pthread_join(waiter_thread, NULL);
}

char	init_table(t_table *table, int argc, char *argv[])
{
	pthread_mutex_init(&table->table_mutex, NULL);
	table->n_threads_running = 0;
	table->is_dinner_finished = 0;
	table->n_philos = ft_atol(argv[1]);
	table->die_time = ft_atol(argv[2]);
	table->eat_time = ft_atol(argv[3]);
	table->sleep_time = ft_atol(argv[4]);
	if (argc == 6)
		table->limit_meals = ft_atol(argv[5]);
	else
		table->limit_meals = -1;
	table->philosophers = malloc(sizeof(t_philo) * table->n_philos);
	table->forks = malloc(sizeof(t_fork) * table->n_philos);
	if (!table->philosophers || !table->forks)
		return (0);
	init_philos_and_forks(table);
	init_waiter(table->philosophers);
	return (1);
}
