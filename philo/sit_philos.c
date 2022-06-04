/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sit_philos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arendon- <arendon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:57:29 by arendon-          #+#    #+#             */
/*   Updated: 2022/06/01 17:47:47 by arendon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*sit_philos(int num_philos)
{
	t_philo		*head;
	pthread_t	eyes;

	head = create_philos(num_philos);
	if (head == NULL)
		return (NULL);
	if (pthread_create(&(eyes), NULL, &watching, (void *)head) != 0)
	{
		printf ("EYES: Pthread_create failed.\n");
		free_philos(head);
		return (NULL);
	}
	if (init_threads(head, eyes, num_philos) == NULL)
	{
		free_philos(head);
		return (NULL);
	}
	return (head);
}

t_philo	*create_philos(int num_philos)
{
	int			i;
	t_philo		*head;
	t_philo		*current;

	head = create_philo(1);
	if (head == NULL)
		return (NULL);
	i = 1;
	while (i < num_philos)
	{
		current = create_philo(i + 1);
		if (current == NULL)
		{
			free_philos(head);
			return (NULL);
		}
		join_philo(head, current);
		i++;
	}
	return (head);
}

int	crete_threads(t_philo	*head, int num_philos)
{
	t_philo	*current;
	int		i;

	i = 0;
	current = head;
	while (i < num_philos)
	{
		if (pthread_create(&(current->philo), NULL,
				&routine, (void *)current) != 0)
		{
			printf ("Pthread_create failed.\n");
			return (EXIT_FAILURE);
		}
		current = current->next;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	philos_detach(t_philo	*head, int num_philos)
{
	t_philo	*current;
	int		i;

	i = 0;
	current = head;
	while (i < num_philos)
	{
		pthread_detach(current->philo);
		current = current->next;
		i++;
	}
	return (EXIT_SUCCESS);
}

t_philo	*init_threads(t_philo *head, pthread_t eyes, int num_philos)
{
	if (crete_threads(head, num_philos) != 0)
	{
		printf ("Create_threads failed.\n");
		return (NULL);
	}
	head->info->start_time = get_time();
	if (pthread_join(eyes, NULL) != 0)
	{
		printf ("Pthread_join failed.\n");
		return (NULL);
	}
	if (philos_detach(head, num_philos) != 0)
	{
		printf ("philos_detach failed.\n");
		return (NULL);
	}
	return (head);
}
