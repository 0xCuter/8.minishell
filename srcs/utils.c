/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:38:16 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/27 16:20:10 by vvandenb         ###   ########.fr       */
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

//Returns index of the first appearing char in `line` from `set`
//End of `line` if none
char	*ft_str_chrset(const char *line, const char *set)
{
	int		i;
	char	*r;
	char	*last_r;

	if (*line == 0)
		return ((char *)line);
	last_r = (char *)line + ft_strlen(line);
	i = 0;
	while (i < (int)ft_strlen(set))
	{
		r = ft_strchr(line, set[i]);
		if (r && r < last_r)
			last_r = r;
		++i;
	}
	return (last_r);
}
