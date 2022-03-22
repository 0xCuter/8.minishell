/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:50:03 by scuter            #+#    #+#             */
/*   Updated: 2022/03/23 00:24:29 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = ((unsigned char *)s1);
	str2 = ((unsigned char *)s2);
	if (str1 == str2)
		return (0);
	i = 0;
	while ((str1[i]) && (str2[i]) && (str1[i] == str2[i]))
		i++;
	return (str1[i] - str2[i]);
}
