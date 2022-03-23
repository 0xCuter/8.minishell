/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:07:05 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/23 17:12:00 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//If a child process exists, redirects the signal to the child
//Else prints a new line
static void	ctrl_c()
{
	if (g_child_pid)
	{
		write(1, "\n", 1);
		kill(g_child_pid, SIGINT);
	}
	else
	{
		write(1, "\n", 1);
		write(1, PROMPT, ft_strlen(PROMPT));
	}
}

//If a child process exists, redirects the signal to the child
static void	ctrl_backslash()
{
	kill(g_child_pid, SIGQUIT);
	printf("\n");
}

void	setup_signals(char child)
{
	struct sigaction		c;
	struct sigaction		backslash;
	static struct sigaction	old_backslash;
	sigset_t				set;

	if (sigemptyset(&set))
		error("SIGEMPTYSET");
	c.sa_flags = 0;
	c.sa_mask = set;
	c.sa_sigaction = ctrl_c;
	if (sigaction(SIGINT, &c, NULL))
		error("SIGACTION");
	if (child)
	{
		old_backslash.sa_sigaction = ctrl_backslash;
		if (sigaction(SIGQUIT, &old_backslash, NULL))
			error("SIGACTION");
	}
	else
	{
		backslash.sa_flags = 0;
		backslash.sa_mask = set;
		backslash.sa_handler = SIG_IGN;
		if (sigaction(SIGQUIT, &backslash, &old_backslash))
			error("SIGACTION");
	}
}
