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

char is_dead(t_philo *philosopher)
{
	char			is_dead;
	unsigned long	time_since_last_meal;

	if (philosopher->last_meal_time == 0)
		time_since_last_meal = gettime() - philosopher->table->start_time;
	else
		time_since_last_meal = gettime() - philosopher->last_meal_time;
	is_dead = time_since_last_meal >= philosopher->table->die_time;
	return is_dead;
}