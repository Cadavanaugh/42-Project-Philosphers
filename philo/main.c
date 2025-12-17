/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:03:51 by jode-cas          #+#    #+#             */
/*   Updated: 2025/12/16 18:40:57 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char *argv[])
{
	t_table	table;
	unsigned long		i;

	if (!is_input_valid(argc, argv))
	{
		printf("Error parsing CLI inputs.");
		return (1);
	}
	if (!init_table(&table, argc, argv))
		return (1);
	init_waiter(table.philosophers);
	i = 0;
	while (i < table.n_philos)
	{
		pthread_join(table.philosophers[i].thread, NULL);
		i++;
	}
	pthread_mutex_destroy(&table.table_mutex);
	i = 0;
	while (i < table.n_philos)
	{
		pthread_mutex_destroy(&table.forks[i].fork_mutex);
		i++;
	}
	return (0);
}
