/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 09:15:23 by jode-cas          #+#    #+#             */
/*   Updated: 2025/12/16 17:54:44 by jode-cas         ###   ########.fr       */
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
	if (philosopher->is_full || philosopher->table->is_dinner_finished)
		return ;
	assign_forks(philosopher);
	philosopher->meals_made++;
	philosopher->last_meal_time = gettime();
	precise_sleep_ms(philosopher->table->eat_time);
	print_status(philosopher, EAT);
	if (philosopher->meals_made == philosopher->table->limit_meals)
		philosopher->is_full = 1;
	pthread_mutex_unlock(&philosopher->right_fork->fork_mutex);
	pthread_mutex_unlock(&philosopher->left_fork->fork_mutex);
}

void	sleep(t_philo *philosopher)
{
	if (philosopher->is_full || dinner_has_finished(philosopher->table))
		return ;
	print_status(philosopher, SLEEP);
	precise_sleep_ms(philosopher->table->sleep_time);
}

void	think(t_philo *philosopher, long think_time_in_ms)
{
	print_status(philosopher, THINK);
	precise_sleep_ms(think_time_in_ms);
}
