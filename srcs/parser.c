/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 09:16:23 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/23 10:55:58 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Parses the read `line` and puts the result in a list
t_list	*parse_line(char *line)
{
	int			i;
	char		**lines;
	t_list		*cmd_list;
	t_command	*cmd;

	cmd_list = NULL;
	lines = ft_split(line, ';');
	if (lines == NULL)
		return (NULL);
	i = 0;
	while (lines[i])
	{
		cmd = malloc(sizeof(t_command));
		if (cmd == NULL)
			return (NULL);
		cmd->cmd_split = ft_split(lines[i], ' ');
		ft_lstadd_back(&cmd_list, ft_lstnew(cmd));
		++i;
	}
	free(lines);
	return (cmd_list);
}
