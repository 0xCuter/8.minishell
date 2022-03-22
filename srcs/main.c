/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:06:18 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/22 12:42:53 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Prints the error and exits with `errno`
static void	error(const char *error)
{
	perror(error);
	exit (errno);
}

//Searches for the command passed and executes it in a child process if found
//Returns the pid of the child, or else 0
static int	execute(char *line, char **path_split)
{
	int			pid;
	int			size;
	char		*command;
	char		found_command_location;
	struct stat	test;

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
			break ;
		}
		free(command);
		++path_split;
	}
	if (found_command_location)
	{
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
		free(command);
		return (pid);
	}
	return (0);
}

int	main()
{
	char	*path;
	char	**path_split;
	char	*line;

	path = getenv("PATH");
	if (path == NULL)
		return (1);
	path_split = ft_split(path, ':');
	if (path_split == NULL)
		error("MALLOC");
	setup_signals();
	while (1)
	{
		line = readline("Minishell$ ");
		execute(line, path_split);
		free(line);
		wait(NULL);
	}
}
