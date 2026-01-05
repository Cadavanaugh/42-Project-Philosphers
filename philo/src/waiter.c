/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 21:12:56 by jode-cas          #+#    #+#             */
/*   Updated: 2025/12/29 21:28:08 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char	is_dead(t_philo *philosopher)
{
	char			is_dead;
	unsigned long	time_since_last_meal;

	if (philosopher->last_meal_time == 0)
		time_since_last_meal = gettime() - philosopher->table->start_time;
	else
		time_since_last_meal = gettime() - philosopher->last_meal_time;
	is_dead = time_since_last_meal >= philosopher->table->die_time;
	return (is_dead);
}

static char is_everyone_full(t_table *table)
{
  unsigned long i;
  unsigned long n_fulls;

  i = -1;
  n_fulls = 0;
  while (++i < table->n_philos)
  {
    if (table->philosophers[i].is_full)
      n_fulls++;
  }
  if (n_fulls == table->n_philos)
    return 1;
  return 0;
}

static void	*waiter_routine(void *arg)
{
	t_table	*table;
  unsigned long	i;

	i = 0;
	table = (t_table *)arg;
	while (!is_anyone_dead(table) && !is_everyone_full(table))
  {
		if (is_dead(&table->philosophers[i]))
    {
      pthread_mutex_lock(&table->write_mutex);
      printf("%ld %ld died\n", gettime() - table->start_time,
        table->philosophers[i].id);
      set_char(&table->table_mutex, &table->is_anyone_dead, 1);
      pthread_mutex_unlock(&table->write_mutex);
			return (0);
    }
    i++;
    if (i == table->n_philos)
      i = 0;
  }
	return (0);
}

void	init_waiter(t_table *table)
{
	pthread_t	waiter_thread;

	pthread_create(&waiter_thread, NULL, &waiter_routine, table);
	pthread_join(waiter_thread, NULL);
}
