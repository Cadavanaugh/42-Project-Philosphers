/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 13:36:23 by jode-cas          #+#    #+#             */
/*   Updated: 2025/12/16 18:35:13 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	set_long(pthread_mutex_t *mutex, unsigned long *attr, unsigned long value)
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
