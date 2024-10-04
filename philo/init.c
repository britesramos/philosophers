/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/03 17:44:26 by sramos        #+#    #+#                 */
/*   Updated: 2024/10/03 17:47:05 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_forks(t_fork *forks, int i)
{
	forks[i].fork_id = i;
	forks[i].init_m_fork = false;
	if (pthread_mutex_init(&forks[i].mutex, NULL) != 0)
		return (ft_print_error("Mutex init failed [fork]!"));
	forks[i].init_m_fork = true;
	return (0);
}

static void	assign_forks(t_table *table, int i)
{
	table->philo[i].r_fork = &table->forks[i];
	if (table->philo[i].philo_id == table->num_philos)
		table->philo[i].l_fork = &table->forks[0];
	else
		table->philo[i].l_fork = &table->forks[i + 1];
}

static int	init_struct_philo(t_table *table, int i)
{
	table->philo[i].num_philos = table->num_philos;
	table->philo[i].philo_id = i + 1;
	table->philo[i].time_to_die = table->time_to_die;
	table->philo[i].time_to_eat = table->time_to_eat;
	table->philo[i].time_to_sleep = table->time_to_sleep;
	table->philo[i].max_times_eat = table->max_times_eat;
	table->philo[i].meals_counter = 0;
	table->philo[i].table = table;
	table->philo[i].last_meal_time = 0;
	table->philo[i].i_am_dead = 0;
	table->philo[i].init_m_philo_dead = false;
	table->philo[i].init_m_philo_meals = false;
	table->philo[i].init_m_philo_lmeal = false;
	if (pthread_mutex_init(&table->philo[i].m_dead, NULL) != 0)
		return (ft_print_error("Creating m_dead failed! [philo]"));
	table->philo[i].init_m_philo_dead = true;
	if (pthread_mutex_init(&table->philo[i].m_meals, NULL) != 0)
		return (ft_print_error("Creating m_meals failed! [philo]"));
	table->philo[i].init_m_philo_meals = true;
	if (pthread_mutex_init(&table->philo[i].m_last_meal_time, NULL) != 0)
		return (ft_print_error("Creating m_last_meal_time failed! [philo]"));
	table->philo[i].init_m_philo_lmeal = true;
	assign_forks(table, i);
	return (0);
}

static int	init_main_struct(t_table *table)
{
	table->init_m_table_start = false;
	if (pthread_mutex_init(&table->m_start, NULL) != 0)
		return (ft_print_error("Creating m_start failed!"));
	table->init_m_table_start = true;
	table->simulation_start_time = 0;
	table->current_time = 0;
	return (0);
}

int	init_program(t_table *table)
{
	int	i;

	i = 0;
	if (init_main_struct(table) == 1)
		return (1);
	while (i < table->num_philos)
	{
		if (init_forks(table->forks, i) == 1)
			return (1);
		if (init_struct_philo(table, i) == 1)
			return (1);
		i++;
	}
	return (0);
}
