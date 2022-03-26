/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:38:16 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/26 16:05:20 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Prints the error and exits with `errno` code
void	error(const char *error)
{
	perror(error);
	exit(errno);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

//Removes a string part between `start` and `end` by replacing it with `fit`
//Returns a newly malloc'd string
char	*ft_str_replace(char *s, int start, int end, char *fit)
{
	char	*r;
	char	*part;
	char	*temp;

	if (s == NULL)
		return (NULL);
	part = ft_substr(s, 0, start);
	r = ft_strjoin(part, fit);
	free(part);
	part = ft_substr(s, end, ft_strlen(s));
	temp = r;
	r = ft_strjoin(r, part);
	free(temp);
	free(part);
	return (r);
}
