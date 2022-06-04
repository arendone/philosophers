/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watching.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arendon- <arendon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:11:53 by arendon-          #+#    #+#             */
/*   Updated: 2022/06/04 16:22:27 by arendon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*watching(void *current)
{
	t_info			*info;
	t_philo			*philo;
	int				num_philos;

	philo = (t_philo *)current;
	info = philo->info;
	num_philos = info->num_philo;
	while (1)
	{	
		if (kill_philo(info, philo) == 1)
		{
			exit (2);
		}
		philo = philo->next;
	}
	return (NULL);
}

int	kill_philo(t_info *info, t_philo *philo)
{
	long	last_meal;
	int		time_to_die;
	pid_t	pid;

	pid = getpid();
	last_meal = philo->last_meal;
	time_to_die = info->time_die;
	if (philo->status == is_thinking || philo->status == grabbed_fork
		|| philo->status == is_eating || philo->status == is_sleeping)
	{
		if ((get_time() - last_meal) > time_to_die)
		{
			philo->status = is_dead;
			pthread_mutex_lock(info->print);
			print_status(philo);
			pthread_mutex_unlock(info->print);
			exit (2);
		}
	}
	return (0);
}
