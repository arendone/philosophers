/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arendon- <arendon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:57:20 by arendon-          #+#    #+#             */
/*   Updated: 2022/06/01 17:52:08 by arendon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief  calculates the current timestamp in milliseconds
 * @note   uses gettimeofday
 * @retval timeofday in milliseconds
 */
long	get_time(void)
{
	long			time_mls;
	struct timeval	te;

	gettimeofday(&te, NULL);
	time_mls = (te.tv_sec * 1000);
	time_mls += (te.tv_usec / 1000);
	return (time_mls);
}

/**
 * @brief  use the funtion usleep in intervales of 100 milliseconds
 * @note   helps the program with the delay
 * @param  desire_time time until you want the thread to sleep
 * @retval none
 */
void	my_usleep(long desire_time)
{
	long	current_time;

	current_time = get_time();
	while (desire_time - current_time > 0)
	{
		usleep(100);
		current_time = get_time();
	}
}
