/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:23:41 by vvandenb          #+#    #+#             */
/*   Updated: 2021/11/07 09:41:13 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_of_splits(char const *s, char c)
{
	int	i;
	int	n;

	if (s == NULL)
		return (1);
	i = 0;
	n = 1;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i])
				++i;
			++n;
			if (s[i] == 0)
				return (n);
		}
		++i;
	}
	return (n);
}

static void	free_array(char **array, int n)
{
	while (n)
	{
		free(array[n]);
		--n;
	}
}

static char	**ft_split2(char const *s, char c, char **array, int n)
{
	int		i;
	int		i_cpy;

	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			i_cpy = i;
			while (s[i_cpy] != c && s[i_cpy])
				++i_cpy;
			array[n] = ft_substr(s, i, i_cpy - i);
			if (array[n] == NULL)
			{
				free_array(array, n);
				return (array);
			}
			i = i_cpy - 1;
			++n;
		}
		++i;
	}
	array[n] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	int		n;
	char	**array;

	if (s == NULL)
		return (NULL);
	n = 0;
	array = malloc(num_of_splits(s, c) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	return (ft_split2(s, c, array, n));
}
