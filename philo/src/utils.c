/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 13:36:23 by jode-cas          #+#    #+#             */
/*   Updated: 2025/12/29 21:58:40 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	set_long(pthread_mutex_t *mutex, unsigned long *attr,
		unsigned long value)
{
	pthread_mutex_lock(mutex);
	*attr = value;
	pthread_mutex_unlock(mutex);
}

void	set_char(pthread_mutex_t *mutex, char *attr, char value)
{
	pthread_mutex_lock(mutex);
	*attr = value;
	pthread_mutex_unlock(mutex);
}

unsigned long	get_long(pthread_mutex_t *mutex, unsigned long *attr)
{
	unsigned long	value;

	pthread_mutex_lock(mutex);
	value = *attr;
	pthread_mutex_unlock(mutex);
	return (value);
}

char	get_char(pthread_mutex_t *mutex, char *attr)
{
	char	value;

	pthread_mutex_lock(mutex);
	value = *attr;
	pthread_mutex_unlock(mutex);
	return (value);
}

// void	wait_all_threads(t_table *table)
// {
// 	while (get_long(&table->table_mutex,
// 			&table->n_threads_running) < table->n_philos)
// 	{
// 		printf("Running: %lu\n", get_long(&table->table_mutex,
// 			&table->n_threads_running));
// 	}
// 	set_long(&table->table_mutex, &table->start_time, gettime());
// }

void	wait_all_threads(t_table *table)
{
    while (1)
    {
        pthread_mutex_lock(&table->table_mutex);
        if (table->n_threads_running >= table->n_philos)
        {
            pthread_mutex_unlock(&table->table_mutex);
            break;
        }
        pthread_mutex_unlock(&table->table_mutex);
    }
    pthread_mutex_lock(&table->table_mutex);
    table->start_time = gettime();
    pthread_mutex_unlock(&table->table_mutex);
}