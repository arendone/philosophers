/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watching.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arendon- <arendon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:11:53 by arendon-          #+#    #+#             */
/*   Updated: 2022/05/31 19:36:46 by arendon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*watching(void *head)
{
	t_info			*info;
	t_philo			*philo;
	int				num_philos;

	philo = (t_philo *)head;
	info = philo->info;
	num_philos = info->num_philo;
	while (1)
	{	
		if (kill_philo(info, philo) == 1)
		{
			usleep(1000);
			break ;
		}
		philo = philo->next;
		if (threads_finish(head, num_philos) == 1)
			break ;
	}
	return (NULL);
}

int	kill_philo(t_info *info, t_philo *philo)
{
	long	last_meal;
	int		time_to_die;

	last_meal = philo->last_meal;
	time_to_die = info->time_die;
	if (philo->status == is_thinking || philo->status == grabbed_fork
		|| philo->status == is_eating || philo->status == is_sleeping)
	{
		if ((get_time() - last_meal) > time_to_die)
		{
			pthread_mutex_lock(info->print);
			philo->status = is_dead;
			print_status(philo);
			return (1);
		}
	}
	return (0);
}

int	threads_finish(t_philo *head, int num_philos)
{
	t_philo	*current;
	int		i;

	i = 0;
	current = head;
	while (i < num_philos)
	{
		if (current->status != is_done)
			return (0);
		current = current->next;
		i++;
	}
	return (1);
}
