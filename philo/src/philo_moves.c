/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 09:15:23 by jode-cas          #+#    #+#             */
/*   Updated: 2026/01/04 15:36:57 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print_status(t_philo *philosopher, t_philo_status status)
{
	unsigned long	elapsed_time;

	pthread_mutex_lock(&philosopher->table->write_mutex);
	elapsed_time = gettime() - get_long(&philosopher->table->table_mutex,
			&philosopher->table->start_time);
	if (is_anyone_dead(philosopher->table))
	{
		pthread_mutex_unlock(&philosopher->table->write_mutex);
		return ;
	}
	if (status == EAT)
		printf("%ld %ld is eating\n", elapsed_time, philosopher->id);
	else if (status == SLEEP)
		printf("%ld %ld is sleeping\n", elapsed_time, philosopher->id);
	else if (status == THINK)
		printf("%ld %ld is thinking\n", elapsed_time, philosopher->id);
	else if (status == TAKEN_FORK)
		printf("%ld %ld has taken a fork\n", elapsed_time, philosopher->id);
	pthread_mutex_unlock(&philosopher->table->write_mutex);
}

char	eat(t_philo *philosopher)
{
	if (!assign_forks(philosopher) || philosopher->has_eaten)
		return (0);
	print_status(philosopher, EAT);
	philosopher->last_meal_time = gettime();
	precise_sleep_ms(philosopher->table->eat_time);
	philosopher->meals_made++;
	philosopher->has_eaten = 1;
	pthread_mutex_unlock(&philosopher->right_fork->fork_mutex);
	pthread_mutex_unlock(&philosopher->left_fork->fork_mutex);
	if (philosopher->meals_made == get_long(&philosopher->table->table_mutex,
			&philosopher->table->limit_meals))
		philosopher->is_full = 1;
	return (1);
}

void	sleep(t_philo *philosopher)
{
	if (philosopher->has_slept || is_anyone_dead(philosopher->table))
		return ;
	print_status(philosopher, SLEEP);
	precise_sleep_ms(philosopher->table->sleep_time);
	philosopher->has_slept = 1;
}

void	think(t_philo *philosopher)
{
	if (is_anyone_dead(philosopher->table))
		return ;
	print_status(philosopher, THINK);
	if (philosopher->table->n_philos % 2 == 0)
	{
		if (philosopher->table->eat_time > philosopher->table->sleep_time)
			precise_sleep_ms(philosopher->table->eat_time
				- philosopher->table->sleep_time);
	}
	else
	{
		if (philosopher->table->eat_time == philosopher->table->sleep_time)
			precise_sleep_ms(philosopher->table->eat_time);
		else if (philosopher->table->eat_time < philosopher->table->sleep_time)
			precise_sleep_ms(philosopher->table->eat_time * 2
				- philosopher->table->sleep_time);
	}
	philosopher->has_eaten = 0;
	philosopher->has_slept = 0;
}
