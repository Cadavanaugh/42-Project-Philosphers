/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 14:20:16 by jode-cas          #+#    #+#             */
/*   Updated: 2025/12/23 18:54:44 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	wait_all_threads(t_table *table)
{
	while (get_long(&table->table_mutex,
			&table->n_threads_running) < table->n_philos)
		;
	set_long(&table->table_mutex, &table->start_time, gettime());
}
