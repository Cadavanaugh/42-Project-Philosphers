/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grab_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:29:23 by jode-cas          #+#    #+#             */
/*   Updated: 2025/12/16 17:50:21 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char	grab_try(t_philo *philosopher, pthread_mutex_t *fork_mutex)
{
	pthread_mutex_lock(fork_mutex);
	if (philosopher->table->is_dinner_finished)
	{
		pthread_mutex_unlock(fork_mutex);
		return (0);
	}
	print_status(philosopher, TAKEN_FORK);
	return (1);
}

static char	even_grab(t_philo *philosopher)
{
	if (grab_try(philosopher, &philosopher->right_fork->fork_mutex)
		&& grab_try(philosopher, &philosopher->left_fork->fork_mutex))
		return (1);
	return (0);
}

static char	odd_grab(t_philo *philosopher)
{
	if (grab_try(philosopher, &philosopher->left_fork->fork_mutex)
		&& grab_try(philosopher, &philosopher->right_fork->fork_mutex))
		return (1);
	return (0);
}

void	assign_forks(t_philo *philosopher)
{
	if (philosopher->id % 2 == 0)
		odd_grab(philosopher);
	else
		even_grab(philosopher);
}