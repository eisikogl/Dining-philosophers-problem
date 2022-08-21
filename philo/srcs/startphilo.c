/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startphilo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 18:16:13 by eisikogl          #+#    #+#             */
/*   Updated: 2022/08/21 06:28:09 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	pick_up_left_fork(t_philo *current_philo)
{
	pthread_mutex_lock(&(current_philo->rules->forks[current_philo->l_fork_id]));
	print_philo(current_philo->rules, current_philo->id, "has taken fork", 2);
}

void	pick_up_right_fork(t_philo *current_philo)
{
	pthread_mutex_lock(&(current_philo->rules->forks[current_philo->r_fork_id]));
	print_philo(current_philo->rules, current_philo->id, "has taken fork", 2);
}

void	philo_eat(t_philo *current_philo)
{
	pthread_mutex_lock(&(current_philo->rules->meal_check));
	print_philo(current_philo->rules, current_philo->id, "is eating", 1);
	current_philo->t_last_meal = timestamp();
	current_philo->ate_this_much++;
	pthread_mutex_unlock(&(current_philo->rules->meal_check));
	smart_sleep(current_philo->rules->time_eating, current_philo);
}

void put_down_forks(t_philo *current_philo)
{
	pthread_mutex_unlock(&(current_philo->rules->forks[current_philo->l_fork_id]));
	pthread_mutex_unlock(&(current_philo->rules->forks[current_philo->r_fork_id]));
}

void	exec_sleep(t_philo *current_philo)
{
	print_philo(current_philo->rules, current_philo->id, "is sleeping", 3);
	smart_sleep(current_philo->rules->time_sleeping, current_philo);
}

void	exec_think(t_philo *current_philo)
{
	print_philo(current_philo->rules, current_philo->id, "is thinking", 4);
}

void	check_eat(t_philo *current_philo)
{
	pthread_mutex_lock(&current_philo->rules->meal_check);
	if ((current_philo->rules->eat_this_much <= current_philo->ate_this_much) &&\
	!(current_philo->ate) && current_philo->rules->eat_this_much != -1 )
	{
		current_philo->rules->ate_all_check++;
		current_philo->ate = 1;
	}
	pthread_mutex_unlock(&current_philo->rules->meal_check);
}

int	check_all_ate(t_philo *philosopher)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (philosopher->rules->eat_this_much == -1)
		return (1);
	while (j < philosopher->rules->nb_philosophers)
	{
		if (philosopher->rules->eat_this_much <= philosopher[j].ate_this_much)
			i++;
		j++;
	}
	if (i == philosopher->rules->nb_philosophers)
	{
		philosopher->rules->somone_died = 1;
		philosopher->rules->ate_all = 1;
		return (0);
	}
	return (1);
}