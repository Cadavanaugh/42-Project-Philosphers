/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:03:51 by jode-cas          #+#    #+#             */
/*   Updated: 2025/12/15 18:13:52 by jode-cas         ###   ########.fr       */
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
	i = 0;
	while (i < table.n_philos)
	{
		pthread_mutex_destroy(&table.table_mutex);
		pthread_mutex_destroy(&table.philosophers[i].left_fork->fork_mutex);
		pthread_mutex_destroy(&table.philosophers[i].right_fork->fork_mutex);
		i++;
	}
	return (0);
}
