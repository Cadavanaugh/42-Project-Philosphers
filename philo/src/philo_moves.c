/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 09:15:23 by jode-cas          #+#    #+#             */
/*   Updated: 2025/12/29 21:12:54 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print_status(t_philo *philosopher, t_philo_status status)
{
	long	elapsed_time;

	if (get_char(&philosopher->table->table_mutex,
			&philosopher->table->is_dinner_finished) && status != DIED)
		return ;
	elapsed_time = gettime() - philosopher->table->start_time;
	if (status == EAT)
		printf("%ld %ld is eating\n", elapsed_time, philosopher->id);
	else if (status == SLEEP)
		printf("%ld %ld is sleeping\n", elapsed_time, philosopher->id);
	else if (status == THINK)
		printf("%ld %ld is thinking\n", elapsed_time, philosopher->id);
	else if (status == TAKEN_FORK)
		printf("%ld %ld has taken a fork\n", elapsed_time, philosopher->id);
	else if (status == DIED)
		printf("%ld %ld died\n", elapsed_time, philosopher->id);
}

char	eat(t_philo *philosopher)
{
	if (!assign_forks(philosopher))
		return (0);
	philosopher->last_meal_time = gettime();
	print_status(philosopher, EAT);
	precise_sleep_ms(philosopher->table->eat_time);
	philosopher->meals_made++;
	pthread_mutex_unlock(&philosopher->right_fork->fork_mutex);
	pthread_mutex_unlock(&philosopher->left_fork->fork_mutex);
	if (philosopher->meals_made == get_long(&philosopher->table->table_mutex,
			&philosopher->table->limit_meals))
		philosopher->is_full = 1;
	return (1);
}

void	sleep(t_philo *philosopher)
{
	print_status(philosopher, SLEEP);
	precise_sleep_ms(philosopher->table->sleep_time);
}

void	think(t_philo *philosopher)
{
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
}

void	die(t_philo *philosopher)
{
	pthread_mutex_unlock(&philosopher->right_fork->fork_mutex);
	pthread_mutex_unlock(&philosopher->left_fork->fork_mutex);
	print_status(philosopher, DIED);
	set_char(&philosopher->table->table_mutex,
		&philosopher->table->is_dinner_finished, 1);
}

