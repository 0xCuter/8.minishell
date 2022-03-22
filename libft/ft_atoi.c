/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:23:00 by vvandenb          #+#    #+#             */
/*   Updated: 2021/10/23 15:07:06 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	char		*strp;
	long int	num;
	char		sign;

	strp = (char *) str;
	sign = 1;
	while ((*strp >= 9 && *strp <= 13) || *strp == ' ')
		++strp;
	if (*strp == '+')
		strp++;
	else if (*strp == '-')
	{
		sign *= -1;
		++strp;
	}
	num = 0;
	while (*strp >= '0' && *strp <= '9' && *strp != 0)
	{
		num = num * 10 + (*strp - 48);
		++strp;
	}
	return (num * sign);
}
