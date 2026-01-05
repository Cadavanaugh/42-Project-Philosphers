/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 23:09:15 by jode-cas          #+#    #+#             */
/*   Updated: 2025/12/15 18:09:27 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

unsigned long	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
}

void	precise_sleep_ms(long time_to_sleep_in_ms)
{
	unsigned long	initial_time;
	unsigned long remaining_time;
	unsigned long target_time;

	initial_time = gettime();
	target_time = initial_time + time_to_sleep_in_ms;
	while (gettime() < target_time)
	{
		remaining_time = target_time - gettime();
		usleep(remaining_time / 2);
	}
}
