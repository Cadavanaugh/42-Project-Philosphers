/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:36:28 by jode-cas          #+#    #+#             */
/*   Updated: 2025/12/11 18:44:49 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	init_table(t_table *table, int argc, char *argv[])
{
	table->n_threads_running = 0;
	table->is_dinner_finished = 0;
	table->n_philos = ft_atol(argv[1]);
	table->die_time = ft_atol(argv[2]);
	table->sleep_time = ft_atol(argv[3]);
	table->eat_time = ft_atol(argv[4]);
	if (argc == 6)
		table->n_meals = ft_atol(argv[5]);
	else
		table->n_meals = -1;
}

static void	init_philos(t_table *table, t_philo *philosophers)
{
	int	i;

	philosophers = safe_malloc(sizeof(t_philo) * table->n_philos);
	i = 0;
	while (i < table->n_philos)
	{
		philosophers[i].id = i;
		philosophers[i].is_full = 0;
		philosophers[i].meals_made = 0;
		philosophers[i].table = table;
		i++;
	}
}

static void	init_forks(t_table *table, t_fork *forks)
{
	int	i;

	forks = safe_malloc(sizeof(t_fork) * table->n_philos);
	i = 0;
	while (i < table->n_philos)
	{
		forks[i].id = i;
		i++;
	}
}

void	data_init(t_table *table, t_philo *philosophers, t_fork *forks,
		int argc, char *argv[])
{
	init_table(table, argc, argv);
	init_philos(table, philosophers);
	init_forks(table, forks);
}
