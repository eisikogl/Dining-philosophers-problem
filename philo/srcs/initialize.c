/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 07:20:53 by eisikogl          #+#    #+#             */
/*   Updated: 2022/08/13 01:42:17 by eisikogl         ###   ########.fr       */
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
    return 0;
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
        philosophers[i].last_meal = 0;
        philosophers[i].rules = *rule;
    }
}

void    *threadHandler(void *philosophers)
{
    t_philo *current_philo = (t_philo *)philosophers;
    printf("time_stamp %d %d eating\n", 0, current_philo->id);
    return (0);
}

void create_threads(t_rules *rule, t_philo *philsopers)
{
    int i;

    i = 0;

    while(i < rule->nb_philosophers)
    {
        pthread_create(&(philsopers[i].thread_id), NULL, &threadHandler, &philsopers[i]);
        i++;
    }
}
