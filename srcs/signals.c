/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:07:05 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/01 10:55:26 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_prompt(void)
{
	char	*tmp;
	int		len;
	int		slash;

	tmp = getenv("USER");
	if (!tmp)
		error("GETENV");
	ft_putstr_fd("\e[1;31m", 1);
	ft_putstr_fd(tmp, 1);
	ft_putstr_fd("\e[1;33m@42\e[1;32mNice\e[0m:", 1);
	tmp = getcwd(NULL, 0);
	len = ft_strlen(tmp);
	slash = 0;
	while (len && slash < 3)
	{
		len--;
		if (tmp[len] == '/')
			slash++;
	}
	ft_putstr_fd("\e[1;36m", 1);
	ft_putstr_fd(&tmp[len], 1);
	ft_putstr_fd("\e[0m$ ", 1);
	free(tmp);
}

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
		signal_prompt();
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
