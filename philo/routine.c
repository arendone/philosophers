/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arendon- <arendon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:49:11 by arendon-          #+#    #+#             */
/*   Updated: 2022/06/01 18:47:46 by arendon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief  main funtion of the threads
 * @note   calls r_sleeping, r_thinking, r_grabbed_fork
 * @param  current pointer to struct with rhe information of every philo
 * @retval NULL
 */
void	*routine(void *current)
{
	t_philo			*philo;
	t_philo			*left_philo;

	philo = (t_philo *)current;
	left_philo = philo->prev;
	philo->last_meal = get_time();
	if (philo->seat % 2 == 0)
		usleep(900);
	else if (philo->seat != 1 && philo->seat == (philo->info->num_philo))
		usleep(1800);
	while (1)
	{	
		if (philo->info->num_philo == 1)
			r_grabbed_fork(philo->info, philo, 1);
		pthread_mutex_lock(philo->fork);
		pthread_mutex_lock(left_philo->fork);
		r_grabbed_fork(philo->info, philo, 2);
		if (r_eating(philo->info, philo, left_philo) == 1)
			return (NULL);
		pthread_mutex_unlock(left_philo->fork);
		pthread_mutex_unlock(philo->fork);
		r_sleeping(philo->info, philo);
		r_thinking(philo->info, philo);
	}
	return (NULL);
}

int	r_grabbed_fork(t_info *info, t_philo *philo, int num)
{
	philo->status = grabbed_fork;
	pthread_mutex_lock(info->print);
	print_status(philo);
	pthread_mutex_unlock(info->print);
	if (num == 2)
	{
		pthread_mutex_lock(info->print);
		print_status(philo);
		pthread_mutex_unlock(info->print);
	}
	return (0);
}

int	r_eating(t_info *info, t_philo *philo, t_philo *left_philo)
{
	long	current_time;

	current_time = get_time() + (info->time_eat);
	philo->status = is_eating;
	philo->last_meal = get_time();
	philo->meals++;
	pthread_mutex_lock(info->print);
	print_status(philo);
	pthread_mutex_unlock(info->print);
	pthread_mutex_lock(info->print);
	if (info->meals != 0 && philo->meals == info->meals)
	{
		philo->status = is_done;
		pthread_mutex_unlock(info->print);
		pthread_mutex_unlock(left_philo->fork);
		pthread_mutex_unlock(philo->fork);
		return (1);
	}
	pthread_mutex_unlock(info->print);
	my_usleep(current_time);
	return (0);
}

int	r_sleeping(t_info *info, t_philo *philo)
{
	long	current_time;

	current_time = get_time() + (info->time_sleep);
	philo->status = is_sleeping;
	pthread_mutex_lock(info->print);
	print_status(philo);
	pthread_mutex_unlock(info->print);
	my_usleep(current_time);
	return (0);
}

int	r_thinking(t_info *info, t_philo *philo)
{
	philo->status = is_thinking;
	pthread_mutex_lock(info->print);
	print_status(philo);
	pthread_mutex_unlock(info->print);
	usleep(500);
	return (0);
}
