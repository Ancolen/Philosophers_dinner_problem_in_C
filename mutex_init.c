/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerturk <myerturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:59:22 by myerturk          #+#    #+#             */
/*   Updated: 2024/05/03 15:46:46 by myerturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	init_mutex(t_rules *rules)
{
	int	i;

	i = rules->nb_philo;
	rules->forks = malloc(sizeof(pthread_mutex_t) * i);
	if (!(rules->forks))
		return (free(rules->philosophers), 1);
	if (destroy_mutex(rules))
		return (free(rules->philosophers), 1);
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(rules->forks[i]), NULL))
		{
			while (++i < rules->nb_philo)
				pthread_mutex_destroy(&(rules->forks[i]));
			free(rules->philosophers);
			return (chose_mutex(rules, 3), 1);
		}
	}
	return (0);
}

int	destroy_mutex(t_rules *rules)
{
	if (pthread_mutex_init(&(rules->x_ate_check), NULL))
		return (1);
	else if (pthread_mutex_init(&(rules->t_last_meal_check), NULL))
		return (chose_mutex(rules, 1), 1);
	else if (pthread_mutex_init(&(rules->dieded_check), NULL))
		return (chose_mutex(rules, 2), 1);
	else if (pthread_mutex_init(&(rules->all_ate_check), NULL))
		return (chose_mutex(rules, 3), 1);
	return (0);
}

void	chose_mutex(t_rules *rules, int x)
{
	if (x >= 1)
		pthread_mutex_destroy(&(rules->x_ate_check));
	if (x >= 2)
		pthread_mutex_destroy(&(rules->t_last_meal_check));
	if (x >= 3)
		pthread_mutex_destroy(&(rules->dieded_check));
}
