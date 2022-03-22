/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:07:05 by vvandenb          #+#    #+#             */
/*   Updated: 2022/03/22 17:33:14 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//If a child process exist, redirects the signal to the child
//Else prints a new line
void	handle_sig(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (CHILD_PID)
	{
		write(1, "\n", 1);
		kill(CHILD_PID, sig);
	}
	else
	{
		write(1, "\n", 1);
		write(1, PROMPT, ft_strlen(PROMPT));
	}
}

char	setup_signals()
{
	static struct sigaction		sig;

	sig.sa_sigaction = handle_sig;
	sig.sa_flags = 0;
	if (sigaction(SIGINT, &sig, NULL))
		error("SIGACTION");
	return (0);
}
