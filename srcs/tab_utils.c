/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 22:44:17 by scuter            #+#    #+#             */
/*   Updated: 2022/04/08 13:25:35 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**duplicate_tab(char **tab)
{
	char	**dup;
	int		i;

	i = 0;
	while (tab[i])
		i++;
	dup = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (tab[i])
	{
		dup[i] = ft_strdup(tab[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

void	sort_tab(char **tab)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (tab[i])
	{
		j = i + 1;
		while (tab[j])
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	**add_line(char *line, char **tab)
{
	char	**new;
	int		i;

	i = 0;
	while (tab[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (tab[i])
	{
		new[i] = ft_strdup(tab[i]);
		i++;
	}
	new[i] = ft_strdup(line);
	new[i + 1] = NULL;
	free_tab(tab);
	return (new);
}

char	**remove_line(char *line, char **tab)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	while (tab[i])
		i++;
	new = malloc(sizeof(char *) * (i));
	i = 0;
	j = 0;
	while (tab[i])
	{
		if (tab[i] == line)
			i++;
		if (tab[i])
		{
			new[j] = ft_strdup(tab[i]);
			i++;
			j++;
		}
	}
	new[j] = NULL;
	free_tab(tab);
	return (new);
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
