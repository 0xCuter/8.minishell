/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:59:32 by vvandenb          #+#    #+#             */
/*   Updated: 2021/10/23 15:11:05 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_digits_count(int n)
{
	if (n == -2147483648)
		return (get_digits_count(2147483647));
	else if (n < 0)
		return (get_digits_count(n * -1));
	else if (n < 10)
		return (1);
	else
		return (1 + get_digits_count(n / 10));
}

static void	reverse_str(char *s, int size)
{
	int		c;
	char	t;

	c = 0;
	while (c < size / 2)
	{
		t = s[size - c - 1];
		s[size - c - 1] = s[c];
		s[c] = t;
		++c;
	}
	s[size] = 0;
}

static void	*sign_and_malloc(long int *n, int *sign)
{
	*sign = 1;
	if (*n < 0)
	{
		*sign = -1;
		*n *= -1;
	}
	if (*sign < 0)
		return (malloc((get_digits_count(*n) + 2) * sizeof(char)));
	else
		return (malloc((get_digits_count(*n) + 1) * sizeof(char)));
}

static char	*return_zero(char *c)
{
	c[0] = '0';
	c[1] = 0;
	return (c);
}

char	*ft_itoa(int n)
{
	int			sign;
	long int	nl;
	char		*c;
	char		*rc;

	nl = n;
	c = sign_and_malloc(&nl, &sign);
	if (c == NULL)
		return (NULL);
	if (nl == 0)
		return (return_zero(c));
	rc = c;
	while (nl)
	{
		*c++ = nl % 10 + 48;
		nl /= 10;
	}
	if (sign < 0)
		*c++ = '-';
	*c++ = 0;
	reverse_str(rc, ft_strlen(rc));
	return (rc);
}
