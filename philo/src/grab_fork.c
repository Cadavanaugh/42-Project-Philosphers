/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grab_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:29:23 by jode-cas          #+#    #+#             */
/*   Updated: 2026/01/04 15:19:20 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char	grab_try(t_philo *philosopher, t_fork *fork)
{
	pthread_mutex_lock(&fork->fork_mutex);
	fork->in_use = 1;
	if (is_dinner_finished(philosopher->table))
	{
		pthread_mutex_unlock(&fork->fork_mutex);
		fork->in_use = 0;
		return (0);
	}
	print_status(philosopher, TAKEN_FORK);
	return (1);
}

static char	even_grab(t_philo *philosopher)
{
	if (grab_try(philosopher, philosopher->right_fork) && grab_try(philosopher,
			philosopher->left_fork))
		return (1);
	return (0);
}

static char	odd_grab(t_philo *philosopher)
{
	if (grab_try(philosopher, philosopher->left_fork) && grab_try(philosopher,
			philosopher->right_fork))
		return (1);
	return (0);
}

char	assign_forks(t_philo *philosopher)
{
	if (philosopher->table->n_philos == 1)
	{
		if (!philosopher->has_eaten)
		{
			print_status(philosopher, TAKEN_FORK);
			philosopher->has_eaten = 1;
		}
		return (0);
	}
	if (philosopher->id % 2 == 1
		&& philosopher->id == philosopher->table->n_philos)
		precise_sleep_ms(1);
	if (philosopher->id % 2 == 0)
		return (even_grab(philosopher));
	else
		return (odd_grab(philosopher));
}

void	release_forks(t_philo *philosopher)
{
	if (philosopher->left_fork->in_use)
		pthread_mutex_unlock(&philosopher->left_fork->fork_mutex);
	if (philosopher->right_fork->in_use)
		pthread_mutex_unlock(&philosopher->right_fork->fork_mutex);
}
