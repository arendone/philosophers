/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arendon- <arendon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:55:54 by arendon-          #+#    #+#             */
/*   Updated: 2022/06/02 22:08:56 by arendon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief  sets the info struct from reading argv
 * @note   the *info is a static and can be accessed by set_info(NULL);
 * @param  **argv: the argv from main
 * @retval pointer to the info struct or NULL if allocation failed
 */
t_info	*set_info(char **argv)
{
	static t_info	*info;

	if (argv == NULL)
		return (info);
	info = ft_calloc(1, sizeof(t_info));
	if (info == NULL)
		return (NULL);
	info->meals = 0;
	if (read_arg(argv, info) == false)
	{
		print_error(2);
		free_info();
		return (NULL);
	}
	info->print = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	if (info->print == NULL)
	{
		free_info();
		return (NULL);
	}
	pthread_mutex_init(info->print, NULL);
	semaphores(info);
	return (info);
}

void	semaphores(t_info	*info)
{
	sem_unlink("semaphore");
	sem_unlink("semaphore_dead");
	info->sem_value = (info->num_philo / 2);
	info->sem = sem_open("semaphore", O_CREAT | O_EXCL, 0600, info->sem_value);
	info->sem_value_dead = 1;
	info->sem_dead = sem_open("semaphore_dead", O_CREAT | O_EXCL, 0600,
			info->sem_value_dead);
}

/**
 * @brief  is made to have access to struct info
 * @retval pointer to struct info
 */
t_info	*get_info(void)
{
	t_info	*info;

	info = set_info(NULL);
	return (info);
}
