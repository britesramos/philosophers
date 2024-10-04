/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/26 11:45:16 by sramos        #+#    #+#                 */
/*   Updated: 2024/10/03 17:46:39 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "stdio.h"
# include "stdlib.h"
# include "limits.h"
# include "pthread.h"
# include "sys/time.h"
# include "unistd.h"
# include <stdbool.h>

typedef struct s_table	t_table;

/*Struct for forks*/
typedef struct s_fork
{
	pthread_mutex_t	mutex;
	bool			init_m_fork;
	int				fork_id;
}	t_fork;

/*Struct for philosophers*/
typedef struct s_philosophers
{
	pthread_t		thread_id;
	int				philo_id;
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	int				time_to_sleep;
	int				max_times_eat;
	int				meals_counter;
	long			last_meal_time;
	bool			i_am_dead;
	t_table			*table;
	pthread_mutex_t	m_meals;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	m_last_meal_time;
	bool			init_m_philo_meals;
	bool			init_m_philo_dead;
	bool			init_m_philo_lmeal;
	t_fork			*l_fork;
	t_fork			*r_fork;
}	t_philo;

/*General content table*/
typedef struct s_table
{
	pthread_t		thread_id;
	int				num_philos;
	long			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_times_eat;
	long			simulation_start_time;
	long			current_time;
	pthread_mutex_t	m_start;
	bool			init_m_table_start;
	t_fork			forks[200];
	t_philo			philo[200];
}	t_table;

/*Utils functions*/
int		ft_print_error(char const *str);
long	get_current_time(void);
long	get_time(t_philo *philo);
int		ft_usleep_pro(t_philo *philo, long time_to_sleep, int eat);
int		am_i_dead(t_philo *philo);
int		printf_action(t_philo *philo, int i);

/*Check input arguments and parsing into data struct.*/
int		parsing(t_table *table, char *argv[]);

/*Initialize program*/
int		init_program(t_table *table);

/*Start simulation*/
int		start_simulation(t_table *table);
void	*monitoring(void *arg);
int		eating(t_philo *philo);
void	*routine(void *arg);

/*Clean up program*/
void	end_program(t_table *table);

#endif