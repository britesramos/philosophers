/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf_functions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/03 17:49:36 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/10 16:03:58 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print_error(char const *str)
{
	printf("%s\n", str);
	return (1);
}

static void	print_action(pthread_mutex_t *m_printf, char *str, t_philo *philo)
{
	pthread_mutex_lock(m_printf);
	printf("%ld %i %s\n", get_time(philo), philo->philo_id, str);
	pthread_mutex_unlock(m_printf);
}

int	printf_action(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->m_dead);
	if (philo->i_am_dead == 1)
	{
		pthread_mutex_unlock(&philo->m_dead);
		return (1);
	}
	else if (i == 1)
		print_action(&philo->table->m_printf, "has taken a fork", philo);
	else if (i == 2)
		print_action(&philo->table->m_printf, "is thinking", philo);
	else if (i == 3)
		print_action(&philo->table->m_printf, "is sleeping", philo);
	else if (i == 4)
	{
		pthread_mutex_lock(&philo->m_last_meal_time);
		philo->last_meal_time = get_current_time();
		pthread_mutex_unlock(&philo->m_last_meal_time);
		print_action(&philo->table->m_printf, "is eating", philo);
	}
	pthread_mutex_unlock(&philo->m_dead);
	return (0);
}
