/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:03:51 by jode-cas          #+#    #+#             */
/*   Updated: 2025/12/12 10:03:35 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void *say_hi(void *philo_id)
{
	printf("Hello from philo %ld\n", (long)philo_id);
	return 0;
}

int	main(int argc, char *argv[])
{
	t_table	table;
	t_philo	*philosophers;
	t_fork	*forks;

	if (argc != 5 && argc != 6)
	{
		printf("Error parsing CLI inputs.");
		return (1);
	}
	
	table.n_threads_running = 0;
	table.is_dinner_finished = 0;
	table.n_philos = ft_atol(argv[1]);
	table.die_time = ft_atol(argv[2]);
	table.sleep_time = ft_atol(argv[3]);
	table.eat_time = ft_atol(argv[4]);
	if (argc == 6)
		table.n_meals = ft_atol(argv[5]);
	else
		table.n_meals = -1;
	
	philosophers = safe_malloc(sizeof(t_philo) * table.n_philos);
	int i = 0;
	while (i < table.n_philos)
	{
		philosophers[i].id = i;
		philosophers[i].is_full = 0;
		philosophers[i].meals_made = 0;
		philosophers[i].table = &table;
		pthread_create(&philosophers[i].thread, NULL, &say_hi, (void *)philosophers[i].id);
		i++;
	}
	
	forks = safe_malloc(sizeof(t_fork) * table.n_philos);
	i = 0;
	while (i < table.n_philos)
	{
		forks[i].id = i;
		i++;
	}
	i = 0;
	while (i < table.n_philos)
	{
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}
	
	return (0);
}
