/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:38:07 by vvandenb          #+#    #+#             */
/*   Updated: 2021/10/25 15:03:04 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		c;
	char	*rs;

	c = 0;
	if (s == 0)
		return (NULL);
	rs = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (rs == NULL)
		return (NULL);
	while (s[c])
	{
		rs[c] = f(c, s[c]);
		++c;
	}
	rs[c] = 0;
	return (rs);
}
