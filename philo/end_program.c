/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   end_program.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/10 12:11:37 by sramos        #+#    #+#                 */
/*   Updated: 2024/10/03 11:17:17 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_program(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		if (table->forks[i].init_m_fork == true)
			pthread_mutex_destroy(&table->forks[i].mutex);
		if (table->philo[i].init_m_philo_dead == true)
			pthread_mutex_destroy(&table->philo[i].m_dead);
		if (table->philo[i].init_m_philo_meals == true)
			pthread_mutex_destroy(&table->philo[i].m_meals);
		if (table->philo[i].init_m_philo_lmeal == true)
			pthread_mutex_destroy(&table->philo[i].m_last_meal_time);
		i++;
	}
	if (table->init_m_table_start == true)
		pthread_mutex_destroy(&table->m_start);
}
