/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/27 16:03:28 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/10 16:03:22 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

	time = get_current_time() - philo->simulation_start_time;
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
