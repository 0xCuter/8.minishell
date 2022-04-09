/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:38:16 by vvandenb          #+#    #+#             */
/*   Updated: 2022/04/09 14:57:33 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Frees prompt & history, prints "exit" and exits with `status`
void	exit_shell(int status)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	free(prompt(NULL));
	rl_clear_history();
	// system("leaks minishell");
	exit(status);
}

//Prints the error corresponding to `errno`, frees the prompt & history
// and exits with `errno` value
void	error(const char *error)
{
	perror(error);
	free(prompt(NULL));
	rl_clear_history();
	exit(errno);
}

//Frees a pointer and sets it to `NULL`
void	free_null(void **elem)
{
	free(*elem);
	*elem = NULL;
}

//Returns 1 if `r` is quoted in `s` by double quotes
//Returns 2 if `r` is quoted in `s` by single quotes
//Else 0
char	in_quotes(const char *s, char *r)
{
	char	*quote;
	char	*quote_end;

	if (s == NULL || r == NULL)
		return (0);
	quote = ft_str_chrset(s, METACHARS_QUOTES);
	while (quote && *quote)
	{
		quote_end = ft_strchr(quote + 1, *quote);
		if (quote_end == NULL)
			return (0);
		if (quote < r && r < quote_end)
		{
			if (*quote == '"')
				return (1);
			return (2);
		}
		quote = ft_str_chrset(quote_end + 1, METACHARS_QUOTES);
	}
	return (0);
}
