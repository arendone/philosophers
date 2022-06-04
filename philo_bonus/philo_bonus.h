/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arendon- <arendon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:37:07 by arendon-          #+#    #+#             */
/*   Updated: 2022/06/02 20:54:07 by arendon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <signal.h>

typedef enum e_status
{
	is_sitting = 0,
	is_eating = 1,
	grabbed_fork = 2,
	is_sleeping = 3,
	is_thinking = 4,
	is_dead = 5,
	is_done = 6,
}	t_status;

typedef struct s_info
{
	long			start_time;
	int				num_philo;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int				meals;
	sem_t			*sem;
	unsigned int	sem_value;
	sem_t			*sem_dead;
	unsigned int	sem_value_dead;
	pthread_mutex_t	*print;
}	t_info;

typedef struct s_philo
{
	int				seat;
	enum e_status	status;
	int				meals;
	long			last_meal;
	struct s_philo	*next;
	struct s_philo	*prev;
	t_info			*info;
}	t_philo;

/* Read arguments in read_arg.c */
int		philo_atoi(const char *str);
long	philo_long_atoi(const char *str);
bool	read_arg(char **argv, t_info *info);

/* info.c*/
t_info	*set_info(char **argv);
void	semaphores(t_info	*info);
t_info	*get_info(void);

/* create philos in memory_philos.c*/
t_philo	*create_philo(int seat);
void	join_philo(t_philo *head, t_philo *current);
t_philo	*get_current_philo(t_philo *head, int i);

/* sit_philos.c */
t_philo	*sit_philos(int num_philos);
t_philo	*create_philos(int num_philos);
int		init_philos(t_philo *head, int num_philos);
void	run_philo(t_philo *head, int seat);
void	run_god(pid_t pid, int *pids, int num_philos);

/* Utils in utils.c*/
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		print_error(int type);
void	print_status(t_philo *philo);
void	print_philos(t_philo *head);

/* time.c */
long	get_time(void);
void	my_usleep(long desire_time);

/* Functions of sleeping, eating or thinking in routine.c*/
//void	*routine(void *current);
void	*routine(t_philo *current);
int		r_grabbed_fork(t_info *info, t_philo *philo, int num);
int		r_eating(t_info *info, t_philo *philo);
int		r_sleeping(t_info *info, t_philo *philo);//, t_philo *left_philo);
int		r_thinking(t_info *info, t_philo *philo);

/* Functions of the thread "eyes" to check if a philo died in watching.c */
void	*watching(void *head);
int		kill_philo(t_info *info, t_philo *philo);
//int		threads_finish(t_philo *head, int num_philos);

/* Exit in exit.c */
void	free_info(void);
void	free_philos(t_philo *head);

#endif