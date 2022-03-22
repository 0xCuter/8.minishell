/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:32:02 by vvandenb          #+#    #+#             */
/*   Updated: 2021/10/23 15:12:06 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	putnbr_fd(long int n, int fd)
{
	if (n / 10)
		putnbr_fd(n / 10, fd);
	ft_putchar_fd(n % 10 + 48, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long int	ln;

	ln = n;
	if (ln < 0)
	{
		ln *= -1;
		ft_putchar_fd('-', fd);
	}
	putnbr_fd(ln, fd);
}
