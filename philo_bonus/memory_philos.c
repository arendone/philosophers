/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arendon- <arendon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 11:52:43 by arendon-          #+#    #+#             */
/*   Updated: 2022/06/02 20:43:58 by arendon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*create_philo(int seat)
{
	t_philo	*philo;

	philo = (t_philo *)ft_calloc(1, sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	philo->seat = seat;
	philo->status = is_sitting;
	philo->meals = 0;
	philo->last_meal = 0;
	philo->next = philo;
	philo->prev = philo;
	philo->info = get_info();
	return (philo);
}

void	join_philo(t_philo *head, t_philo *current)
{
	t_philo	*tmp;
	t_philo	*last;

	last = NULL;
	if (head == NULL)
		return ;
	tmp = head;
	last = (tmp->next);
	while ((last->next) != head)
	{
		tmp = last;
		last = tmp->next;
	}
	head->prev = current;
	last->next = current;
	current->prev = last;
	current->next = head;
}

t_philo	*get_current_philo(t_philo *head, int i)
{
	t_philo	*current;

	current = head;
	while (i > 1)
	{
		current = current->next;
		i--;
	}
	return (current);
}
