/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:31:34 by eisikogl          #+#    #+#             */
/*   Updated: 2022/08/11 08:55:52 by eisikogl         ###   ########.fr       */
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

typedef struct s_philo
{
   int				id;
   int				l_fork_id;
   int				r_fork_id;
   int				ate;
   long long		last_meal;
   struct s_rules	*rules;
   pthread_t		thread_id;
   
} t_philo;

typedef struct s_rules
{
	int	                nb_philosophers;
    int                 time_eating;
    int                 time_sleeping;
    int                 time_thinking;
    int                 time_to_die;
    int                 eatthismuch;
} t_rules;


# endif
