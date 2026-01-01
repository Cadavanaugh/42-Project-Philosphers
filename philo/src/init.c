/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:36:28 by jode-cas          #+#    #+#             */
/*   Updated: 2025/12/29 21:21:24 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	*dinner_routine(void *arg)
{
	t_philo			*philosopher;

	philosopher = (t_philo *)arg;
	while (!get_char(&philosopher->table->table_mutex, &philosopher->table->all_threads_running))
		;
	while (!philosopher->is_full && !get_char(&philosopher->table->table_mutex, &philosopher->table->is_dinner_finished))
	{
		eat(philosopher);
		sleep(philosopher);
		think(philosopher);
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
	set_long(&table->table_mutex, &table->start_time, gettime());
	set_char(&table->table_mutex, &table->all_threads_running, 1);
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
