/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:36:28 by jode-cas          #+#    #+#             */
/*   Updated: 2025/12/13 22:50:19 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	*get_forks(void *arg)
{
	t_philo *philosopher = (t_philo *)arg;
	pthread_mutex_lock(&philosopher->right_fork->fork_mutex);
	printf("#%ld got right fork (#%ld)\n", philosopher->id, philosopher->right_fork->id);
	pthread_mutex_lock(&philosopher->left_fork->fork_mutex);
	printf("#%ld got left fork (#%ld)\n", philosopher->id, philosopher->left_fork->id);
	// pthread_mutex_unlock(&philosopher->right_fork->fork_mutex); 
	// pthread_mutex_unlock(&philosopher->left_fork->fork_mutex);
	return (0);
}

static void	init_philos_and_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		table->forks[i].id = i;
		pthread_mutex_init(&table->forks[i].fork_mutex, NULL);
		table->philosophers[i].id = i;
		table->philosophers[i].is_full = 0;
		table->philosophers[i].meals_made = 0;
		table->philosophers[i].table = table;
		table->philosophers[i].right_fork = &table->forks[i];
		if (i == 0)
			table->philosophers[i].left_fork = &table->forks[table->n_philos
				- 1];
		else
			table->philosophers[i].left_fork = &table->forks[i - 1];
		pthread_create(&table->philosophers[i].thread, NULL, &get_forks,
			(void *)&table->philosophers[i]);
		i++;
	}
}

char	init_table(t_table *table, int argc, char *argv[])
{
	table->n_threads_running = 0;
	table->is_dinner_finished = 0;
	table->n_philos = ft_atol(argv[1]);
	table->die_time = ft_atol(argv[2]);
	table->sleep_time = ft_atol(argv[3]);
	table->eat_time = ft_atol(argv[4]);
	if (argc == 6)
		table->limit_meals = ft_atol(argv[5]);
	else
		table->limit_meals = -1;
	table->philosophers = malloc(sizeof(t_philo) * table->n_philos);
	table->forks = malloc(sizeof(t_fork) * table->n_philos);
	if (!table->philosophers || !table->forks)
		return (0);
	init_philos_and_forks(table);
	return (1);
}
