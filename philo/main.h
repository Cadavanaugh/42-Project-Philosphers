/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:03:49 by jode-cas          #+#    #+#             */
/*   Updated: 2025/12/13 22:06:13 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_philo	t_philo;

typedef struct s_fork
{
	long				id;
	pthread_mutex_t		fork_mutex;
}						t_fork;

typedef struct s_table
{
	long				n_philos;
	long				limit_meals;
	long				die_time;
	long				eat_time;
	long				sleep_time;
	long				start_time;
	long				is_dinner_finished;
	long				n_threads_running;
	t_philo				*philosophers;
	t_fork				*forks;
}						t_table;

typedef struct s_philo
{
	long				id;
	char				is_full;
	long				last_meal_time;
	long				meals_made;
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_t			thread;
	pthread_mutex_t		philo_mutex;
	t_table				*table;
}						t_philo;

typedef enum e_thread_operation
{
	CREATE,
	JOIN
}						t_thread_operation;

long					ft_atol(const char *nptr);
char					is_input_valid(int argc, char *argv[]);
char					init_table(t_table *table, int argc, char *argv[]);
