/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arendon- <arendon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:39:04 by arendon-          #+#    #+#             */
/*   Updated: 2022/06/03 16:52:33 by arendon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_info			*info;
	t_philo			*head;

	info = NULL;
	if (!(argc == 5 || argc == 6))
		return (print_error(1));
	info = set_info(argv);
	if (info == NULL)
		return (EXIT_FAILURE);
	head = sit_philos(info->num_philo);
	if (head == NULL)
	{
		free_info();
		printf("Failed create philosophers\n");
		return (EXIT_FAILURE);
	}
	free_info();
	free_philos(head);
	return (EXIT_SUCCESS);
}
