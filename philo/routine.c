/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/03 18:06:56 by sramos        #+#    #+#                 */
/*   Updated: 2024/10/03 17:48:50 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	sleeping(t_philo *philo)
{
	printf_action(philo, 3);
	if (ft_usleep_pro(philo, philo->time_to_sleep, 0) == 1)
		return (0);
	return (0);
}

static int	thinking(t_philo *philo)
{
	long	thinking;

	thinking = (philo->time_to_eat * 2) - philo->time_to_sleep;
	printf_action(philo, 2);
	if (thinking < 0)
		thinking = 0;
	if (philo->num_philos % 2 != 0)
		ft_usleep_pro(philo, thinking, 0);
	return (0);
}

static int	one_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork->mutex);
	if (am_i_dead(philo) == 1)
	{
		pthread_mutex_unlock(&philo->l_fork->mutex);
		return (0);
	}
	printf_action(philo, 1);
	pthread_mutex_unlock(&philo->l_fork->mutex);
	return (0);
}

static void	syncronize(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->m_start);
	pthread_mutex_unlock(&philo->table->m_start);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	syncronize(philo);
	if (philo->num_philos == 1)
		one_philo_routine(philo);
	else
	{
		if (philo->philo_id % 2 == 0)
			ft_usleep_pro(philo, philo->time_to_eat / 2, 0);
		while (am_i_dead(philo) == 0)
		{
			if (philo->meals_counter == philo->max_times_eat)
				break ;
			eating(philo);
			sleeping(philo);
			thinking(philo);
		}
	}
	return (0);
}
