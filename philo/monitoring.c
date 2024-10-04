/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/12 18:21:25 by sramos        #+#    #+#                 */
/*   Updated: 2024/10/04 16:32:11 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_philos_dead(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->philo[i].m_dead);
		table->philo[i].i_am_dead = 1;
		pthread_mutex_unlock(&table->philo[i].m_dead);
		i++;
	}
}

static int	simulation_ended(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->philo[i].m_meals);
		if (table->max_times_eat == table->philo[i].meals_counter)
		{
			pthread_mutex_unlock(&table->philo[i].m_meals);
			return (1);
		}
		pthread_mutex_unlock(&table->philo[i].m_meals);
		i++;
	}
	return (0);
}

static int	philo_starved(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->philo[i].m_last_meal_time);
		if (get_current_time() - table->philo[i].last_meal_time
			> table->time_to_die)
		{
			set_philos_dead(table);
			pthread_mutex_lock(&table->m_start);
			printf("%ld This philo has died: %i\n", get_current_time()
				- table->simulation_start_time, i + 1);
			pthread_mutex_unlock(&table->m_start);
			pthread_mutex_unlock(&table->philo[i].m_last_meal_time);
			return (1);
		}
		pthread_mutex_unlock(&table->philo[i].m_last_meal_time);
		i++;
	}
	return (0);
}

void	*monitoring(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		if (philo_starved(table) == 1 || simulation_ended(table) == 1)
			break ;
		usleep(100);
	}
	return (0);
}
