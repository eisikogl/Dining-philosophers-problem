/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 02:33:21 by eisikogl          #+#    #+#             */
/*   Updated: 2022/08/20 03:06:04 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

void errorhandler(int exit_mode)
{
    if(exit_mode == 1)
        printf("Wrong number of Arguments\n");
    if(exit_mode == 2)
        printf("There has to be atleast one Philosopher");
}

int errorcheck(int argc,char **argv)
{
    if(!(argc == 5 || argc == 6))
    {
        errorhandler(1);
        return (1);
    }
    if(ft_atoi(argv[1]) < 1)
    {
        errorhandler(2);
        return (1);
    }
    return (0);
}