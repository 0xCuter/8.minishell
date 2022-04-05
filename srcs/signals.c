/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:07:05 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/05 00:31:29 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//If a child process exists, redirects the signal to the child
//Else prints a new line
static void	ctrl_c()
{
	// if (g_child_pid)
	// {
	// 	write(1, "\n", 1);
	// 	kill(g_child_pid, SIGINT);
	// }
	// else
	{
		write(1, "\n", 1);
		prompt(NULL, 0);
	}
}

void	setup_signals(void)
{
	struct sigaction	c;
	struct sigaction	backslash;
	sigset_t			set;

	if (sigemptyset(&set))
		error("SIGEMPTYSET");
	c.sa_flags = 0;
	c.sa_mask = set;
	c.sa_sigaction = ctrl_c;
	if (sigaction(SIGINT, &c, NULL))
		error("SIGACTION");
	backslash.sa_flags = 0;
	backslash.sa_mask = set;
	backslash.sa_sigaction = ctrl_c;
	if (sigaction(SIGQUIT, &backslash, NULL))
		error("SIGACTION");
}
