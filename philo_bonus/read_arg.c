/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arendon- <arendon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:30:16 by arendon-          #+#    #+#             */
/*   Updated: 2022/06/01 17:42:28 by arendon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief  ft_atoi with small modificacions
 * @note checks if there is only digits
 * @param  *str: argv[i] from main
 * @retval 0 if is not a interger or it is 0... or the interger
 */
int	philo_atoi(const char *str)
{
	int		n;
	int		i;
	int		sign;

	n = 0;
	i = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			n = n * 10 + (str[i] - '0');
			i++;
		}
		else
			return (0);
	}
	return (sign * n);
}

/**
 * @brief  philo_atoi with small modificacions
 * @note for long intergers
 * @param  *str: argv[i] from main
 * @retval 0 if is not a interger or it is 0... or the interger
 */
long	philo_long_atoi(const char *str)
{
	long	n;
	int		i;
	int		sign;

	n = 0;
	i = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			n = n * 10 + (str[i] - '0');
			i++;
		}
		else
			return (0);
	}
	return (sign * n);
}

/**
 * @brief  checks if argv has only integers
 * @note int & long 
 * @param  **argv: argv from main
 * @retval true if only numbers were found, false if not
 */
bool	read_arg(char **argv, t_info *info)
{
	info->num_philo = philo_atoi(argv[1]);
	info->time_die = philo_long_atoi(argv[2]);
	info->time_eat = philo_long_atoi(argv[3]);
	info->time_sleep = philo_long_atoi(argv[4]);
	if (argv[5])
	{
		info->meals = philo_atoi(argv[5]);
		if (info->meals < 1)
		{
			return (false);
		}
	}	
	if (info->num_philo < 1 || info->time_die < 1 || info->time_eat < 1
		|| info->time_sleep < 1)
		return (false);
	return (true);
}
