/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sit_philos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arendon- <arendon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:57:29 by arendon-          #+#    #+#             */
/*   Updated: 2022/06/03 17:18:59 by arendon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*sit_philos(int num_philos)
{
	t_philo		*head;

	head = create_philos(num_philos);
	if (head == NULL)
		return (NULL);
	if (init_philos(head, num_philos) != 0)
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

int	init_philos(t_philo *head, int num_philos)
{
	int			i;
	pid_t		pid;
	pid_t		*pids;

	i = 0;
	pids = malloc(sizeof(pid_t) * num_philos);
	head->info->start_time = get_time();
	while (i < num_philos)
	{
		pid = fork();
		if (pid != 0)
			pids[i] = pid;
		if (pid < 0)
			return (1);
		else if (pid == 0)
			break ;
		i++;
	}
	if (pid == 0)
		run_philo(head, i + 1);
	else if (pid > 0)
		run_god(pid, pids, num_philos);
	free(pids);
	usleep(500);
	return (0);
}

void	run_philo(t_philo *head, int seat)
{
	pthread_t	eyes;
	t_philo		*current;

	current = get_current_philo(head, seat);
	if (pthread_create(&(eyes), NULL, &watching, (void *)current) != 0)
	{
		printf ("EYES: Pthread_create failed.\n");
		exit(EXIT_FAILURE);
	}
	routine(current);
	if (pthread_detach(eyes) != 0)
	{
		printf ("Pthread_join failed.\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

void	run_god(pid_t pid, int *pids, int num_philos)
{
	int	child_state;
	int	k;

	k = 0;
	while (1)
	{
		pid = waitpid(0, &child_state, 0);
		if (pid == -1)
			break ;
		if (WIFEXITED(child_state))
		{
			if (WEXITSTATUS(child_state) == 2)
			{
				while (k < num_philos)
				{
					if (pids[k] != 0)
						kill(pids[k], 2);
					k++;
				}
				break ;
			}
		}
	}
}
