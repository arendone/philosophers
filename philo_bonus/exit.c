/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arendon- <arendon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:23:19 by arendon-          #+#    #+#             */
/*   Updated: 2022/06/02 20:28:50 by arendon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
/**
 * @brief will correctly free the info struct and its contents
 * @note use funtion get_info
 * @retval None
 */
void	free_info(void)
{
	t_info	*info;

	info = get_info();
	free(info->print);
	sem_unlink("semaphore");
	sem_close(info->sem);
	sem_unlink("semaphore_dead");
	sem_close(info->sem_dead);
	free(info);
}

/**
 * @brief will correctly free the list of philos
 * @note philo->info was already freeded
 * @retval None
 */
void	free_philos(t_philo *head)
{
	t_philo	*tmp;
	t_philo	*next;
	t_philo	*last;

	tmp = NULL;
	last = head->prev;
	last->next = NULL;
	if (head->next == NULL)
	{
		free(tmp);
		return ;
	}
	tmp = head;
	next = tmp->next;
	while (tmp->next != NULL)
	{
		free(tmp);
		tmp = next;
		next = tmp->next;
	}
	free(tmp);
}
