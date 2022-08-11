/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 07:20:53 by eisikogl          #+#    #+#             */
/*   Updated: 2022/08/11 08:43:51 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

void init_philo(t_rules *rule, t_philo *philosophers)
{
    int i;
    
    i = rules->nb_philosophers;

    while (--i >= 0)
    {
        philosophers[i].id = i;
        philosophers[i].ate = 0;
        philosophers[i].l_fork_id = i;
        philosophers[i].r_fork_id = (i + 1) % rule->nb_philosophers;
        philosophers[i].last_meal = 0;
        philosophers[i].rules = rule;
    }
}

void init_rules(t_rules *rule, **argv)
{
    rule->nb_philosophers = ft_atoi(argv[1]);
    rule->time_to_die = ft_atoi(argv[2]);
    rule->time_eating = ft_atoi(argv[3]);
    rule->time_sleeping = ft_atoi(argv[4]);
}