/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:02:57 by dangonza          #+#    #+#             */
/*   Updated: 2022/05/03 18:35:24 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	ft_isspace(char c);
static int	return_final_value(unsigned long long final, int negative_sign);

int	ft_atoi(const char *str)
{
	unsigned long long	final;
	int					negative_sign;
	int					index;

	index = 0;
	final = 0;
	negative_sign = 1;
	while (ft_isspace(*(str + index)))
		index++;
	if (*(str + index) == '-' || *(str + index) == '+')
	{
		if (*(str + index) == '-')
			negative_sign = -1;
		index++;
	}
	while (*(str + index))
	{
		if (!ft_isdigit(*(str + index)))
			break ;
		final = (final * 10) + (*(str + index) - 48);
		index++;
	}
	return (return_final_value(final, negative_sign));
}

static int	return_final_value(unsigned long long final, int negative_sign)
{
	if (final > 9223372036854775807 && negative_sign < 0)
		return (0);
	else if (final > 9223372036854775807 && negative_sign > 0)
		return (-1);
	return ((int)(final * negative_sign));
}

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	if (c == '\f' || c == '\v' || c == '\r')
		return (1);
	return (0);
}
