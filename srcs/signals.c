/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:07:05 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/08 18:29:18 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_signal(void)
{
	// int	stdin_copy;

	// stdin_copy = dup(STDIN_FILENO);
	close(STDIN_FILENO);
	// dup2(stdin_copy, STDIN_FILENO);
	// close(stdin_copy);
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
		else if (sig == SIGINT)
		{
			write(STDERR_FILENO, prompt(NULL), ft_strlen(prompt(NULL)));
			write(STDERR_FILENO, rl_line_buffer, ft_strlen(rl_line_buffer));
			write(STDERR_FILENO, "  \n", 3);
			rl_on_new_line();
			rl_replace_line("", 1);
			rl_redisplay();
		}
		else if (sig == SIGQUIT)
		{
			write(STDERR_FILENO, prompt(NULL), ft_strlen(prompt(NULL)));
			write(STDERR_FILENO, rl_line_buffer, ft_strlen(rl_line_buffer));
			write(STDERR_FILENO, "  \a\b\b", 5);
			rl_redisplay();
		}
	}
}

void	setup_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
