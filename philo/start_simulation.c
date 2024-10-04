/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_simulation.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/12 13:35:10 by sramos        #+#    #+#                 */
/*   Updated: 2024/09/13 17:51:38 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_create_threads(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->m_start);
	while (i < table->num_philos)
	{
		if (pthread_create(&table->philo[i].thread_id, NULL,
				&routine, &table->philo[i]) != 0)
		{
			printf("Fail to create thread!\n");
			return (1);
		}
		table->philo[i].last_meal_time = get_current_time();
		i++;
	}
	table->simulation_start_time = get_current_time();
	pthread_mutex_unlock(&table->m_start);
	return (0);
}

static int	ft_create_join_monitoring_thread(t_table *table)
{
	if (pthread_create(&table->thread_id, NULL, &monitoring, table) != 0)
	{
		printf("Fail to create monitoring thread!\n");
		return (1);
	}
	if (pthread_join(table->thread_id, NULL) != 0)
	{
		printf("Fail to join monitoring thread!\n");
		return (1);
	}
	return (0);
}

static int	ft_join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_join(table->philo[i].thread_id, NULL) != 0)
		{
			printf("Fail to join thread!\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	start_simulation(t_table *table)
{
	if (ft_create_threads(table) == 1)
		return (1);
	if (ft_create_join_monitoring_thread(table) == 1)
		return (1);
	if (ft_join_threads(table) == 1)
		return (1);
	return (0);
}
