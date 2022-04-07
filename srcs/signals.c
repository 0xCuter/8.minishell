/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:07:05 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/07 04:27:21 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//If a child process exists, redirects the signal to the child
//Else prints a new line
static void	ctrl_c(void)
{
	static int	flag = 0;
	char	*line;

	if (g_pid)
	{
		write(STDERR_FILENO, "\n", 1);
		kill(g_pid, SIGINT);
		g_pid = 0;
		flag = 0;
	}
	else
	{
		if (flag)
			write(STDERR_FILENO, "\b\b  \b\b\n", ft_strlen("\b\b  \b\b\n"));
		else
			write(STDERR_FILENO, "\n", 1);
		flag = 1;
		line = prompt(NULL);
		write(STDERR_FILENO, line, ft_strlen(line));
	}
}

static void	ctrl_backslash(void)
{
	static int	flag = 0;

	if (g_pid)
	{
		write(STDERR_FILENO, "Quit: 3\n", ft_strlen("Quit: 3\n"));
		kill(g_pid, SIGQUIT);
		g_pid = 0;
		flag = 0;
	}
	else
	{
		if (flag)
			write(STDERR_FILENO, "\b\b  \b\b", ft_strlen("\b\b  \b\b"));
		flag = 1;
	}
}

void	setup_signals(void)
{
	signal(SIGINT, (void *)ctrl_c);
	signal(SIGQUIT, (void *)ctrl_backslash);


	// struct sigaction	c;
	// struct sigaction	backslash;
	// sigset_t			set;

	// if (sigemptyset(&set))
	// 	error("SIGEMPTYSET");
	// c.sa_flags = 0;
	// c.sa_mask = set;
	// c.sa_sigaction = ctrl_c;
	// if (sigaction(SIGINT, &c, NULL))
	// 	error("SIGACTION");
	// backslash.sa_flags = 0;
	// backslash.sa_mask = set;
	// backslash.sa_sigaction = ctrl_c;
	// if (sigaction(SIGQUIT, &backslash, NULL))
	// 	error("SIGACTION");
}
