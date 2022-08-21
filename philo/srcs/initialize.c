/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 07:20:53 by eisikogl          #+#    #+#             */
/*   Updated: 2022/08/21 06:25:42 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_rules(t_rules *rule, char **argv)
{
	rule->ate_all_check = 0;
	rule->somone_died = 0;
	rule->ate_all = 0;
	rule->nb_philosophers = ft_atoi(argv[1]);
	rule->time_to_die = ft_atoi(argv[2]);
	rule->time_eating = ft_atoi(argv[3]);
	rule->time_sleeping = ft_atoi(argv[4]);
	if (rule->nb_philosophers < 2 || rule->time_to_die < 0 || \
	rule->time_eating < 0 || rule->time_sleeping < 0)
		return (1);
	if (argv[5])
	{
		rule->eat_this_much = ft_atoi(argv[5]);
		if (rule->eat_this_much <= 0)
			return (1);
	}
	else
		rule->eat_this_much = -1;
	return (0);
}

void	init_philo(t_rules *rule, t_philo *philosophers)
{
	int	i;

	i = rule->nb_philosophers;
	while (--i >= 0)
	{
		philosophers[i].id = i;
		philosophers[i].ate_this_much = 0;
		philosophers[i].l_fork_id = i;
		philosophers[i].r_fork_id = (i + 1) % rule->nb_philosophers;
		philosophers[i].t_last_meal = 0;
		philosophers[i].ate = 0;
		philosophers[i].rules = rule;
}
}

int	init_mutex(t_rules *rule)
{
	int	i;

	rule->forks = malloc(sizeof(pthread_mutex_t) * rule->nb_philosophers);
	i = 0;
	while (i < rule->nb_philosophers)
	{
		pthread_mutex_init(&rule->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&rule->writing, NULL);
	pthread_mutex_init(&rule->meal_check, NULL);
	return (0);
}

void	*threadHandler(void *philosophers)
{
	t_philo	*current_philo = (t_philo *)philosophers;

	if (current_philo->id % 2)
		usleep(15000);
	while (!(current_philo->rules->somone_died))
	{
		pick_up_left_fork(current_philo);
		if (current_philo->rules->nb_philosophers == 1)
		{
			pthread_mutex_unlock(&(current_philo->rules->forks[current_philo->l_fork_id]));
			break ;
		}
		pick_up_right_fork(current_philo);
		philo_eat(current_philo);
		put_down_forks(current_philo);
		check_eat(current_philo);
		if ((current_philo->rules->ate_all_check) == current_philo->rules->nb_philosophers)
		{
			current_philo->rules->ate_all = 1;
			break ;
		}
		exec_sleep(current_philo);
		exec_think(current_philo);
	}
	return (NULL);
}

int	death_check(t_philo *current_philo)
{
	if (current_philo->rules->nb_philosophers == 1)
		usleep((current_philo->rules->time_to_die) * 1000);
	if (time_diff(timestamp(),current_philo->t_last_meal) > current_philo->rules->time_to_die)
	{
		print_philo(current_philo->rules, current_philo->id, "died", 5);
		current_philo->rules->somone_died = 1;
		return (0);
	}
	return (1);
}

void	exit_launcher(t_rules *rules, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < rules->nb_philosophers)
		pthread_join(philo[i].thread_id, NULL);
	i = -1;
	while (++i < rules->nb_philosophers)
		pthread_mutex_destroy(&(rules->forks[i]));
	pthread_mutex_destroy(&(rules->writing));
	pthread_mutex_destroy(&(rules->meal_check));
	free(rules->forks);
	free(philo);
}

void	death_checker(t_rules *rules, t_philo *philsopers)
{
	int	i;

	while (!(rules->ate_all))
	{
		i = -1;
		while (++i < rules->nb_philosophers && !(rules->somone_died))
		{
			pthread_mutex_lock(&(rules->meal_check));
			if (time_diff(timestamp(), philsopers[i].t_last_meal) > \
			rules->time_to_die)
			{
				print_philo(rules, philsopers->id, "died", 5);
				rules->somone_died = 1;
			}
			pthread_mutex_unlock(&(rules->meal_check));
			usleep(100);
		}
		if (rules->somone_died)
			break ;
	}
}

int	create_threads(t_rules *rule, t_philo *philsopers)
{
	int	i;

	i = 0;
	rule->first_time = timestamp();
	while (i < rule->nb_philosophers)
	{
		pthread_create(&(philsopers[i].thread_id), NULL, \
		&threadHandler, &philsopers[i]);
		philsopers[i].t_last_meal = timestamp();
		i++;
	}
	death_checker(rule, philsopers);
	exit_launcher(rule, philsopers);
	return (0);
}
