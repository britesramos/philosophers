/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/27 16:03:28 by sramos        #+#    #+#                 */
/*   Updated: 2024/10/04 16:30:20 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	printf_action(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->m_dead);
	if (philo->i_am_dead == 1)
	{
		pthread_mutex_unlock(&philo->m_dead);
		return (1);
	}
	if (i == 1)
		printf("%ld %i has taken a fork\n", get_time(philo), philo->philo_id);
	if (i == 2)
		printf("%ld %i is thinking\n", get_time(philo), philo->philo_id);
	if (i == 3)
		printf ("%ld %i is sleeping\n", get_time(philo), philo->philo_id);
	if (i == 4)
	{
		pthread_mutex_lock(&philo->m_last_meal_time);
		philo->last_meal_time = get_current_time();
		pthread_mutex_unlock(&philo->m_last_meal_time);
		printf ("%ld %i is eating\n", get_time(philo), philo->philo_id);
	}
	pthread_mutex_unlock(&philo->m_dead);
	return (0);
}

int	am_i_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_dead);
	if (philo->i_am_dead == 1)
	{
		pthread_mutex_unlock(&philo->m_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->m_dead);
	return (0);
}

long	get_current_time(void)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) != 0)
		printf("Error on gettimeofday!\n");
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

long	get_time(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->table->m_start);
	time = get_current_time() - philo->table->simulation_start_time;
	pthread_mutex_unlock(&philo->table->m_start);
	return (time);
}

int	ft_usleep_pro(t_philo *philo, long time_to_sleep, int eat)
{
	long	start_time;

	start_time = get_current_time();
	while (get_current_time() - start_time < time_to_sleep)
	{
		pthread_mutex_lock(&philo->m_dead);
		if (philo->i_am_dead == true)
		{
			if (eat == 1)
			{
				pthread_mutex_unlock(&philo->l_fork->mutex);
				pthread_mutex_unlock(&philo->r_fork->mutex);
			}
			pthread_mutex_unlock(&philo->m_dead);
			return (1);
		}
		pthread_mutex_unlock(&philo->m_dead);
		usleep(500);
	}
	return (0);
}
