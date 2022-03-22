/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:37:08 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/22 17:32:59 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Searches for the command passed 
char	*find_command(char *line, char **path_split)
{
	struct stat	test;
	int			size;
	char		found_command_location;
	char		*command;

	found_command_location = 0;
	while (found_command_location == 0 && *path_split != NULL)
	{
		size = ft_strlen(*path_split) + ft_strlen(line) + 2;
		command = malloc(size * sizeof(char));
		ft_strlcpy(command, *path_split, size);
		ft_strlcat(command, "/", size);
		ft_strlcat(command, line, size);
		if (stat(command, &test) == 0)
		{
			found_command_location = 1;
			return (command);
		}
		free(command);
		++path_split;
	}
	return (NULL);
}

//Executes a command in a child process
//Returns its PID
int	execute(char *command)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		free(command);
		error("FORK");
	}
	if (pid == 0)
	{
		char *test[] = {"ls", NULL};
		if (execve(command, test, NULL))
			error("EXECVE");
	}
	CHILD_PID = pid;
	free(command);
	return (pid);
}
