/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:31:15 by eisikogl          #+#    #+#             */
/*   Updated: 2022/08/21 06:02:54 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_rules	rule;
	t_philo	*philosophers;

	if (!errorcheck(argc, argv))
	{
		init_rules(&rule, argv);
		philosophers = malloc(sizeof(t_philo) * rule.nb_philosophers);
		init_mutex(&rule);
		init_philo(&rule, philosophers);
		create_threads(&rule, philosophers);
	}
	return (0);
}
