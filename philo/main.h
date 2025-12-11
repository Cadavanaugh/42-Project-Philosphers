/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:03:49 by jode-cas          #+#    #+#             */
/*   Updated: 2025/12/11 13:09:28 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_fork {
	long id;
	pthread_mutex_t fork_mutex;
} t_fork;

typedef struct s_table
{
	long n_philos;
	long n_meals;
	long die_time;
	long eat_time;
	long sleep_time;
	long start_time;
	long is_dinner_finished;
	long n_threads_running;
} t_table;

typedef struct s_philo {
	char is_full;
	t_fork *left_fork;
	t_fork *right_fork;
} t_philo;