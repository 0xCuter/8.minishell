/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:07:05 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/09 10:58:47 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_signal(void)
{
	g_heredocing = 1;
	close(STDIN_FILENO);
}

static void	signal_parent(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		if (g_heredocing == 1)
			write(STDERR_FILENO, WAIT_PROMPT, ft_strlen(WAIT_PROMPT));
		write(STDERR_FILENO, "  \a\b\b", 5);
		rl_redisplay();
	}
}

// If a child processes exist, redirects the signal to the child
// Else if CTRL+C prints newline
// Else if CTRL+\ rings terminal
void	signal_handler(int sig)
{
	int	i;

	if (g_last_child)
	{
		if (g_pids)
		{
			if (sig == SIGQUIT)
				write(STDERR_FILENO, "Quit: 3", ft_strlen("Quit: 3"));
			write(STDERR_FILENO, "\n", 1);
			i = 0;
			while (g_pids[i])
				kill(g_pids[i++], SIGINT);
		}
		else
			signal_parent(sig);
	}
}

void	setup_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
