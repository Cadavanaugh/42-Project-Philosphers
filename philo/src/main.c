/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:03:51 by jode-cas          #+#    #+#             */
/*   Updated: 2025/12/28 16:23:32 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char *argv[])
{
	t_table			table;
	unsigned long	i;

	if (!is_input_valid(argc, argv))
	{
		printf("Error parsing CLI inputs.");
		return (1);
	}
	if (!init_table(&table, argc, argv))
		return (1);
	i = -1;
	while (++i < table.n_philos)
	{
		pthread_join(table.philosophers[i].thread, NULL);
		i++;
	}
	pthread_mutex_unlock(&
		table.write_mutex);
	i = -1;
	while (++i < table.n_philos)
	{
		pthread_mutex_unlock(&table.forks[i].fork_mutex);
		pthread_mutex_destroy(&table.forks[i].fork_mutex);
	}
	pthread_mutex_unlock(&table.write_mutex);
	pthread_mutex_destroy(&table.write_mutex);
	pthread_mutex_destroy(&table.table_mutex);
	return (0);
}
