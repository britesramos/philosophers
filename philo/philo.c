/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/26 11:45:14 by sramos        #+#    #+#                 */
/*   Updated: 2024/10/01 17:37:17 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		if (parsing(&table, argv) == 1)
			return (1);
		if (init_program(&table) == 1)
		{
			end_program(&table);
			return (1);
		}
		if (start_simulation(&table) == 1)
		{
			end_program(&table);
			return (1);
		}
		end_program(&table);
	}
	else
	{
		printf("Please provide a correct input.\n"
			"Like this: ./philo 5 800 200 200 [last input optional]");
		return (1);
	}
	return (0);
}
