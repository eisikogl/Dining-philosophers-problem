/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloroutput.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 22:00:01 by eisikogl          #+#    #+#             */
/*   Updated: 2022/08/19 22:54:04 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void pick_color(int color)
{
    if(color == 1)
      red();
    if(color == 2)
      blue();
    if(color == 3)
      yellow();
    if(color == 4)
      green();
    if(color == 5)
      purple();
}

void red() 
{
  printf("\033[1;31m");
}

void yellow()
{
  printf("\033[1;33m");
}

void green()
{
    printf("\033[0;32m");
}

void blue()
{
    printf("\033[0;34m");
}

void purple()
{
    printf("\033[0;35m");
}

void reset() 
{
  printf("\033[0m");
}

