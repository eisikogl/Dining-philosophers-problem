/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 07:20:53 by eisikogl          #+#    #+#             */
/*   Updated: 2022/08/14 05:30:07 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"


int init_rules(t_rules *rule,char **argv)
{
    rule->nb_philosophers = ft_atoi(argv[1]);
    rule->time_to_die = ft_atoi(argv[2]);
    rule->time_eating = ft_atoi(argv[3]);
    rule->time_sleeping = ft_atoi(argv[4]);
    if (rule->nb_philosophers < 2 || rule->time_to_die < 0 || \
    rule->time_eating < 0 || rule->time_sleeping < 0)
        return (1);
    if(argv[5])
    {
       rule->eatthismuch = ft_atoi(argv[5]);
       if (rule->eatthismuch <= 0)
            return (1);
    }
    else
        rule->eatthismuch = -1;
	return (0);
}

void init_philo(t_rules *rule, t_philo *philosophers)
{
    int i;
    
    i = rule->nb_philosophers;

    while (--i >= 0)
    {
        philosophers[i].id = i;
        philosophers[i].ate = 0;
        philosophers[i].l_fork_id = i;
        philosophers[i].r_fork_id = (i + 1) % rule->nb_philosophers;
        philosophers[i].t_last_meal = 0;
        philosophers[i].rules = rule;
    }
}

int	init_mutex(t_rules *rule)
{
	size_t	i;
 
	rule->forks = malloc(sizeof(pthread_mutex_t) * rule->nb_philosophers);
	i = 0;
	while (i < rule->nb_philosophers)
	{
		pthread_mutex_init(&rule->forks[i], NULL);
        i++;
	}
    pthread_mutex_init(&rule->writing, NULL);
    pthread_mutex_init(&rule->meal_check,NULL);
	return (0);
}

void    *threadHandler(void *philosophers)
{
    t_philo *current_philo = (t_philo *)philosophers;
    //eat
    //sleep after eat
    //think till eating
    //die if u dont eat sleep+think
    if (current_philo->id % 2)
		usleep(15000);
    while(death_check(current_philo))
    {
        pick_up_left_fork(current_philo);
        pick_up_right_fork(current_philo);
        philo_eat(current_philo);
        put_down_forks(current_philo);
        exec_sleep(current_philo);
        exec_think(current_philo);
    }

    return NULL;
}

int death_check(t_philo *current_philo)
{
    if(time_diff(timestamp(),current_philo->t_last_meal) >= current_philo->rules->time_to_die)
    {
        print_philo(current_philo->rules, current_philo->id,"died");
        
        return 0;
    }
    return 1;
}

void create_threads(t_rules *rule, t_philo *philsopers)
{
    int i;

    i = 0;

    rule->first_time = timestamp();
    while(i < rule->nb_philosophers)
    {
        pthread_create(&(philsopers[i].thread_id), NULL, &threadHandler, &philsopers[i]);
        philsopers[i].t_last_meal = timestamp();
        i++;
    }
}
