/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eating.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/03 11:35:48 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/10 15:34:54 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_forks_even(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork->mutex);
	printf_action(philo, 1);
	pthread_mutex_lock(&philo->r_fork->mutex);
	printf_action(philo, 1);
	return (0);
}

static int	take_forks_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork->mutex);
	printf_action(philo, 1);
	pthread_mutex_lock(&philo->l_fork->mutex);
	printf_action(philo, 1);
	return (0);
}

int	eating(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
		take_forks_even(philo);
	if (philo->philo_id % 2 != 0)
		take_forks_odd(philo);
	printf_action(philo, 4);
	pthread_mutex_lock(&philo->m_meals);
	philo->meals_counter++;
	pthread_mutex_unlock(&philo->m_meals);
	if (ft_usleep_pro(philo, philo->time_to_eat, 1) == 1)
		return (0);
	pthread_mutex_unlock(&philo->r_fork->mutex);
	pthread_mutex_unlock(&philo->l_fork->mutex);
	return (0);
}
