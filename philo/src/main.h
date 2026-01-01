/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-cas <jode-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:03:49 by jode-cas          #+#    #+#             */
/*   Updated: 2025/12/29 21:13:39 by jode-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

typedef struct s_philo	t_philo;

typedef struct s_fork
{
	pthread_mutex_t		fork_mutex;
}						t_fork;

typedef struct s_table
{
	unsigned long		n_philos;
	unsigned long		limit_meals;
	unsigned long		die_time;
	unsigned long		eat_time;
	unsigned long		sleep_time;
	unsigned long		start_time;
	char				is_dinner_finished;
	char		all_threads_running;
	t_philo				*philosophers;
	t_fork				*forks;
	pthread_mutex_t		table_mutex;
}						t_table;

typedef struct s_philo
{
	unsigned long		id;
	char				is_full;
	char				has_eaten;
	char				has_slept;
	unsigned long		last_meal_time;
	unsigned long		meals_made;
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_t			thread;
	t_table				*table;
}						t_philo;

typedef enum e_philo_status
{
	EAT,
	SLEEP,
	THINK,
	DIED,
	TAKEN_FORK
}						t_philo_status;

long					ft_atol(const char *nptr);
char					is_input_valid(int argc, char *argv[]);
char					init_table(t_table *table, int argc, char *argv[]);
unsigned long			gettime(void);
void					precise_sleep_ms(long time_to_sleep_in_ms);
char					assign_forks(t_philo *philosopher);
void					print_status(t_philo *philosopher,
							t_philo_status status);
char					eat(t_philo *philosopher);
void					sleep(t_philo *philosopher);
void					die(t_philo *philosopher);
void					set_char(pthread_mutex_t *mutex, char *attr,
							char value);
void					set_long(pthread_mutex_t *mutex, unsigned long *attr,
							unsigned long value);
unsigned long			get_long(pthread_mutex_t *mutex, unsigned long *attr);
char					get_char(pthread_mutex_t *mutex, char *attr);
void					think(t_philo *philosopher);
void					wait_all_threads(t_table *table);
char					check_stop(t_philo *philosophers);
void					init_waiter(t_philo *philosophers);