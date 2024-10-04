/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/03 15:00:21 by sramos        #+#    #+#                 */
/*   Updated: 2024/10/03 20:15:13 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(char c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	valid_input(char *argv)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	if (argv[i] == '0' || argv[i] == '\0')
		return (ft_print_error("Invalid input"));
	while (argv[i])
	{
		if (!ft_isdigit(argv[i]))
			return (ft_print_error("Invalid input"));
		i++;
	}
	i = 0;
	while (ft_isdigit(argv[i]))
	{
		res = res * 10 + (argv[i] - '0');
		i++;
	}
	if (res > INT_MAX)
		return (ft_print_error("Invalid input. Max limit."));
	return (0);
}

int	ft_atol(char *argv)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while (ft_isspace(argv[i]))
		i++;
	if (argv[i] == '+')
		i++;
	while (ft_isdigit(argv[i]))
	{
		res = res * 10 + (argv[i] - '0');
		i++;
	}
	return (res);
}

int	parsing(t_table *table, char *argv[])
{
	if (valid_input(argv[1]) == 1 || valid_input(argv[2]) == 1
		|| valid_input(argv[3]) == 1 || valid_input(argv[4]) == 1)
		return (1);
	if (ft_atol(argv[1]) > 200)
	{
		printf("Max number of philosophers: 200\n");
		return (1);
	}
	table->num_philos = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
	{
		if (valid_input(argv[5]) == 0)
			table->max_times_eat = ft_atol(argv[5]);
		else
			return (1);
	}
	if (!argv[5])
		table->max_times_eat = -1;
	return (0);
}
