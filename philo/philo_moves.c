/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 09:15:23 by jode-cas          #+#    #+#             */
/*   Updated: 2025/12/17 17:28:43 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print_status(t_philo *philosopher, t_philo_status status)
{
	long	elapsed_time;

	if (philosopher->table->is_dinner_finished && status != DIED)
		return ;
	elapsed_time = gettime() - philosopher->table->start_time;
	if (status == EAT)
		printf("%ld #%ld is EATING 🍝\n", elapsed_time, philosopher->id);
	else if (status == SLEEP)
		printf("%ld #%ld is SLEEPING 💤\n", elapsed_time, philosopher->id);
	else if (status == THINK)
		printf("%ld #%ld is THINKING 🤔💭\n", elapsed_time, philosopher->id);
	else if (status == TAKEN_FORK)
		printf("%ld #%ld has TAKEN A FORK 🍴\n", elapsed_time, philosopher->id);
	else if (status == DIED)
		printf("%ld #%ld has DIED ☠️\n", elapsed_time, philosopher->id);
}

void	eat(t_philo *philosopher)
{
	if ((philosopher->is_full || philosopher->table->is_dinner_finished)
		|| !assign_forks(philosopher))
		return ;
	philosopher->meals_made++;
	philosopher->last_meal_time = gettime();
	print_status(philosopher, EAT);
	precise_sleep_ms(philosopher->table->eat_time);
	pthread_mutex_unlock(&philosopher->right_fork->fork_mutex);
	pthread_mutex_unlock(&philosopher->left_fork->fork_mutex);
	if (philosopher->meals_made == philosopher->table->limit_meals)
		philosopher->is_full = 1;
}

void	sleep(t_philo *philosopher)
{
	if (philosopher->is_full || philosopher->table->is_dinner_finished)
		return ;
	print_status(philosopher, SLEEP);
	precise_sleep_ms(philosopher->table->sleep_time);
}

void	think(t_philo *philosopher, long think_time_in_ms)
{
	if (philosopher->is_full || philosopher->table->is_dinner_finished)
		return ;
	print_status(philosopher, THINK);
	precise_sleep_ms(think_time_in_ms);
}

char	check_death(t_philo *philosophers)
{
	unsigned long	i;
	char			is_dead;
	unsigned long	time_since_last_meal;

	i = 0;
	time_since_last_meal = gettime() - philosophers[i].last_meal_time;
	is_dead = time_since_last_meal >= philosophers->table->die_time;
	if (is_dead && !philosophers[i].is_full)
	{
		print_status(&philosophers[i], DIED);
		philosophers->table->is_dinner_finished = 1;
		return (1);
	}
	return (0);
}
