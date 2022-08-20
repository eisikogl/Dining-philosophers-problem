/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:31:34 by eisikogl          #+#    #+#             */
/*   Updated: 2022/08/20 03:06:37 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

typedef struct s_rules
{
	int	                nb_philosophers;
    int                 time_eating;
    int                 time_sleeping;
    int                 time_thinking;
    int                 time_to_die;
    int                 eat_this_much;
    long long           first_time;
    int                 ate_all;
    int                 ate_all_check;
    int                 somone_died;
    pthread_mutex_t		*forks;
    pthread_mutex_t     meal_check;
    pthread_mutex_t		writing;
} t_rules;

typedef struct s_philo
{
   int				id;
   int				l_fork_id;
   int				r_fork_id;
   int				ate_this_much;
   int              ate;
   long long		t_last_meal;
   struct s_rules	*rules;
   pthread_t		thread_id;
} t_philo;

void	philo_eats(t_philo *philosopher);
int ft_atoi(char *str);
void init_philo(t_rules *rule, t_philo *philosophers);
int init_rules(t_rules *rule,char **argv);
void    *threadHandler(void *philosophers);
int create_threads(t_rules *rule, t_philo *philsopers);
int	init_mutex(t_rules *rule);
long long	timestamp(void);
int	time_diff(long long past, long long pres);

void	pick_up_right_fork(t_philo *current_philo);
void	pick_up_left_fork(t_philo *current_philo);
void	philo_eat(t_philo *current_philo);
void    put_down_forks(t_philo *current_philo);
void	exec_sleep(t_philo *current_philo);
void	exec_think(t_philo *current_philo);
void		smart_sleep(long long time, t_philo *philo);
void	print_philo(t_rules *rules, int id, char *string,int color);
void death_checker(t_rules *rules, t_philo *current_philo);
int	check_all_ate(t_philo *philosopher);
void	exit_launcher(t_rules *rules, t_philo *philo);
void	join_threads(t_rules *rules, t_philo *philo);
void	check_eat(t_philo *current_philo);
int errorcheck(int argc,char **argv);

//Color output
void pick_color(int color);
void red();
void yellow();
void green();
void blue();
void purple();
void reset();

# endif
