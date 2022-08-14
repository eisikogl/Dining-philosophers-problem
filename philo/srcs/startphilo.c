/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startphilo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 18:16:13 by eisikogl          #+#    #+#             */
/*   Updated: 2022/08/14 05:13:41 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_eats(t_philo *philosopher)
{
	t_rules *rules;
	int i;
	
	rules = philosopher->rules;
	pthread_mutex_lock(&(rules->forks[philosopher->l_fork_id]));
    printf("%d has taken a left fork\n",philosopher->id);
	pthread_mutex_lock(&(rules->forks[philosopher->r_fork_id]));
	printf("%d has taken a right fork\n",philosopher->id);

	//eat function
	printf("%d is eating\n",philosopher->id);
	philosopher->ate++;
	pthread_mutex_unlock(&(rules->forks[philosopher->l_fork_id]));
	pthread_mutex_unlock(&(rules->forks[philosopher->r_fork_id]));
}

void	pick_up_left_fork(t_philo *current_philo)
{
	pthread_mutex_lock(&(current_philo->rules->forks[current_philo->l_fork_id]));
	print_philo(current_philo->rules,current_philo->id,"has taken fork");
}

void	pick_up_right_fork(t_philo *current_philo)
{
	pthread_mutex_lock(&(current_philo->rules->forks[current_philo->r_fork_id]));
	print_philo(current_philo->rules,current_philo->id,"has taken fork");
}

void	philo_eat(t_philo *current_philo)
{
	pthread_mutex_lock(&(current_philo->rules->meal_check));
	print_philo(current_philo->rules,current_philo->id,"is eating");
	current_philo->t_last_meal = timestamp();
	pthread_mutex_unlock(&(current_philo->rules->meal_check));
	smart_sleep(current_philo->rules->time_eating, NULL);
}

void put_down_forks(t_philo *current_philo)
{
	pthread_mutex_unlock(&(current_philo->rules->forks[current_philo->l_fork_id]));
	pthread_mutex_unlock(&(current_philo->rules->forks[current_philo->r_fork_id]));
}

void	exec_sleep(t_philo *current_philo)
{
	print_philo(current_philo->rules,current_philo->id,"is sleeping");
	smart_sleep(current_philo->rules->time_sleeping, NULL);
}

void	exec_think(t_philo *current_philo)
{
	print_philo(current_philo->rules,current_philo->id,"is thinking");
}