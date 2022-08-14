/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 07:44:29 by eisikogl          #+#    #+#             */
/*   Updated: 2022/08/14 05:08:05 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

int	ft_atoi(char *str)
{
	int		neg;
	long	num;
	int		i;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			neg *= -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * neg);
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int time_diff(long long pres, long long past)
{
	return (pres - past);
}

void		smart_sleep(long long time, t_rules *rules)
{
	long long i;

	i = timestamp();
	while (1)
	{
		if (time_diff(timestamp(), i) >= time)
			break ;
		usleep(50);
	}
}

void	print_philo(t_rules *rules, int id, char *string)
{
		pthread_mutex_lock(&(rules->writing));
		printf("%dms %i ", time_diff(timestamp(),rules->first_time),id + 1);
		printf("%s\n", string);
		pthread_mutex_unlock(&(rules->writing));
}