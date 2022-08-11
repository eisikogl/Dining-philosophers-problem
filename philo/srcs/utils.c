/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 07:44:29 by eisikogl          #+#    #+#             */
/*   Updated: 2022/08/11 07:56:49 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

int ft_atoi(char *str)
{
    int i;
    int num;

    i = 0;
    while(str != '\0')
    {
        if (str[i] == 32 || str[i] >= 9 && str[i] <= 13)
            i++;
        if (str[i] == '-' || str[i] == '+')
        {
            if (str[i] == '-')
                printf("Error negative input");
            i++;
        }
        while(str[i] >= '0' && str[i] <= '9')
        {
            num = num * 10 + (str[i] - 48);
            i++;
        }
        return (num);
    }
}