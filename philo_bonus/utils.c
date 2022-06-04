/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arendon- <arendon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:41:30 by arendon-          #+#    #+#             */
/*   Updated: 2022/06/04 16:22:05 by arendon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief  ft_memset of libft (but static)
 * @param  s: the pointer whose values to set
 * @param  c: the ascii to set it to (converted to an unsigned char)
 * @param  n: the number of characters to set
 * @retval its first argument
 */
void	*ft_memset(void *s, int c, size_t n)
{
	char	*buf;

	buf = s;
	while (n > 0)
	{
		*buf = c;
		buf++;
		n--;
	}
	return (s);
}

/**
 * @brief  ft_calloc of libft
 * @param  count: number of elements
 * @param  size: the size of each element
 * @retval the pointer to the allocated memory or NULL if allocation failed
 */
void	*ft_calloc(size_t count, size_t size)
{
	void	*pr;

	pr = malloc(count * size);
	if (pr == NULL)
		return (NULL);
	return (ft_memset(pr, 0, (count * size)));
}

/**
 * @brief  print instruccions
 * @note   with colors
 * @param  type: defines the error message
 * @retval only exists to save some lines
 */
int	print_error(int type)
{
	if (type == 1)
		printf("Wrong input!\n");
	if (type == 2)
		printf("Only positive integers as input allowed\n");
	printf("Please use like: ' \033[0;37m./philo\033[0;31m a \033[0;32m b\
	\033[0;33m c \033[0;34m d \033[0;35m e \033[0;37m'\
	\n\033[0;31ma = [number_of_philosophers]\n\033[0;32mb = [time_to_die]\
	\n\033[0;33mc = [time_to_eat]\n\033[0;34md = [time_to_sleep]\
	\n\033[0;35me = [number_of_times_each_philosopher_must_eat]\
	\n\033[0;37m*Every value but \033[0;35me\033[0;37m is mandatory.\n");
	return (EXIT_FAILURE);
}

/**
 * @brief  print status of the philo
 * @note   in current time
 * @param  philo: pointer to the struct with all the information of the philo
 * @retval none
 */
void	print_status(t_philo *philo)
{
	long	start_time;

	sem_wait(philo->info->sem_dead);
	start_time = philo->info->start_time;
	if (philo->status == grabbed_fork)
		printf("%lu %d has taken a fork\n", get_time()
			- start_time, philo->seat);
	else if (philo->status == is_eating)
		printf("%lu %d is eating\n", get_time() - start_time, philo->seat);
	else if (philo->status == is_sleeping)
		printf("%lu %d is sleeping\n", get_time() - start_time, philo->seat);
	else if (philo->status == is_thinking)
		printf("%lu %d is thinking\n", get_time() - start_time, philo->seat);
	else if (philo->status == is_dead)
		printf("%lu %d died\n", get_time() - start_time, philo->seat);
	if (philo->status != is_dead)
		sem_post(philo->info->sem_dead);
}

/**
 * @brief  it was made as a tool of testing
 */
void	print_philos(t_philo *head)
{
	t_philo	*tmp;
	t_philo	*next;

	tmp = head;
	if (tmp->next == head)
	{
		printf("Solo hay un philo en sit %d\n", tmp->seat);
		return ;
	}
	next = tmp->next;
	while (next != head)
	{
		printf("philo in seat: %d\n", tmp->seat);
		tmp = next;
		next = tmp->next;
	}
	printf("philo in seat: %d\n", tmp->seat);
}
