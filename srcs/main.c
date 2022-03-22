/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:06:18 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/22 10:56:26 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error(const char *error)
{
	perror(error);
	return (errno);
}

int	main()
{
	char 		*line;
	struct stat	buf;
	int			i;
	int			e;

	i = 0;
	while (i < 3)
	{
		line = readline("Minishell$ ");
		e = stat(line, &buf);
		if (e)
			perror("STAT");
		else
		{
			int pid = fork();
			if (pid == 0)
			{
				char *test[] = {"ls", NULL};
				if (execve(line, test, NULL))
					return (error("EXECVE"));
			}
			wait(NULL);
		}
		free(line);
		++i;
	}
}
