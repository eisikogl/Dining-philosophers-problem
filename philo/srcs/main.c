/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:31:15 by eisikogl          #+#    #+#             */
/*   Updated: 2022/08/18 03:47:23 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

    // argv[1] == number_of_philosophers
    // argv[2] == time_to_die
    // argv[3] == time_to_eat
    // argv[4] == time_to_sleep
    // argv[5] == [number_of_times_each_philosopher_must_eat]

int main(int argc, char **argv)
{
	t_rules	rule;
	t_philo *philosophers;
    
    //do stuff
    if (argc == 5 || argc == 6)
    {
        init_rules(&rule, argv);
        philosophers = malloc(sizeof(t_philo) * rule.nb_philosophers);
        init_mutex(&rule);
        init_philo(&rule, philosophers);
        create_threads(&rule, philosophers);
        join_threads(&rule,philosophers);
    }
  
        // number_of_times_each_philosopher_must_eat
        // times, the simulation stops. If not specified, the simulation stops when a
        // philosopher dies.
}


// ◦ timestamp_in_ms X has taken a fork
// ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking
// ◦ timestamp_in_ms X died
// Replace timestamp_in_ms with the current timestamp in milliseconds
// and X with the philosopher number.
