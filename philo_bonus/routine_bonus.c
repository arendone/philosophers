/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arendon- <arendon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:49:11 by arendon-          #+#    #+#             */
/*   Updated: 2022/06/03 17:39:21 by arendon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief  simulation of the routine of the philos
 * @note   calls r_sleeping, r_thinking, r_grabbed_fork
 * @param  current pointer to struct with rhe information of every philo
 * @retval NULL
 */
void	*routine(t_philo *current)
{
	current->last_meal = get_time();
	if (current->seat % 2 == 0)
		usleep(900);
	else if (current->seat != 1 && current->seat == (current->info->num_philo))
		usleep(1800);
	while (1)
	{	
		if (current->info->num_philo == 1)
			r_grabbed_fork(current->info, current, 1);
		sem_wait(current->info->sem);
		r_grabbed_fork(current->info, current, 2);
		if (r_eating(current->info, current) == 1)
		{
			exit (0);
		}
		sem_post(current->info->sem);
		r_sleeping(current->info, current);
		r_thinking(current->info, current);
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

int	r_eating(t_info *info, t_philo *philo)
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
		sem_post(philo->info->sem);
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
	return (0);
}
